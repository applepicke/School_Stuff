/*
 * File Name:     Lab3.c
 * version:       1.0
 * Author:        William Collins
 * Date:          1/23/2012
 * Assignment:    Lab #3
 * Course:        Real Time Programming
 * Code:          CST8244
 * Professor:     Saif Terai
 * Due Date:      1/25/2012
 * Submission
 * Type:          Email Submission
 * Destination
 * Address:       terais@algonquincollege.com
 * Subject Line:  CST 8244, F11, Lab 3
 * Description:	  Alternately writes random numbers to a file from separate threads.
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/* functions called by threads WITH mutex */
void operand1_mutex();
void operand2_mutex();

//Globals
pthread_mutex_t filemutex;


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
	pthread_t t1;
	pthread_t t2;

	//Initialize the mutex
	pthread_mutex_init(&filemutex, NULL);

	printf("Operand mixer\n");
	printf("\nStarting threads WITHOUT mutex\n");
	pthread_create( &t1, NULL,(void*) &operand1_mutex, NULL );
	pthread_create( &t2, NULL,(void*) &operand2_mutex, NULL );

	pthread_join( t1, NULL );
    pthread_join( t2, NULL );
    printf( "Completed threads t1 and t2\n" );
	return EXIT_SUCCESS;
}
/********************************************************************************************
 * Function Name        calculate()
 * Version              1.0
 * Author               William Collins
 * Purpose				Prints two random numbers to file
 * Inputs               none
 * Outputs              none
 *********************************************************************************************/
void operand1_mutex() {
	FILE *outfile;
	int i, rand1, rand2;

	if( ( outfile = fopen( "out_nomutex.log", "a" ) ) == NULL ) {
		printf( "\nCannot open file\n" );
		exit( EXIT_FAILURE );
	}

	for( i = 0; i < 400; i++ ) {
		rand1 = rand();
		rand2 = rand();
		pthread_mutex_lock(&filemutex);
		fprintf( outfile, "t1 %d, ", rand1 );
		fflush( outfile );
		delay(5);
		fprintf( outfile, "t1 %d\n", rand2 );
		delay(55);
		pthread_mutex_unlock(&filemutex);
		fflush( outfile );
		if( i % 40 == 0 ) printf( "." );

	}
	fclose( outfile );

}

/********************************************************************************************
 * Function Name        calculate()
 * Version              1.0
 * Author               William Collins
 * Purpose				Prints two random numbers to file
 * Inputs               none
 * Outputs              none
 *********************************************************************************************/
void operand2_mutex() {
	FILE *outfile;
	int i, rand1, rand2;

	if( ( outfile = fopen( "out_nomutex.log", "a" ) ) == NULL ) {
		printf( "Cannot open file\n" );
		exit( EXIT_FAILURE );
	}
	for( i = 0; i < 400; i++ ) {
		rand1 = rand();
		rand2 = rand();
		pthread_mutex_lock(&filemutex);
		fprintf( outfile, "t2 %d, ", rand1 );
		fflush( outfile );
		delay( 5 );
		fprintf( outfile, "t2 %d\n", rand2 );
		delay( 55 );
		pthread_mutex_unlock(&filemutex);
		fflush( outfile );
	}
	fclose( outfile );
}
