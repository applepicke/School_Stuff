
/*
 *  mutex.c
 *
 *  This code is the same as nomutex.c.
 *
 *  The exercise is to use the mutex construct that we learned
 *  about to modify the source to prevent our access problem.
 *
*/

#include <stdio.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

/*
 *  The number of threads that we want to have running
 *  simultaneously.
*/

#define NumThreads      4

/*
 *  the global variables that the threads compete for.
 *  To demonstrate contention, there are two variables
 *  that have to be updated "atomically".  With RR
 *  scheduling, there is a possibility that one thread
 *  will update one of the variables, and get preempted
 *  by another thread, which will update both.  When our
 *  original thread runs again, it will continue the
 *  update, and discover that the variables are out of
 *  sync.
*/

volatile unsigned     var1;
volatile unsigned     var2;

void    *update_thread (void *);

char    *progname = "mutex";

int main ()
{
    pthread_t           threadID [NumThreads];  // a place to hold the thread ID's
    pthread_attr_t      attrib;                 // scheduling attributes
    struct sched_param  param;                  // for setting priority
    int                 i, policy;

    var1 = var2 = 0;        /* initialize to known values */

    printf ("%s:  starting; creating threads\n", progname);

    /*
     *  we want to create the new threads using Round Robin
     *  scheduling, and a lowered priority, so set up a thread
     *  attributes structure.  We use a lower priority since these
     *  threads will be hogging the CPU
    */

    pthread_getschedparam( pthread_self(), &policy, &param );

    pthread_attr_init (&attrib);
    pthread_attr_setinheritsched (&attrib, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy (&attrib, SCHED_RR);
    param.sched_priority -= 2;      // drop priority a couple levels
    pthread_attr_setschedparam (&attrib, &param);

    /*
     *  create the threads.  As soon as each pthread_create
     *  call is done, the thread has been started.
    */

    for (i = 0; i < NumThreads; i++) {
        pthread_create (&threadID [i], &attrib, &update_thread, NULL );
    }

    /*
     *  let the other threads run for a while
    */

    sleep (20);

    /*
     *  and then kill them all
    */

    printf ("%s:  stopping; cancelling threads\n", progname);

    for (i = 0; i < NumThreads; i++) {
        pthread_cancel (threadID [i]);
    }

    printf ("%s:  all done, var1 is %u, var2 is %u\n", progname, var1, var2);
    fflush (stdout);
    sleep (1);
    exit (0);
}

/*
 *  the actual thread.
 *
 *  The thread ensures that var1 == var2.  If this is not the
 *  case, the thread sets var1 = var2, and prints a message.
 *
 *  Var1 and Var2 are incremented.
 *
 *  Looking at the source, if there were no "synchronization" problems,
 *  then var1 would always be equal to var2.  Run this program and see
 *  what the actual result is...
*/

void do_work()
{
    static volatile unsigned var3;

    var3++;
    /* For faster/slower processors, may need to tune this program by
     * modifying the frequency of this printf -- add/remove a 0
     */
    if ( !(var3 % 10000000) )
        printf ("%s: thread %d did some work\n", progname, pthread_self());
}

void *
update_thread (void *i)
{
    while (1) {
        if (var1 != var2) {
            printf ("%s:  thread %d, var1 (%u) is not equal to var2 (%u)!\n",
                    progname, pthread_self(), var1, var2);
            var1 = var2;
        }

        /* do some work here */
        do_work();

        var1++;
        //sched_yield(); /* for faster processors, to cause problem to happen */
        var2++;
    }
    return (NULL);
}

