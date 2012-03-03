/*
 * File Name:     Arith-Lab2.c
 * version:       1.0
 * Author:        William Collins
 * Date:          1/16/2012
 * Assignment:    Lab #2
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      1/18/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Lab 2
 * Description:   	Set up four threads that perform different arithmentic
 * 					operations on a data file.
 */
#include <stdio.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * The number of threads to run simultaneously
 */
#define NUM_THREADS 4
#define MAX_NUMS_IN_FILE 1000
#define ADD 0
#define SUB 1
#define MULT 2
#define DIV 3

/*
 * Globals
 */
FILE *logfile;

/*
 * Function declarations
 */
double add(int, int);
double subs(int, int);
double mult(int, int);
double divide(int, int);
void *(*get_thread_function(int))(void *);
void *calculate(int *mode);

/********************************************************************************************
 * Function Name        main()
 * Version              1.0
 * Author               William Collins
 * Purpose
 * Inputs               none
 * Outputs              Returns an integer, '0' on successful completion, '1' if an error
 *                      occurred.
 *********************************************************************************************/
int main() {

    pthread_t           threadID[NUM_THREADS];  // a place to hold the thread ID's
    int					t_num[NUM_THREADS];		// distinguishes between threads
    pthread_attr_t      attrib;                 // scheduling attributes
    struct sched_param  param;                  // for setting priority
    int                 i, policy;
	logfile = fopen("Lab2.log", "w+");	// log file

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

    //Create threads
	for (i = 0; i < NUM_THREADS; i++){
		t_num[i] = i;
		pthread_create(&threadID[i], &attrib, calculate, t_num+i);
		delay(1000);
	}

	//Wait for threads to finish
	for (i = 0; i < NUM_THREADS; i++){
		pthread_join(threadID[i], NULL);
	}

	fclose(logfile);
	return EXIT_SUCCESS;
}

//Add two numbers
double add(int num1, int num2){
	return (double)num1 + (double)num2;
}

//Subtract two numbers
double subs(int num1, int num2){
	return (double)num1 - (double)num2;
}

//Multiply two numbers
double mult(int num1, int num2){
	return (double)num1 * (double)num2;
}

//Divide two numbers
double divide(int num1, int num2){
	if (num1 == 0 || num2 == 0) return 0.0;
	return (double)num1 / (double)num2;
}

/********************************************************************************************
 * Function Name        calculate()
 * Version              1.0
 * Author               William Collins
 * Purpose
 * Inputs               mode - tells the function which operation to perform
 * Outputs              Returns a null void pointer.
 *********************************************************************************************/
void *calculate(int *mode){
	int i, num1 = 0, num2 = 0;
	double total = 0.0;
	char *type;
	FILE *data_file = fopen("arith_data.txt", "r");
	double (*calc_fn)(int,int);

	//Determine which calculation to perform
	if (*mode == ADD) {
		calc_fn = add;
		type = "sum";
	}
	if (*mode == SUB) {
		calc_fn = subs;
		type = "difference";
	}
	if (*mode == MULT) {
		calc_fn = mult;
		type = "product";
	}
	if (*mode == DIV) {
		calc_fn = divide;
		type = "quotient";
	}

	for (i = 0; i < MAX_NUMS_IN_FILE; i++){
		fscanf(data_file, "%d,%d", &num1, &num2);
		total += calc_fn(num1, num2);
	}

	printf("Total of %s: %.4lf\n", type, total);
	fprintf(logfile, "Total of %s: %.4lf\n", type, total);
	printf("Average of %s: %.4lf\n", type, total / (double)MAX_NUMS_IN_FILE);
	fprintf(logfile, "Average of %s: %.4lf\n", type, (total / (double)MAX_NUMS_IN_FILE));
	fclose(data_file);

	return (NULL);
}

