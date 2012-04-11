#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <semaphore.h>
#include <signal.h>
#include "prod.h"

void sig_handler(int sigval){
	printf("Recieved signal %d...cannot increment semaphore.\n", sigval);
	exit(0);
}

int main( int argc, char *argv[] )
{
    int     fd;
    name_attach_t *attach;
    struct prod *ptr;
    struct msg msg;
	attach = name_attach(NULL, SERVER_NAME, 0);
	printf("ready to receive message\n");

	//Recieve message
    int rcvid = MsgReceive(attach->chid, &msg, sizeof( struct msg), NULL);
    printf("received message from creator\n");

    /* open the shared memory object */
    fd = shm_open( NAME, O_RDWR, 0 );
    if ( fd == -1 ) {
        printf( "error opening the shared memory object\n" );
        exit( EXIT_FAILURE );
    }

    /* get a pointer to a piece of the shared memory */
    ptr = mmap( 0, sizeof(ptr), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    if( ptr == MAP_FAILED )
    {
    	perror( "mmap" );
    	exit( EXIT_FAILURE );
    }
    printf("Got a chunk of memory\n");

    int i;
    for(i = 0; i < 10; i++){
    	printf("%d * %d = %d\n", ptr[i].x, ptr[i].y, ptr[i].x * ptr[i].y);
    }

    MsgReply(rcvid, 1, NULL, 0);
    printf("Replying to shmem_cr\n");

    /* don't need fd anymore */
    close( fd );

    munmap( ptr, sizeof(ptr) );
    signal(SIGSEGV, sig_handler);
    sem_post(NULL);

    printf("unmapped!\n");
    name_detach(attach, 0);

    return EXIT_SUCCESS;
}



//eof:shmem_usr
