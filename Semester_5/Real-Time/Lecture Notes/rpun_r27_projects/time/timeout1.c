
/*
 *  timeout1.c
 *
 *  This module demonstrates some strategies that can
 *  be used for timeouts.
 *
 *  This module is a producer/consumer arrangement but we 
 *  have no producers, only consumers.  The point here is 
 *  to show one of the ways that the server can implement 
 *  a timeout on the consumer, so that the consumer doesn't 
 *  wait too long for a reply.  We've arbitrarily set this
 *  timeout to 5 seconds.  Since there are no producers,
 *  all consumers will timeout.
 *
 *  Note that this method isn't that great for two reasons:
 *  1. The server is basically counting time - it has implemented
 *     it's own timer.
 *  2. The server is more complex than it needs to be.
 *  timeout2.c doesn't have these problems.
*/

#include <errno.h>
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

#define STS_OK          0
#define STS_TIMEOUT     1

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
    IPC_t       message;
    IPC_reply_t message_reply;
    struct _pulse   pulseMessage;
}   Message_t;

typedef struct qmt
{
    int     rcvid;          // who to reply to
    int     number;         // the job ID number
    int     timeleft;       // number of seconds left in timeout
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

char    *progname = "to1";

int main ()
{
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
    printf ("%s:  main, exiting\n", progname);
    
    return 0;
}

/*-------------------------------------------------------------------*
 *  Consumer thread
 *
 *  The consumer's job is to consume numbers produced by the producer.
 *  Note that with no producers, all of the requests will time out
 *  after 5 seconds.  This timeout is implemented in the server.
 *-------------------------------------------------------------------*/

void *
consumer (void *i)
{
    Message_t   ipc;
    int         coid;

    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        printf ("%s:  (consumer %d) couldn't connect to channel, errno %d\n",
                progname, (int) i, errno);
        pthread_exit (NULL);    // shut down just this thread
        // or, we could have just done a "return (NULL);"
    }

    while (1) {
        ipc.message.command = COMMAND_GET;
        printf ("%s:  (consumer %d) getting work\n", progname, (int) i);
        MsgSend (coid, &ipc, sizeof(ipc), &ipc, sizeof(ipc));
        switch (ipc.message_reply.status) {
        case    STS_OK:
            printf ("%s:  (consumer %d) got job ID %d\n",
                    progname, (int) i, ipc.message_reply.number);
            break;
        case    STS_TIMEOUT:
            printf ("%s:  (consumer %d) timed out by server\n",
                    progname, (int) i);
            break;
        default:
            printf ("%s:  (consumer %d) unknown status %d\n",
                    progname, (int) i, ipc.message_reply.status);
            break;
        }
    }
    return (NULL);
}

/*-------------------------------------------------------------------*
 *  Server thread
 *
 *  In this example, we maintain a queue of consumers.  Since there
 *  are no producers, the consumers will simply line up, waiting for
 *  a request that cannot be satisfied.  After 5 seconds, the server
 *  will time them out, and return a "timed out" message.
 *-------------------------------------------------------------------*/

void *
server (void *i)
{
    Message_t       ipc;
    int             rcvid;
    QueueMember_t   *hdr, *tmp;     // temp pointers

    struct  sigevent    event;      // event we want delivered, a pulse
    struct  itimerspec  itime;      // interval timer
    timer_t             timerID;    // our timer ID

    int         coid;

    chid = ChannelCreate (0);
    if (chid == -1) {
        printf ("%s:  (server %d) couldn't create a channel, errno %d\n",
                progname, (int) i, errno);
        exit (1);   // shut down the whole show
    }

    /*
     *  set a connection back to ourselves, so that we can send
     *  ourselves pulses 
    */

    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if (coid == -1) {
        printf ("%s:  (server %d) couldn't connect to channel, errno %d\n",
                progname, (int) i, errno);
        exit (1);      // shut down everything
    }

    /*
     *  now set up the timer to go off once per second, and generate
     *  a pulse event
    */

    event.sigev_notify = SIGEV_PULSE;
    event.sigev_coid = coid;
    event.sigev_priority = 10;
    event.sigev_code = 39;          // some number we select
    timer_create (CLOCK_REALTIME, &event, &timerID);

    itime.it_value.tv_sec = 1;
    itime.it_value.tv_nsec = 0;
    itime.it_interval.tv_sec = 1;
    itime.it_interval.tv_nsec = 0;
    timer_settime (timerID, 0, &itime, NULL);
    
    while (1) {

        /*
         *  get an IPC message via MsgReceivev
         *  Note that we block here until someone sends us
         *  something.
        */

        rcvid = MsgReceive (chid, &ipc, sizeof(ipc), NULL);
        printf ("%s:  (server %d) rcvid %x\n", progname, (int) i, rcvid);

        if (rcvid == 0) {           // not a regular message, must be a pulse!
            while (consumerHead) {
                if (--consumerHead -> timeleft == 0) {
                    ipc.message_reply.status = STS_TIMEOUT;
                    MsgReply (consumerHead -> rcvid, 0, &ipc, sizeof(ipc));
                    tmp = consumerHead;
                    consumerHead = consumerHead -> next;
                    free (tmp);
                } else {
                    hdr = consumerHead -> next;
                    while (hdr) {
                        --hdr -> timeleft;
                        hdr = hdr -> next;
                    }
                    break;
                }
            }
        } else {                    // assume it's a GET command
            printf ("%s:  (server %d) blocked consumer\n", progname, (int) i);
            tmp = malloc (sizeof (QueueMember_t));
            if (tmp == NULL) {
                fprintf (stderr, "%s:  out of memory!\n", progname);
                perror (NULL);
                exit (1);
            }
            tmp -> rcvid = rcvid;
            tmp -> timeleft = 5;            // 5 second timeout
            tmp -> next = NULL;
            if (consumerHead == NULL) {
                consumerHead = tmp;
            } else {
                for (hdr = consumerHead; hdr -> next; hdr = hdr -> next)
                    ;
                hdr -> next = tmp;          // put at end, so they are sorted
            }
        }
    }
    return (NULL);
}

