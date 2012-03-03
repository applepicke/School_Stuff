
/*
 *  semex.c
 *
 *  This module demonstrates POSIX semaphores.
 *
 *  Operation:
 *      A counting semaphore is created, primed with 0 counts.
 *      Five consumer threads are started, each trying to obtain
 *      the semaphore.  
 *      A producer thread is created, which periodically posts
 *      the semaphore, unblocking one of the consumer threads.
 *
*/

#include <stdio.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <malloc.h>

/*
 *  our global variables, and forward references
*/

sem_t   *mySemaphore;

void    *producer (void *);
void    *consumer (void *);

char    *progname = "semex";

#define SEM_NAME "/Semex"

int main ()
{
    int     i;

// #define  Named
#ifdef  Named
    mySemaphore = sem_open (SEM_NAME, O_CREAT, S_IRWXU, 0);
    /* not sharing with other process, so immediately unlink */
    sem_unlink( SEM_NAME );
#else   // Named
    mySemaphore = malloc (sizeof (sem_t));
    sem_init (mySemaphore, 1, 0);
#endif  // Named

    for (i = 0; i < 5; i++) {
        pthread_create (NULL, NULL, consumer, (void *) i);
    }

    pthread_create (NULL, NULL, producer, (void *) 1);

    sleep (20);     // let the threads run
    printf ("%s:  main, exiting\n", progname);
    return 0;
}

/*
 *  producer
*/

void *
producer (void *i)
{
    while (1) {
        sleep (1);
        printf ("%s:  (producer %d), posted semaphore\n", progname, (int) i);
        sem_post (mySemaphore);
    }
    return (NULL);
}

/*
 *  consumer
*/

void *
consumer (void *i)
{
    while (1) {
        sem_wait (mySemaphore);
        printf ("%s:  (consumer %d) got semaphore\n", progname, (int) i);
    }
    return (NULL);
}

