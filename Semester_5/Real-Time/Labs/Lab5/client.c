/*
 * File Name:     client.c
 * version:       1.0
 * Author:        William Collins
 * Date:          1/30/2012
 * Assignment:    Lab #4
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      2/2/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Lab 4
 * Description:	  Sends an x and y value to the server, and recieves a product in response
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <unistd.h>
#include "prod.h"

void *run_thread1(void *);
void *run_thread2(void *);

struct prod msg;	//Message to hold variables and product

/********************************************************************************************
 * Function Name        main()
 * Version              1.0
 * Author               William Collins
 * Purpose
 * Inputs               command line arguments
 * Outputs              Returns an integer, '0' on successful completion, '1' if an error
 *                      occurred.
 *********************************************************************************************/
int main(int argc, char *argv[]) {

    pthread_t           t1, t2;  // a place to hold the thread ID's
    pthread_attr_t      attrib;                 // scheduling attributes
    struct sched_param  param;                  // for setting priority
    int policy;

    /*
     * Create the new threads using Round Robin scheduling. The thread attribute structure
     * needs to be set up for creation.
     */

    pthread_getschedparam( pthread_self(), &policy, &param );

    pthread_attr_init (&attrib);
    pthread_attr_setinheritsched (&attrib, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy (&attrib, SCHED_RR);
    param.sched_priority = 10;	// we don't want a very high priority
    pthread_attr_setschedparam (&attrib, &param);

	//Assign default values
	msg.x = rand();
	msg.y = rand();

	pthread_create(&t1, &attrib, run_thread1, NULL);
	pthread_create(&t2, &attrib, run_thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return EXIT_SUCCESS;
}

void *run_thread1(void *param){
	int coid;
	int status;

	//Connect to the server
	printf("Thread 1: Connecting to server %s...\n",SERVER_NAME);
	coid = name_open(SERVER_NAME, 0);

	//Wait a quick second
	delay(1000);

	//Determine if the connection was successful
	if(-1 == coid) {   //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		exit(EXIT_FAILURE);
	} else {
		printf( "Successfully connected.\n");
	}

	//Send the message to server and get the reply
	status = MsgSend(coid, &msg.x, sizeof msg.x, &msg.product, sizeof msg.product);

	//Check for communication errors
	if(-1 == status) {   //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	} else {
		printf( "The product of %d and %d is %d\n", msg.x, msg.y, msg.product );
	};

	//Make sure to close resources
	name_close(coid);
	return NULL;
}

void *run_thread2(void *param){
	int coid;
	int status;

	//Connect to the server
	printf("Thread 2: Connecting to server %s...\n",SERVER_NAME);
	coid = name_open(SERVER_NAME, 0);

	//Wait a quick second
	delay(1000);

	//Determine if the connection was successful
	if(-1 == coid) {   //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		exit(EXIT_FAILURE);
	} else {
		printf( "Successfully connected.\n");
	}

	//Send the message to server and get the reply
	status = MsgSend(coid, &msg.y, sizeof msg.y, &msg.product, sizeof msg.product);

	//Check for communication errors
	if(-1 == status) {   //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	} else {
		printf( "The product of %d and %d is %d\n", msg.x, msg.y, msg.product );
	};

	//Make sure to close resources
	name_close(coid);
	return NULL;
}
