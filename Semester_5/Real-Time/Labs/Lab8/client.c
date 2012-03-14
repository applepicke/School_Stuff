/*
 * File Name:     client.c
 * version:       1.0
 * Author:        William Collins
 * Date:          1/30/2012
 * Assignment:    Lab #6
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      2/13/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Lab 6
 * Description:	  Sends an x and y value to the server, and recieves a product in response
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/netmgr.h>
#include <unistd.h>
#include "prod.h"

#define MY_PULSE_CODE   _PULSE_CODE_MINAVAIL

typedef union {
        struct _pulse   pulse;
        /* your other message structures would go
           here too */
} my_message_t;


void *run_thread1(void *);
void *run_thread2(void *);

struct prod msg1;	//Message to hold variables and product
struct prod msg2;

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

	pthread_create(&t1, &attrib, run_thread1, NULL);
	pthread_create(&t2, &attrib, run_thread2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return EXIT_SUCCESS;
}

void *run_thread1(void *param){
	int coid;
	int status;



	struct sigevent         event;
	struct itimerspec       itime;
	timer_t                 timer_id;
	int                     chid;
	int                     rcvid;
	my_message_t            msg;

	chid = ChannelCreate(0);

	event.sigev_notify = SIGEV_PULSE;
	event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0,
			chid,
			_NTO_SIDE_CHANNEL, 0);
	event.sigev_priority = getprio(0);
	event.sigev_code = MY_PULSE_CODE;
	timer_create(CLOCK_REALTIME, &event, &timer_id);

	itime.it_value.tv_sec = 1;
	/* 500 million nsecs = .5 secs */
	itime.it_value.tv_nsec = 250000000;
	itime.it_interval.tv_sec = 1;
	/* 500 million nsecs = .5 secs */
	itime.it_interval.tv_nsec = 250000000;
	timer_settime(timer_id, 0, &itime, NULL);

	/*
	 * As of the timer_settime(), we will receive our pulse
	 * in 1.5 seconds (the itime.it_value) and every 1.5
	 * seconds thereafter (the itime.it_interval)
	 */

	//Connect to the server
	printf("Thread 1: Connecting to server %s...\n",SERVER_NAME);
	coid = name_open(SERVER_NAME, 0);

	//Determine if the connection was successful
	if(-1 == coid) {   //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		exit(EXIT_FAILURE);
	} else {
		printf( "Successfully connected.\n");
	}

	while(1) {
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if (rcvid == 0) { /* we got a pulse */
			if (msg.pulse.code == MY_PULSE_CODE) {

				msg1.x = rand();
				msg1.y = rand();

				//Send the message to server and get the reply
				status = MsgSend(coid, &msg1, sizeof msg1, &msg1.product, sizeof msg1.product);

				//Check for communication errors
				if(-1 == status) {   //was there an error sending to server?
					perror("MsgSend");
					exit(EXIT_FAILURE);
				} else {
					printf( "Thread 1: The product of %d and %d is %d\n", msg1.x, msg1.y, msg1.product );
				};

			} /* else other pulses ... */
		} /* else other messages ... */
	}

	//Make sure to close resources
	name_close(coid);
	return NULL;
}

void *run_thread2(void *param){
	int coid;
	int status;
	struct sigevent         event;
	struct itimerspec       itime;
	timer_t                 timer_id;
	int                     chid;
	int                     rcvid;
	my_message_t            msg;

	chid = ChannelCreate(0);

	event.sigev_notify = SIGEV_PULSE;
	event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0,
			chid,
			_NTO_SIDE_CHANNEL, 0);
	event.sigev_priority = getprio(0);
	event.sigev_code = MY_PULSE_CODE;
	timer_create(CLOCK_REALTIME, &event, &timer_id);

	itime.it_value.tv_sec = 1;
	/* 500 million nsecs = .5 secs */
			itime.it_value.tv_nsec = 750000000;
	itime.it_interval.tv_sec = 1;
	/* 500 million nsecs = .5 secs */
	itime.it_interval.tv_nsec = 750000000;
	timer_settime(timer_id, 0, &itime, NULL);

	//Connect to the server
	printf("Thread 2: Connecting to server %s...\n",SERVER_NAME);
	coid = name_open(SERVER_NAME, 0);

	//Determine if the connection was successful
	if(-1 == coid) {   //was there an error attaching to server?
		perror("ConnectAttach"); //look up error code and print
		exit(EXIT_FAILURE);
	} else {
		printf( "Successfully connected.\n");
	}

	/*
	 * As of the timer_settime(), we will receive our pulse
	 * in 1.5 seconds (the itime.it_value) and every 1.5
	 * seconds thereafter (the itime.it_interval)
	 */
	while(1) {
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if (rcvid == 0) { /* we got a pulse */
			if (msg.pulse.code == MY_PULSE_CODE) {
				msg2.x = rand();
				msg2.y = rand();

				//Send the message to server and get the reply
				status = MsgSend(coid, &msg2, sizeof msg2, &msg2.product, sizeof msg2.product);

				//Check for communication errors
				if(-1 == status) {   //was there an error sending to server?
					perror("MsgSend");
					exit(EXIT_FAILURE);
				} else {
					printf( "Thread 2: The product of %d and %d is %d\n", msg2.x, msg2.y, msg2.product );
				};


			} /* else other pulses ... */
		} /* else other messages ... */
	}

	//Make sure to close resources
	name_close(coid);
	return NULL;
}

// eof: client.c
