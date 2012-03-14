/*
 * File Name:     server.c
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
 * Description:	  Waits until it recieves an x and y value, and returns a product to the client
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <unistd.h>
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
	int rcvid1;
	union my_msg msg1;
	int status1;

	FILE * log = fopen("prod_server.log", "w");

	//Give the process a name
	attach = name_attach(NULL, SERVER_NAME, 0);
	printf("Now receiving messages...\n");
	fprintf(log, "Now receiving messages...\n");
	while (1) {

		//Recieve message from client
		rcvid1 = MsgReceive(attach->chid, &msg1, sizeof msg1, NULL);

		if (rcvid1 == 0){
			if (msg1.pulse.code == EXIT_PULSE_CODE){
				printf("Received exit pulse...shutting down\n");
				fprintf(log, "Received exit pulse...shutting down\n");
				break;
			}
		}
		msg1.msg.product = calculate_product(msg1.msg.x, msg1.msg.y);
		status1 = MsgReply(rcvid1, 0, &msg1.msg.product, sizeof msg1.msg.product);

	}

	printf("Server now exiting\n");
	//Make sure to free up resources
	fclose(log);
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

//eof: server.c
