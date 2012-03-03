/*
 *  pps_client_select.c
 *  Demonstrate using select() to get events when a pps data element is updated.
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "pps_def.h"

char    *progname = "pps_client_select";

int main (int argc, char **argv)
{
    char    buf[256];
    fd_set  rfd;
    int     pps_fd;    /* file descriptor for talking to ionotify.c */
    int     n;
    
    printf ("%s:  starting...\n", progname);

    if ((pps_fd = open (PPS_COUNT_NAME, O_RDONLY)) == -1) {
        fprintf (stderr, "%s:  open('%s') failed: %s\n",
                progname, PPS_COUNT_NAME, strerror (errno));
        exit (EXIT_FAILURE);
    }

    FD_ZERO (&rfd); 
    FD_SET (pps_fd, &rfd);
    
    while (1) {
    
        /*
         * select() will ask pps to notify us when data is available.
         * It will then block, waiting to be notified.  When an attribute has
         * changed, pps will notify us and select() will unblock
         * and return which file descriptor has data.
        */
        
        if ((n = select (1 + pps_fd, &rfd, 0, 0, NULL)) == -1) {
            perror ("select failed");
            exit (EXIT_FAILURE);
        }
        if (n > 0 && FD_ISSET (pps_fd, &rfd)) {
            n = read (pps_fd, buf, sizeof(buf)-1);
            buf[n] = NULL;
            printf ("%s:  read\n%s\n", progname, buf);
        }
    }
}
