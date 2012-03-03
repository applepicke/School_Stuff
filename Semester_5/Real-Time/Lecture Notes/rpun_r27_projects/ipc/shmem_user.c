
/*
 *  shmemuser.c
 *
 *  This module demonstrates shared memory and semaphores
 *  by opening some shared memory, waiting on a semaphore (whose
 *  semaphore structure is in the shared memory) and then printing out
 *  what it finds in the shared memory.
 *
 *  This one is meant to be run in tandem with shmemcreator.c.
 *
 *  Run it as: shmemuser shared_memory_object_name
 *  Example: shmemuser /wally
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

char        *progname = "shmem_user";

int main( int argc, char *argv[] )
{
    int     fd;
    shmem_t *ptr;
   
    if ( argc != 2 ) {
        printf( "ERROR: use: shmem_user shared_memory_object_name\n" );
        printf( "Example: shmem_user /wally\n" );
        exit( EXIT_FAILURE );
    }
    
    /* open the shared memory object */
    
    fd = shm_open( argv[1], O_RDWR, 0 );
    if ( fd == -1 ) {
        printf( "%s: error opening the shared memory object '%s': %s\n",
                progname, argv[1], strerror(errno) );
        exit( EXIT_FAILURE );
    }
    
    /* get a pointer to a piece of the shared memory */
    
    ptr = mmap( 0, sizeof(shmem_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    if( ptr == MAP_FAILED )
    {
    	perror( "mmap" );
    	exit( EXIT_FAILURE );
    }
    

    /* don't need fd anymore */
    close( fd );

    /* wait on the semaphore */
    
    printf( "%s: Waiting on the semaphore. \n Look at state in System information perspective.  This process should be SEM blocked.\n", progname );
    
    sem_wait( &ptr->semaphore );
    
    printf( "%s: The shared memory contains '%s'\n", progname, ptr->text );
    
    munmap( ptr, sizeof(shmem_t) );
    
    return EXIT_SUCCESS;
}
