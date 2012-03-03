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
#include "prod.h"

int main( int argc, char *argv[] )
{
    int     fd;
    struct prod *ptr;
    struct prod prods[10];
    int coid;

	coid = name_open(SERVER_NAME, 0);
	printf("Ready to send\n");

    //Open file and read in values
    int i = 0;
    FILE *num_file = fopen("lab_7_data.txt", "r");
    while (num_file != NULL && !feof(num_file)){
    	fscanf(num_file, "%d,%d\n", &prods[i].x, &prods[i].y);
    	i++;
    }
    fclose(num_file);
    printf("Numbers successfully loaded!\n");

    /* create the shared memory object */

    fd = shm_open( NAME, O_RDWR | O_CREAT, 0666 );
    if ( fd == -1 ) {
        printf( "error creating the shared memory object");
        exit( EXIT_FAILURE );
    }
    ftruncate(fd, sizeof(prods));
    /* get a pointer to a piece of the shared memory */
    ptr = mmap( 0, sizeof(prods), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    printf("shared memory created!\n");

    for(i = 0; i < 10; i++){
     	printf("%d * %d = %d\n", prods[i].x, prods[i].y, prods[i].x * prods[i].y);
     }

    for (i = 0; i < 10; i++){
    	ptr[i].x = prods[i].x;
    	ptr[i].y = prods[i].y;
    }


    struct msg msg;
    MsgSend(coid, &msg, sizeof(struct msg), &msg, sizeof(struct msg));
    printf("Sending message to server\n");


    close( fd );
    munmap( ptr, sizeof(prods) );
    printf("unmapped!\n");
    name_close(coid);

    return EXIT_SUCCESS;
}
// eof: shmem_cr
