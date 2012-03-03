/* Do NOT do the condition variable exercise in this source file.
 * Work in condvar.c instead.
 */
 
/*
 *  prodcons.c
 *
 *  This module demonstrates POSIX condition variables by
 *  way of a producer and consumer.  Since we only have
 *  two threads waiting for the signal, and at any given
 *  point one of them is running, we can just use the
 *  pthread_cond_signal call to awaken the other thread.
 *
*/

#include <stdio.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

/*
 *  our mutex and condition variable
*/

pthread_mutex_t     mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t      cond  = PTHREAD_COND_INITIALIZER;

/*
 *  our global variables.
*/

volatile int        state = 0;    // used as a state variable
volatile int        product = 0;  // the output of the producer

void    *producer (void *);
void    *consumer (void *);
void    do_producer_work (void);
void    do_consumer_work (void);

char    *progname = "prodcons";

int main ()
{
    pthread_create (NULL, NULL, consumer, NULL);
    pthread_create (NULL, NULL, producer, NULL);

    sleep (20);     // let the threads run
    printf ("%s:  main, exiting\n", progname);
    return 0;
}

/*
 *  producer
*/

void *
producer (void *arg)
{
    while (1) {
        pthread_mutex_lock (&mutex);
        while (state == 1) {
            pthread_cond_wait (&cond, &mutex);
        }
        printf ("%s:  produced %d, state %d\n", progname, ++product, state);
        state = 1;
        pthread_cond_signal (&cond);
        pthread_mutex_unlock (&mutex);
        do_producer_work ();
    }
    return (NULL);
}

/*
 *  consumer
*/

void *
consumer (void *arg)
{
    while (1) {
        pthread_mutex_lock (&mutex);
        while (state == 0) {
            pthread_cond_wait (&cond, &mutex);
        }
        printf ("%s:  consumed %d, state %d\n", progname, product, state);
        state = 0;
        pthread_cond_signal (&cond);
        pthread_mutex_unlock (&mutex);
        do_consumer_work ();
    }
    return (NULL);
}

void
do_producer_work (void)
{
    delay (100); // pretend to be doing something
}

void
do_consumer_work (void)
{
    delay (100); // pretend to be doing something
}
