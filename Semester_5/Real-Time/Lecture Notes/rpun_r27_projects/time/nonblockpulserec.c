
/*
 *  This module demonstrates how a pulse receiver can clean up a burst
 *  of pulses.  This typically is used when you have an interrupt
 *  that will cause a burst of pulses.  When you receive the first one, 
 *  you might want to clean up any others before going back to the main loop.
 *
 *  The trick is to turn the block MsgReceivePulse() call into a
 *  nonblocking call.  To do this we use a zero length timeout.
 *  If a pulse is waiting then MsgReceivePulse() is not about to
 *  block so it simply returns with the pulse.  If no pulse is waiting
 *  then MsgReceivePulse() is about to block so it immediately times out.
 *  Since it timed out you know that there is no pulse waiting and can
 *  go back to the main loop. 
 *
 *  To make things simple, the pulse deliverer is just another thread in 
 *  this same process.  To test this:
 *
 *    nonblockpulserec -v &
 *
 *  nonblockpulserec will soon start getting bursts of pulses.
 *
*/

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/neutrino.h>

#define OUR_PULSE_CODE  (_PULSE_CODE_MINAVAIL + 7)

void *pulse_sender_thread (void *arg);
void options (int argc, char **argv);

char    *progname = "nonblockpulserec";
int     verbose;            /* -v for verbose operation */
int     chid;               /* the channel for receiving pulses on */
int     pulse_rec_coid;     /* the connection to send the pulse to */

int main (int argc, char **argv)
{
    int             rcvid, flags;
    struct _pulse   pulse;
    struct sigevent event;
    
    printf ("%s:  starting...\n", progname);

    options (argc, argv);

    chid = ChannelCreate (0);
    
    /* create the thread that will send us the pulses */
    pthread_create (NULL, NULL, pulse_sender_thread, NULL);

    while (1) {
        rcvid = MsgReceive (chid, &pulse, sizeof(pulse), NULL);

        printf ("%s:  we received a pulse, checking for more", progname);
    
        event.sigev_notify = SIGEV_UNBLOCK;
        flags = _NTO_TIMEOUT_RECEIVE;
        /* loop, receiving (cleaning up) all pulses in receive queue */
        do {
            /* MsgReceivePulse() wont block, if theres a pulse it
             * will return 0, otherwise it will timeout immediately
            */
            TimerTimeout (CLOCK_REALTIME, flags, &event, NULL, NULL);
            rcvid = MsgReceivePulse (chid, &pulse, sizeof(pulse), NULL);
            if (rcvid == 0)
                printf ("... pulse");
        } while (rcvid != -1);
        /* if errno is ETIMEDOUT, then we got all the pulses */
        printf ("\n");
    }
}

/*
 *  pulse_sender_thread
 *
 *  This simulates an interrupt that delivers bursts of pulses
 *  every now and then.
*/

void *
pulse_sender_thread (void *arg)
{
    int i, coid;

    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);

    while (1) {
        sleep (5);
        /* send a burst of pulses */
        for (i = 0; i < 7; i++)
            MsgSendPulse (coid, OUR_PULSE_CODE, 0, 0);
    }
    return NULL;
}

/*
 *  options
 *
 *  This routine handles the command line options:
 *      -v          verbose operation
*/

void
options (int argc, char **argv)
{
    int     opt;

    verbose = 0;

    while ((opt = getopt (argc, argv, "v")) != -1) {
        switch (opt) {
        case 'v':
            verbose = 1;
            break;
        }
    }   
}
