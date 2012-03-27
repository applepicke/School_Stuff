/*
 * File Name:     producer.c
 * version:       1.0
 * Author:        William Collins
 * Date:          3/22/2012
 * Assignment:    Assignment 2
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      3/30/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Asgn 2
 * Description: Reads a data file, and writes its values to shared memory
 * 				to be read elsewhere.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "arith.h"


/********************************************************************************************
 * Function Name        main()
 * Version              1.0
 * Author               William Collins
 * Purpose
 * Inputs
 * Outputs              Returns an integer, '0' on successful completion, '1' if an error
 *                      occurred.
 *********************************************************************************************/
int main(){
	int fd;
	arith *values;	//Structures to store data values
	int coid;
	int i = 0;


	FILE *data = fopen("data.csv", "r");
	if (data == NULL){
		printf("Can not open file.\n");
		return 1;
	}
	printf("File opened for reading..\n");

	//Open up shared memory object
	fd = shm_open( NAME, O_RDWR | O_CREAT, 0666 );
	if ( fd == -1 ) {
		printf( "error opening the shared memory object\n" );
	    exit( EXIT_FAILURE );
	}

	ftruncate(fd, sizeof(arith) * 1000);

    /* get a pointer to a piece of the shared memory */
    values = mmap( NULL, sizeof(arith) * 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    if( values == MAP_FAILED )
    {
    	perror( "mmap" );
    	exit( EXIT_FAILURE );
    }
    printf("Shared memory ready to write..\n");

	//Get value pairs from the data file
	while (i < 1000){
		fscanf(data, "%lf,%lf", &values[i].operand1, &values[i].operand2);
		i++;
	}
	printf("Finished writing to shared memory.\n");
	printf("Connecting to user..\n");
    //Connect to user and send pulse
    coid = name_open(SERVER_NAME, 0);
    if (coid == -1){
    	perror("Connect to user");
    	exit(0);
    }
    MsgSendPulse(coid, getprio(0), BEGIN_PULSE, 0);
    printf("Pulse has been sent to the user.\n");

    //Release everything we have used so far
    fclose(data);
    close( fd );
    name_close(coid);
    munmap( values, sizeof(arith) * 1000 );
    printf("Finished releasing resources.\n");

	return 0;
}
//EOF: producer.c
