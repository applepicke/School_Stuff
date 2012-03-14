/*
 * File Name:     server.c
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
 * Subject Line:  CST 8244, F11, Lab 3
 * Description:	  Waits until it recieves an x and y value, and returns a product to the client
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "prod.h"

int calculate_product(int x, int y);

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
	name_attach_t *attach;
	int rcvid1, rcvid2;
	int x = 0, y = 0, result;
	int status1, status2;

	//Give the process a name
	attach = name_attach(NULL, SERVER_NAME, 0);

	//Make sure we are successful
	if(attach->chid == -1)
	{
		perror("ChannelCreate()");
		exit(EXIT_FAILURE);
	} else {
		printf( "Channel successfully created\n" );
	}

	//Recieve message from client
	rcvid1 = MsgReceive(attach->chid, &x, sizeof x, NULL);
	rcvid2 = MsgReceive(attach->chid, &y, sizeof y, NULL);

	//Make sure nothing bad happened
	if (rcvid1 == -1 || rcvid2 == -1) {
		perror("MsgReceive");
	}

	printf("X is: %d\nY is: %d\n", x, y);
	result = calculate_product(x, y);

	printf("Result is %d\n", result);

	status1 = MsgReply(rcvid1, 0, &result, sizeof result);
	status2 = MsgReply(rcvid2, 0, &result, sizeof result);

	if (status1 == -1 || status2 == -1) {
		perror("MsgReply");
	}

	//Make sure to free up resources
	name_detach(attach, 0);
	return 0;
}

/********************************************************************************************
 * Function Name        calculate_product()
 * Version              1.0
 * Author               William Collins
 * Purpose				calculates the product of two numbers;
 * Inputs               x and y values to be multiplied
 * Outputs              The product of the x and y values
 *********************************************************************************************/
int calculate_product(int x, int y)
{
	return x * y;
}

