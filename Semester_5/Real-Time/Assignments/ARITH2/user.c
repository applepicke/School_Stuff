/*
 * File Name:     user.c
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
 * Description:   Performs calculations on data in shared memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/netmgr.h>
#include "arith.h"

//function declarations
void *sum(void *arg);
void *diff(void *arg);
void *divide(void *arg);
void *mult(void *arg);
void *totalsum(void *arg);
void *average(void *arg);

//Globals
arith *values;
FILE *results;

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
	pthread_t sum_t, diff_t, div_t, mult_t, totalsum_t, average_t;
	pthread_attr_t attrib, sum_att, diff_att;
	struct sched_param  param;
	int i;

	name_attach_t *attach;
	int rcvid;
	struct _pulse pulse;

	int fd;

	//Open the results file for use by the threads
	results = fopen("A2-output.txt", "w");

	if (results == NULL){
		printf("Cannot open results file for writing... Aborting.\n");
		exit( EXIT_FAILURE );
	}

	//Open the file that will hold the array of arithmetic structures
	FILE *array = fopen("1000-array.txt", "w");
	if (array == NULL){
		printf("Can't open the file to write array. Getting out of here..\n");
		exit( EXIT_FAILURE );
	}

	//Set regular thread sttributes
	pthread_getschedparam( pthread_self(), NULL, &param );
	pthread_attr_init (&attrib);
	pthread_attr_setinheritsched (&attrib, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy (&attrib, SCHED_RR);
	param.sched_priority = 10;
	pthread_attr_setschedparam (&attrib, &param);

	//Set the sum and diff priorities
	pthread_attr_init(&sum_att);
	pthread_attr_setinheritsched (&sum_att, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy (&sum_att, SCHED_RR);
	param.sched_priority = 20;
	pthread_attr_setschedparam (&sum_att, &param);

	pthread_attr_init(&diff_att);
	pthread_attr_setinheritsched (&diff_att, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy (&diff_att, SCHED_RR);
	param.sched_priority = 18;
	pthread_attr_setschedparam (&diff_att, &param);

	printf("Attaching a name to the process..\n");
	//Give the process a name
	attach = name_attach(NULL, SERVER_NAME, 0);

	//Recieve message from producer
	printf("Waiting for pulse..\n");
	rcvid = MsgReceivePulse(attach->chid, &pulse, sizeof(pulse), NULL);

	//Make sure it is the pulse we want
	if (rcvid != 0 || pulse.code != BEGIN_PULSE){
		printf("Message received is not the begin pulse...exiting...\n");
		return 1;
	}
	printf("Pulse received, opening shared memory..\n");

	// Access the shared memory
	fd = shm_open( NAME, O_RDWR, 0 );
	if ( fd == -1 ) {
		printf( "error opening the shared memory object\n" );
		exit( EXIT_FAILURE );
	}

	// get a pointer to a piece of the shared memory
	values = mmap( 0, sizeof(arith) * 1000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
	if( values == MAP_FAILED )
	{
		perror( "mmap" );
		exit( EXIT_FAILURE );
	}
	printf("Memory is now mapped.\n");

	printf("Calculation threads are now being started...\n");
	//Create threads
	pthread_create(&sum_t, &sum_att, sum, NULL);
	pthread_create(&diff_t, &diff_att, diff, NULL);
	pthread_create(&div_t, &attrib, divide, NULL);
	pthread_create(&mult_t, &attrib, mult, NULL);

	//Wait for threads to finish
	pthread_join(sum_t, NULL);
	pthread_join(diff_t, NULL);
	pthread_join(div_t, NULL);
	pthread_join(mult_t, NULL);

	printf("Calculation threads have finished, now calculating totals..\n");
	pthread_create(&totalsum_t, &attrib, totalsum, NULL);
	pthread_create(&average_t, &attrib, average, NULL);
	pthread_join(totalsum_t, NULL);
	pthread_join(average_t, NULL);

	printf("Writing value datastructures to filesystem..\n");

	for (i = 0; i < 1000; i++){
		fprintf(array, "%lf,%lf,%lf,%lf,%lf,%lf\n", values[i].operand1,
													values[i].operand2,
													values[i].sum,
													values[i].difference,
													values[i].quotient,
													values[i].product);
	}

	printf("All threads have finished..releasing resources..\n");
	fclose(results);
	fclose(array);
	name_detach(attach, 0);
	munmap(values, sizeof(arith) * 1000);
	return 0;
}

/********************************************************************************************
 * Function Name        sum()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the sum of all arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *sum(void *arg){
	struct sigevent         event;
	struct itimerspec       itime;
	timer_t                 timer_id;
	struct _pulse 			pulse;
	int                     chid, rcvid, i;

	chid = ChannelCreate(0);

	event.sigev_notify = SIGEV_PULSE;
	event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0, chid,_NTO_SIDE_CHANNEL, 0);
	event.sigev_priority = getprio(0);
	event.sigev_code = SUM_PULSE;
	timer_create(CLOCK_REALTIME, &event, &timer_id);

	itime.it_value.tv_nsec = 200000000;
	itime.it_interval.tv_nsec = 200000000;
	timer_settime(timer_id, 0, &itime, NULL);

	rcvid = MsgReceive(chid, &pulse, sizeof(pulse), NULL);
	if (rcvid != 0 || pulse.code != SUM_PULSE) {
		printf("Getting a weird pulse. Weird.\n");
		return NULL;
	}

	for (i = 0; i < 1000; i++){
		values[i].sum = values[i].operand1 + values[i].operand2;
	}
	printf("Sum thread has finished.\n");

	return NULL;
}

/********************************************************************************************
 * Function Name        diff()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the diff of all arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *diff(void *arg){
	struct sigevent         event;
	struct itimerspec       itime;
	timer_t                 timer_id;
	struct _pulse 			pulse;
	int                     chid, rcvid, i;

	chid = ChannelCreate(0);

	event.sigev_notify = SIGEV_PULSE;
	event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0, chid,_NTO_SIDE_CHANNEL, 0);
	event.sigev_priority = getprio(0);
	event.sigev_code = DIFF_PULSE;
	timer_create(CLOCK_REALTIME, &event, &timer_id);

	itime.it_value.tv_nsec = 150000000;
	itime.it_interval.tv_nsec = 150000000;
	timer_settime(timer_id, 0, &itime, NULL);

	rcvid = MsgReceive(chid, &pulse, sizeof(pulse), NULL);
	if (rcvid != 0 || pulse.code != DIFF_PULSE) {
		printf("Getting a weird pulse. Weird.\n");
		return NULL;
	}

	for (i = 0; i < 1000; i++){
		values[i].difference = values[i].operand1 - values[i].operand2;
	}
	printf("Difference thread has finished.\n");

	return NULL;
}

/********************************************************************************************
 * Function Name        divide()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the quotient of all arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *divide(void *arg){
	int i;

	//Perform division
	for (i = 0; i < 1000; i++){
		if (values[i].operand1 != 0 && values[i].operand2 != 0){
			values[i].quotient = values[i].operand1 / values[i].operand2;
		}
		else {
			values[i].quotient = 0.0f;
		}
	}

	printf("Divide thread has finished.\n");
	return NULL;
}
/********************************************************************************************
 * Function Name        mult()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the product of all arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *mult(void *arg){
	int i;

	//Perform multiplication
	for (i = 0; i < 1000; i++){
		values[i].product = values[i].operand1 * values[i].operand2;
	}
	printf("Multiply thread has finished.\n");

	return NULL;
}

/********************************************************************************************
 * Function Name        sum()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the sum of all values in the arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *totalsum(void *arg){
	int i;
	for (i = 0; i < 1000; i++){
		float sum = values[i].difference +
					values[i].operand1 +
					values[i].operand2 +
					values[i].product +
					values[i].quotient +
					values[i].sum;
		fprintf(results, "%d: totalsum = %lf\n", i, sum);
	}

	printf("Finished calculating total sums.\n");

	return NULL;
}

/********************************************************************************************
 * Function Name        average()
 * Version              1.0
 * Author               William Collins
 * Purpose				To calculate the average of all arith structures
 * Inputs               arguments passed to the thread
 * Outputs              NULL
 *********************************************************************************************/
void *average(void *arg){
	int i;
	for (i = 0; i < 1000; i++){
		float avg = (values[i].difference +
					values[i].operand1 +
					values[i].operand2 +
					values[i].product +
					values[i].quotient +
					values[i].sum) / 6;
		fprintf(results, "%d: average = %lf\n", i, avg);
	}
	printf("Finished calculating averages.\n");

	return NULL;
}

//EOF: user.c
