////////////////////////////////////////////////////////////////////////////////
// client.c
//
// A QNX msg passing client.  It's purpose is to send a string of text to a
// server.  The server calculates a checksum and replies back with it.  The client
// expects the reply to come back as an int
//
// This program program must be started with commandline args.  
// See  if(argc != 4) below
//
// To complete the exercise, put in the code, as explained in the comments below
// Look up function arguments in the course book or the QNX documentation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>     // #define for ND_LOCAL_NODE is in here

#include "prod.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>

struct prod msg;

int main(int argc, char* argv[]) {
	int coid;         //Connection ID to server
	int status;       //status return value used for ConnectAttach and MsgSend
	int len;


	// look up name, rather than get it from command line	
	coid = name_open( SERVER_NAME, 0 );
	
	if(-1 == coid) {   //was there an error attaching to server?
		perror("name_open");
		exit(EXIT_FAILURE);
	}
	
	len = sizeof( msg );
	printf( "message length is %d\n", len );
	MsgSendPulse( coid, 11, 3, len );
	
	msg.x = 7;
	msg.y = 7;

	status = MsgSend( coid, &msg, sizeof( msg ) , &msg,
	                  sizeof( msg ));
	                  
	//PUT CODE HERE to send message to server and get the reply
	if(-1 == status) {   //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	}
	
	printf( "received product, product = %d from server\n", msg.product );
	printf("MsgSend return status: %d\n", status);
	
	printf( "product is %d\n", msg.product );
	return EXIT_SUCCESS;
}
	
// eof: name_look_up.c
