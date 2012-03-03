/*
 * File Name:     arithd.c
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
 * Description:   Waits for arithmetic operands to be send, processes them,
 * 				  and sends back the result.
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "arith.h"

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
	int rcvid;
	arith stmt;
	int status;

	//Give the process a name
	attach = name_attach(NULL, SERVER_NAME, 0);

	//Make sure we are successful
	if(attach->chid == -1)
	{
		perror("ChannelCreate()");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Ready to accept connections...\n");
	}

	while (1) {
		//Recieve message from client
		rcvid = MsgReceive(attach->chid, &stmt, sizeof stmt, NULL);

		//Make sure nothing bad happened
		if (rcvid == -1) {
			perror("MsgReceive");
		}

		//Perform calculation on operands
		if (stmt.operator == '+'){
			stmt.result = stmt.operand1 + stmt.operand2;
		}
		else if (stmt.operator == '-'){
			stmt.result = stmt.operand1 - stmt.operand2;
		}
		else if (stmt.operator == '/'){
			if (stmt.operand1 == 0 || stmt.operand2 == 0)
				stmt.result = 0;
			else {
				stmt.result = stmt.operand1 / stmt.operand2;
			}
		}
		else if (stmt.operator == '*'){
			stmt.result = stmt.operand1 * stmt.operand2;
		}

		//Reply with the calculated value
		status = MsgReply(rcvid, 0, &stmt, sizeof stmt);
	}

	//Make sure to free up resources
	name_detach(attach, 0);
	return 0;
}

//eof: arithd.c
