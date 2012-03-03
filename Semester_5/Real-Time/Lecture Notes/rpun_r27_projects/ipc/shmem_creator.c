
/*
 *  shmemcreator.c
 *
 *  This module demonstrates shared memory and semaphores
 *  by creating some shared memory and putting something in it (including
 *  a semaphore structure).  It then posts to the semaphore to tell other
 *  processes that it is okay to read from the shared memory.
 *
 *  This one is meant to be run in tandem with shmemuser.c.
 *
 *  Run it as: shmemcreator shared_memory_object_name
 *  Example: shmemcreator /wally
 *
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

/* shmem.h contains the structure that is overlayed on the shared memory */
#include "shmem.h"

/*
 *  our global variables.
*/

char        *progname = "shmem_creator";

int main( int argc, char *argv[] )
{
    char    *text = "Text by shmem_creator.c";
    int     fd;
    shmem_t *ptr;
   
    if ( argc != 2 ) {
        printf( "ERROR: use: shmem_creator shared_memory_object_name\n" );
        printf( "Example: shmem_creator /wally\n" );
        exit( EXIT_FAILURE );
    }
    
    /* create the shared memory object */
    
    fd = shm_open( argv[1], O_RDWR | O_CREAT, 0666 );
    if ( fd == -1 ) {
        printf( "%s: error creating the shared memory object '%s': %s\n",
                progname, argv[1], strerror(errno) );
        exit( EXIT_FAILURE );
    }
    
    /* set the size of the shared memory object */
    
    ftruncate( fd, sizeof(shmem_t) );
    
    /* get a pointer to a piece of the shared memory */
    
    ptr = mmap( 0, sizeof(shmem_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );

    /* don't need fd anymore, so close it */
    close( fd );

    /*
     * initialize the semaphore
     * The 1 means it can be shared between processes.  The 0 is the
     * count, 0 meaning sem_wait() calls will block until a sem_post()
     * is done.
     */
    sem_init( &ptr->semaphore, 1, 0 );
    
    strcpy( ptr->text, text ); /* write to the shared memory */
    
    printf( "%s: Shared memory created and semaphore initialized to 0.\n"
            "%s: Wrote text '%s' to shared memory.\n"
            "%s: Sleeping for 30 seconds.  While this program is sleeping\n"
            "%s: run 'shmem_user %s'.\n",
            progname, progname, ptr->text, progname, progname, argv[1] );
    sleep( 30 );
    
    printf( "%s: Woke up.  Now posting to the semaphore.\n", progname );
    sem_post( &ptr->semaphore );
    

    /* another delay for people to look at things */
    sleep( 300 );

    munmap( ptr, sizeof(shmem_t) );
    shm_unlink( argv[1] );
    
    return EXIT_SUCCESS;
}
