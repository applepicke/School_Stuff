/*
 * reptimer.c
 * 
 * This program demonstrates how to use a repeating timer to wake up
 * a thread periodically.  In this case we will wake up by receiving
 * a pulse message whenever the timer expires.
 * 
 * This example uses a simple MsgReceive() loop.  It could also have been
 * written as a resource manager, the only difference being the way in 
 * which the pulse would be received.  The set up for the timer is the same.
 * An example of where you might use a timer with a simple MsgReceive()
 * loop like this is in a driver, where the hardware handling driver
 * thread needs to wake up periodically as well as handle interrupts.
 * 
 * You need to add the code to create the timer and start it ticking.
 *
 *  To test it, run it as follows:
 *    reptimer
 *
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>
#include <unistd.h>
#include <string.h>

#define TIMER_PULSE_EVENT (_PULSE_CODE_MINAVAIL + 7)

/* union of all different types of message(s) we will receive (for this
 * exercise we will only be receiving pulses)
*/
typedef union {
    struct _pulse pulse;
} message_t;

char *progname = "reptimer";

int main(int argc, char *argv[]) 
{
    int               rcvid;
    struct sigevent   event;
    int               chid, coid;
    message_t         msg;

    chid = ChannelCreate( 0 );
    if (chid == -1) {
        fprintf( stderr, "%s:  ChannelCreate failed: %s\n",
            progname, strerror(errno) );
        exit( EXIT_FAILURE );
    } else {
    	printf( "channel created, id is %d\n", chid );
    }

    /* set up the pulse event that will be delivered to us by the kernel
     * whenever the timer expires
    */
    coid = ConnectAttach( 0, 0, chid, _NTO_SIDE_CHANNEL, 0 );
    if (coid == -1) {
        fprintf( stderr, "%s:  ConnectAttach failed: %s\n",
            progname, strerror(errno) );
        exit( EXIT_FAILURE );
    } else {
    	printf( "ConnectAttach Succeed, coid = %d\n", coid );
    }

    SIGEV_PULSE_INIT( &event, coid, 10, TIMER_PULSE_EVENT, 0 );

    /* class: Create a timer which will send the above pulse event 
     * 5 seconds from now and then repeatedly after that every
     * 1500 milliseconds.  The event to use has already been filled in
     * above and is in the variable called 'event'.
    */

    while (1) {
        /* wait here for the pulse message */
        rcvid = MsgReceive( chid, &msg, sizeof(msg), NULL );
        if (rcvid == -1) {
            fprintf( stderr, "%s:  MsgReceive failed: %s\n",
                progname, strerror(errno) );
            continue;
        }
        if (rcvid == 0) {
            /* we got a pulse */
            switch (msg.pulse.code) {
            case TIMER_PULSE_EVENT:
                /* we got our timer pulse */
                printf( "%s:  got our pulse, the timer must have expired\n",
                    progname );
                break;
            default:
                printf( "%s: unexpect pulse code: %d\n", progname, msg.pulse.code );
                break;
            }
        }
    }
}
