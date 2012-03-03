
/*
 *  alarm1.c
 *
 *  This module demonstrates the POSIX alarm function.
 *
*/

#include <stdio.h>
#include <sys/neutrino.h>
#include <unistd.h>

char    *progname = "alarm1";

int main ()
{
    printf ("%s:  setting an alarm for 10 seconds\n", progname);

    alarm (10);

    printf ("%s:  and then sleeping for 20!\n", progname);

    sleep (20);

    printf ("%s:  main, should never get here\n", progname);
    
    return 0;
}
    
