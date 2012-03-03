
/*
 *  timeout2.c
 *
 *  This module demonstrates a different strategy for
 *  timeouts -- in this example, the clients themselves
 *  determine their own timeout policies, and the
 *  server has to deal with it.
 *
 *  We still have no producers, as we are still demonstrating
 *  timeouts :-)
 *
 *  The advantage of this approach over timeout1.c is that
 *  the server is not counting seconds (i.e. waking up
 *  periodically and wastefully just to increment and check
 *  a counter).
 *
 *  Another difference between this one and timeout1.c is
 *  that since the client is timing out on its own, the server
 *  doesn't know about it.  The client simply turns around 
 *  and sends another message.  But each time the server receives 
 *  a message from a client, it mallocs some memory to add the
 *  client to a list of blocked clients.  And since it doesn't
 *  know when the client times out, it never removes the client
 *  from the list.  So this one has a memory leak.
 *
 *  You can see this memory leak because when the main thread 
 *  is about to exit, it sends a message to the server to get 
 *  it to dump its internal work queue...
 *
 *  timeout3.c fixes this problem.
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

char    *progname = "to2";

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
    int             rcvid;
    QueueMember_t   *tmp;       // temp pointers

    chid = ChannelCreate (0);
    if (chid == -1) {
        printf ("%s:  (server %d) couldn't create a channel, errno %d\n",
                progname, (int) i, errno);
        exit (1);   // shut down the whole show
    }

    while (1) {

        /*
         *  get an IPC message via MsgReceivev
         *  Note that we block here until someone sends us
         *  something.
        */

        rcvid = MsgReceive (chid, &ipc, sizeof(ipc), NULL);
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
            printf ("%s:  server data structure dump, listing RCVIDs:\n", progname);
            for (tmp = consumerHead; tmp; tmp = tmp -> next) {
                printf ("%X ", tmp -> rcvid);
            }
            printf ("\nDump done, replying\n");
            MsgReplyv (rcvid, 0, NULL, 0);
            break;
        }
    }
    return (NULL);
}

