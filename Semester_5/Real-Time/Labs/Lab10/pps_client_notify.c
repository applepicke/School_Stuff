
/*
 *  pps_client_notify.c
 *  Demonstrate using ionotify() to get events when a pps data element is updated.
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/iomsg.h>
#include <sys/neutrino.h>
#include "pps_def.h"


void get_data_and_ionotify (int fd, struct sigevent *event);

#define MY_PULSE_CODE  (_PULSE_CODE_MINAVAIL+0)

char    *progname = "pps_notify_client";
int     pps_fd;            /* file descriptor for talking to ionotify.c */
struct sigevent pps_notify_event; /* the event for ionotify.c to deliver */
struct _pulse   pulse_msg;      /* the receive message buffer */

int main (int argc, char **argv) {
    int chid, coid, rcvid;

    printf ("%s:  starting...\n", progname);

    chid = ChannelCreate (0);

    /* create a connection to the channel that we are receiving on */
    coid = ConnectAttach (0, 0, chid, _NTO_SIDE_CHANNEL, 0);

    /* this macro fills in the event structure */
    SIGEV_PULSE_INIT (&pps_notify_event, coid, getprio (0), MY_PULSE_CODE, 0);

    /*
     * send the pulse event structure to ionotify.c, ionotify.c will
     * deliver this pulse event when data is available.  When it does,
     * our MsgReceive() below will return with the pulse.
     */

    if ((pps_fd = open (PPS_COUNT_NAME, O_RDONLY)) == -1) {
        fprintf (stderr, "%s:  open('%s') failed: %s\n",
                progname, PPS_COUNT_NAME, strerror (errno));
        exit (EXIT_FAILURE);
    }

    /*
     * send the event to ionotify.c so that it can deliver it whenever 
     * it wants to but check for data at the same time (see 
     * get_data_and_ionotify() below)
     */
     
    get_data_and_ionotify (pps_fd, &pps_notify_event);
    
    while (1) {
        rcvid = MsgReceive (chid, &pulse_msg, sizeof(pulse_msg), NULL);
        if (rcvid == 0) {
            // we got a pulse, assume it is the one we asked for
            printf ("%s:  we received a pulse\n", progname);
            get_data_and_ionotify (pps_fd, &pps_notify_event);
        }
    }
}

void
get_data_and_ionotify (int fd, struct sigevent *event) {
    char    buf[255];
    int     nbytes, flags;
    
    /*
     * Note that we are doing _NOTIFY_ACTION_POLLARM which tells
     * the pps to poll first.  If there is no data then
     * notification is armed (i.e. it'll deliver the event when
     * data arrives).  However, if there is data then ionotify() will
     * return with a flag indicating that there is data.  So we read
     * the data below.  Once you've read the data, however, notification
     * is removed so you have to remind it, hence the second call to
     * ionotify().  And since more data may have arrived between the
     * last read() and the second ionotify(), we check the flags again.
     */
    
    flags = ionotify (fd, _NOTIFY_ACTION_POLLARM, _NOTIFY_COND_INPUT, event);
    while (flags & _NOTIFY_COND_INPUT) {
        nbytes = read (fd, buf, sizeof(buf)-1);
        buf[nbytes] = NULL;
        printf ("%s:  read:\n%s\n", progname, buf);
        flags = ionotify (fd, _NOTIFY_ACTION_POLLARM, _NOTIFY_COND_INPUT, event);
    }
}

// eof: pps_client_notify.c
