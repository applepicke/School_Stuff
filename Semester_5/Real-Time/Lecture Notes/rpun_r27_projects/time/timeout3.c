
/*
 *  timeout3.c
 *
 *  This module demonstrates how to fix the memory leak problem
 *  that exists in timeout2.c.
 *
 *  The whole key to this solution is that the server now sets the
 *  _NTO_CHF_UNBLOCK flag when it creates its channel.  This causes
 *  two things to happen:
 *  1. When the client is supposed to timeout, it doesn't.  Instead
 *     it remains blocked until the server replies, and...
 *  2. ... the server receives a special pulse message (with a
 *     pulse code of _PULSE_CODE_UNBLOCK) from the kernel essentially 
 *     telling the server that the client would like a reply so that 
 *     it could unblock.
 *
 *  It is during handling of this _PULSE_CODE_UNBLOCK pulse message 
 *  that the server removes the client from it's list of blocked 
 *  clients and then replies.
 *
*/

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <malloc.h>
#include <stdlib.h>

/*
 *  the communications structure
*/

#define COMMAND_GET     1
#define COMMAND_DUMP    2

#define STS_OK          0
#define STS_TIMEOUT     1
#define STS_DUMPED      2

typedef struct              // input message structure
{
    int     command;
    int     number;
}   IPC_t;

typedef struct              // output message structure
{
    int     status;
    int     number;
}   IPC_reply_t;

typedef union               // all possible messages
{
    IPC_t           message;
    IPC_reply_t     message_reply;
    struct _pulse   pulse;
}   Message_t;

typedef struct qmt
{
    int     rcvid;          // who to reply to
    int     number;         // the job ID number
    struct  qmt *next;      // next on queue
}   QueueMember_t;

/*
 *  our global variables
*/

int     chid;               // the channel ID

QueueMember_t   *consumerHead;  // queue of queued consumers

/*
 *  forward references
*/

void    *consumer (void *);
void    *server (void *);
void    dequeueRcvid (int rcvid);

char    *progname = "to3";

int main ()
{
    Message_t   ipc;
    int         coid;

    consumerHead = NULL;                // no consumers

    pthread_create (NULL, NULL, server, (void *) 1);
    sleep (1);      // give the server a chance to startup

    /*
     *  create three consumers, with a delay between
     *  them.
    */

    pthread_create (NULL, NULL, consumer, (void *) 1);
    sleep (1);
    pthread_create (NULL, NULL, consumer, (void *) 2);
    sleep (1);
    pthread_create (NULL, NULL, consumer, (void *) 3);

    sleep (20);     // let the threads run

    /*
     *  now send a message to the server to get it to dump
     *  out its internal data structures...
    */

    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        printf ("%s:  (main) couldn't connect to channel, errno %d\n",
                progname, errno);
        exit (1);
    }

    ipc.message.command = COMMAND_DUMP;
    MsgSend (coid, &ipc, sizeof(ipc), NULL, 0);

    printf ("%s:  main, exiting\n", progname);
    
    return 0;
}

/*-------------------------------------------------------------------*
 *  Consumer thread
 *
 *  The consumer's job is to consume numbers produced by the producer.
 *  Note that with no producers, all of the requests will time out
 *  after 5 seconds.  This timeout is implemented in the consumer
 *  itself, using the kernel timeout feature.
 *-------------------------------------------------------------------*/

void *
consumer (void *i)
{
    Message_t   ipc;
    int         coid;
    struct  sigevent    event;          // the event we want delivered
    uint64_t    timeout;                // specify the timeout
    int         flags;
    int         sts;
    int         dumped = 0;

    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        printf ("%s:  (consumer %d) couldn't connect to channel, errno %d\n",
                progname, (int) i, errno);
        pthread_exit (NULL);    // shut down just this thread
        // or, we could have just done a "return (NULL);"
    }

    while (!dumped) {
        ipc.message.command = COMMAND_GET;
        printf ("%s:  (consumer %d) getting work\n", progname, (int) i);

        /*
         *  prime the timeout to be 5 seconds, on either a SEND or REPLY
        */

        event.sigev_notify = SIGEV_UNBLOCK;
        timeout = 5000000000LL; /* 5,000,000,000 nanosecs = 5 seconds */
        flags = _NTO_TIMEOUT_SEND | _NTO_TIMEOUT_REPLY;
        TimerTimeout (CLOCK_REALTIME, flags, &event, &timeout, NULL);

        sts = MsgSend (coid, &ipc, sizeof(ipc), &ipc, sizeof(ipc));
        if (sts != 0) {
            switch (errno) {
            case    ETIMEDOUT:
                printf ("%s:  (consumer %d) timed out by kernel\n",
                        progname, (int) i);
                break;
            default:
                printf ("%s:  (consumer %d) unexpected errno %d\n",
                        progname, (int) i, errno);
                perror (NULL);
                break;
            }
        } else {
            switch (ipc.message_reply.status) {
            case    STS_OK:
                printf ("%s:  (consumer %d) got job ID %d\n",
                        progname, (int) i, ipc.message_reply.number);
                break;
            case    STS_TIMEOUT:
                printf ("%s:  (consumer %d) got timeout confirmation\n",
                        progname, (int) i);
                break;
            case    STS_DUMPED:
                dumped = 1; /* this'll cause this thread to terminate */
                printf ("%s:  (consumer %d) got reply from server during cleanup (dump)\n",
                        progname, (int) i);
                break;
            default:
                printf ("%s:  (consumer %d) unknown status %d\n",
                        progname, (int) i, ipc.message_reply.status);
                break;
            }
        }
    }
    return (NULL);
}

/*-------------------------------------------------------------------*
 *  Server thread
 *
 *  In this example, we maintain a queue of consumers.  Since there
 *  are no producers, the consumers will simply line up, waiting for
 *  a request that cannot be satisfied.  After 5 seconds, the clients
 *  time out, and the request is lost.
 *-------------------------------------------------------------------*/

void *
server (void *i)
{
    Message_t       ipc;
    int             rcvid, client_rcvid;
    QueueMember_t   *tmp;       // temp pointers

    chid = ChannelCreate (_NTO_CHF_UNBLOCK);
    if (chid == -1) {
        printf ("%s:  (server %d) couldn't create a channel, errno %d\n",
                progname, (int) i, errno);
        exit (1);   // shut down the whole show
    }

    while (1) {
        rcvid = MsgReceive (chid, &ipc, sizeof(ipc), NULL);

        if (rcvid == 0) {
            /* we got a pulse message */

            /* the rcvid that was returned when we received the client's
             * original message is passed to us in the pulse message.
             * Save it since we are about to overwrite the receive
             * message buffer with our reply and we don't want to take
             * a chance on overwriting this rcvid.
            */
            client_rcvid = ipc.pulse.value.sival_int;

            /* reply to the client */
            ipc.message_reply.status = STS_TIMEOUT;
            MsgReply (client_rcvid, 0, &ipc, sizeof(ipc));

            /* dequeueRcvid() is written below.  It removes the client
             * from our list of blocked clients.
            */
            dequeueRcvid (client_rcvid);
            
            continue; /* go back to the MsgReceive() */
        }

        /* we got a regular message */

        printf ("%s:  (server %d) rcvid %x, command %d\n",
                progname, (int) i, rcvid, ipc.message.command);
        switch (ipc.message.command) {
        case    COMMAND_GET:
            printf ("%s:  (server %d) blocked consumer\n", progname, (int) i);
            tmp = malloc (sizeof (QueueMember_t));
            if (tmp == NULL) {
                fprintf (stderr, "%s:  out of memory!\n", progname);
                perror (NULL);
                exit (1);
            }
            tmp -> rcvid = rcvid;
            tmp -> next = consumerHead;
            consumerHead = tmp;
            break;
        case    COMMAND_DUMP:
            printf ("%s:  server data structure dump, listing RCVIDs and replying:\n", progname);
            for (tmp = consumerHead; tmp; tmp = tmp -> next) {
                printf ("%X ", tmp -> rcvid);
            }
            /* loop again, but this time replying, this way the printfs
               work out nicer */
            ipc.message_reply.status = STS_DUMPED;
            for (tmp = consumerHead; tmp; tmp = tmp -> next) {
                MsgReply (tmp -> rcvid, 0, &ipc, sizeof(ipc));
            }
            printf ("\nDump done, replying\n");
            MsgReply (rcvid, 0, NULL, 0);
            break;
        }
    }
    return (NULL);
}

/*
 *  a convenient subroutine for removing all matching entries
 *  out of the consumer queue, based on the rcvid
*/

void
dequeueRcvid (int rcvid)
{
    QueueMember_t   *hdr, *tmp;

    if (consumerHead && consumerHead -> rcvid == rcvid) {
        tmp = consumerHead;
        consumerHead = consumerHead -> next;
        free (tmp);
    } else {            // we have to search for it
        for (hdr = consumerHead; hdr -> next; ) {
            if (hdr -> next -> rcvid == rcvid) {
                tmp = hdr -> next;
                hdr -> next = hdr -> next -> next;
                free (tmp);
            } else {
                hdr = hdr -> next;
            }
        }
    }
}

