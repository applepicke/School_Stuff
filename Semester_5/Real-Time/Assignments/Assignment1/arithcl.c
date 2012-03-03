/*
 * File Name:     arithcl.c
 * version:       1.0
 * Author:        William Collins
 * Date:          2/14/2012
 * Assignment:    Assignment 1
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      2/17/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Asgn 1
 * Description: Reads a file, sending operations to the server to be completed
 * 				and returned with results.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "arith.h"

//function declarations
void *snd_stmt(void*);

//globals
char ops[] = { '+', '-', '/', '*' };
pthread_mutex_t filemutex; //mutex for the log file
FILE *flog;  //The log file that the threads will write to


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

	pthread_t           t_add, t_sub, t_div, t_mult;  // a place to hold the thread ID's
	pthread_attr_t      attrib;                 // scheduling attributes
	struct sched_param  param;                  // for setting priority
	int policy;

	//Get the file ready to write to
	flog = fopen("arith.log", "w");
	if (flog == NULL){
		perror("Log File");
		exit(EXIT_FAILURE);
	}

	pthread_getschedparam( pthread_self(), &policy, &param );
	pthread_attr_init (&attrib);
	pthread_attr_setinheritsched (&attrib, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy (&attrib, SCHED_RR);
	param.sched_priority = 10;	// default priority
	pthread_attr_setschedparam (&attrib, &param);

	//Get the mutex ready to use
	pthread_mutex_init(&filemutex, NULL);

	//My name, for I am the chosen one
	fprintf(flog, "Student Name: William Collins\n");

	//Launch each thread
	pthread_create(&t_add, &attrib, snd_stmt, &ops[0]);
	pthread_create(&t_sub, &attrib, snd_stmt, &ops[1]);
	pthread_create(&t_div, &attrib, snd_stmt, &ops[2]);
	pthread_create(&t_mult, &attrib, snd_stmt, &ops[3]);

	//Wait for each thread to finish
	pthread_join(t_add, NULL);
	pthread_join(t_sub, NULL);
	pthread_join(t_div, NULL);
	pthread_join(t_mult, NULL);

	printf("All threads have successfully completed!");

	//Clean up resources
	fclose(flog);
	pthread_mutex_destroy(&filemutex);

	return EXIT_SUCCESS;
}

/********************************************************************************************
 * Function Name        snd_stmt()
 * Version              1.0
 * Author               William Collins
 * Purpose				Sends arithmetic statements to the server
 * Inputs				The operation to be performed on the data
 * Outputs              NULL
 *********************************************************************************************/
void *snd_stmt(void *op){

	int coid;	//connection id
	int status; //return status
	arith stmt; //arithmetic statement to send

	//Open the data file for reading
	FILE *data = fopen("arith_data.txt", "r");
	if (data == NULL){
		perror("Data File");
		exit(EXIT_FAILURE);
	}

	//Connect to the server
	coid = name_open(SERVER_NAME, 0);

	//Determine if the connection was successful
	if(-1 == coid) {
		perror("ConnectAttach");
		exit(EXIT_FAILURE);
	}

	int scan;
	int line = 0;
	//Read the entire file sending values on each line
	while (!feof(data)){
		scan = fscanf(data, "%lf,%lf", &stmt.operand1, &stmt.operand2);
		line++;
		//Only perform the operation if scan returned properly
		if (scan == 2) {
			stmt.operator = *(char*)op;

			//Send the message to server and get the reply
			status = MsgSend(coid, &stmt, sizeof stmt, &stmt, sizeof stmt);

			//Check for communication errors
			if(status == -1) {
				perror("MsgSend");
				exit(EXIT_FAILURE);
			}

			//Write to log file when able
			pthread_mutex_lock(&filemutex);
			fprintf(flog, "line %d: op1 = %.2lf, op2 = %.2lf, op = '%c', result = %.3lf\n", line, stmt.operand1, stmt.operand2, stmt.operator,stmt.result );
			pthread_mutex_unlock(&filemutex);
		}
	}
	fclose(data);
	name_close(coid);

	return NULL;
}

//eof: arithcl.c
