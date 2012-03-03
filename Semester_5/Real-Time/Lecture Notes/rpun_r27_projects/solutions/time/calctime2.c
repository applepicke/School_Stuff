
/*
 *  calctime2.c
 *
 *  This module is a copy of calctime1.c, modify it to adjust
 *  the clock resolution to be 2 ms.
 *
*/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>

#define BILLION         1000000000
#define NumSamples      30

char    *progname = "calctime2";

int main ()
{
    struct timespec clockval, prevclockval;
    uint64_t        delta;
    uint64_t        cycs [NumSamples];
    int             i;
	struct _clockperiod new, old;

    /*
     *  class: adjust the timer to be 2 ms
    */
    new.nsec = 2*1000*1000;
    new.fract = 0;
    ClockPeriod( CLOCK_REALTIME, &new, &old, 0 );

    printf ("\nClockTime deltas:\n");

    /*
     *  capture some clock changes
    */

    for (i = 0; i < 10; i++) {
        clock_gettime (CLOCK_REALTIME, &prevclockval);
        do {
            clock_gettime (CLOCK_REALTIME, &clockval);
        } while (clockval.tv_sec  == prevclockval.tv_sec &&
                 clockval.tv_nsec == prevclockval.tv_nsec);
        delta = ((uint64_t) clockval.tv_sec * BILLION + (uint64_t) clockval.tv_nsec) -
                ((uint64_t) prevclockval.tv_sec * BILLION + (uint64_t) prevclockval.tv_nsec);
        printf ("prev %u.%09lu, new %u.%09lu, delta %llu\n",
                prevclockval.tv_sec, prevclockval.tv_nsec,
                clockval.tv_sec, clockval.tv_nsec,
                delta);
    }

    /*
     *  next, we very quickly snapshot some values of the ClockCycles
     *  call.  We don't do any printf's, as we want to see the speed
     *  with which the "for" loop executes.
    */

    printf ("%d ClockCycles values:\n", NumSamples);

    for (i = 0; i < NumSamples; i++) {
        cycs [i] = ClockCycles ();
    }

    /*
     *  now, print out the delta's, so we can easily compute how much
     *  time each "for" loop iteration took.
    */

    printf ("%llu\n", cycs [0]);
    for (i = 1; i < NumSamples; i++) {
        printf ("%llu, delta %llu (decimal)\n",
                cycs [i], cycs [i] - cycs [i - 1]);
    }

	// Restore old clock period when done.
	ClockPeriod( CLOCK_REALTIME, &old, NULL, 0 );

    printf("clock cycles value is %lld\n", SYSPAGE_ENTRY(qtime)->cycles_per_sec);

    printf ("%s:  main, exiting\n", progname);
    return EXIT_SUCCESS;
}
