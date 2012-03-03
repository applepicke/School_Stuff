////////////////////////////////////////////////////////////////////////////////
// iov_client.c
//
// demonstrates using input/output vector (IOV) messaging
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>     // #define for ND_LOCAL_NODE is in here

#include "iov_server.h"
#include <sys/iofunc.h>
#include <sys/dispatch.h>

int main(int argc, char* argv[]) 
{
	int coid;         //Connection ID to server
	cksum_header_t hdr; //msg header will specify how many bytes of data will follow
	int incoming_checksum;  //space for server's reply
	int status;       //status return value 
	iov_t siov[2];    //create a 2 part iov
	
	if(2 != argc) {
		printf("ERROR: This program must be started with a command-line arg, for example:\n\n");
		printf("   iov_client abcdefjhi    \n\n");
		printf(" where 1st arg(abcdefghi) is the text to be sent to the server to be checksum'd\n");
		exit(EXIT_FAILURE);
	}
	
	// locate the server
	coid = name_open(CKSUM_SERVER_NAME, 0);	
	if(-1 == coid) {   //was there an error attaching to server?
		perror("name_open"); //look up error code and print
		exit(EXIT_FAILURE);
	}
	
	printf("Sending the following text to checksum server: %s\n", argv[1]);
	
	// build the header
	hdr.msg_type = CKSUM_MSG_TYPE;
	hdr.data_size = strlen(argv[1]);
	
	// setup the message as a two part iov, first the header then the data
	SETIOV (&siov[0], &hdr, sizeof hdr);
	SETIOV (&siov[1], argv[1], hdr.data_size);
	
	// and send the message off to the server
	status = MsgSendvs(coid, siov, 2, &incoming_checksum, sizeof incoming_checksum );
	if(-1 == status) {   //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	}
	
	printf("received checksum=%d from server\n", incoming_checksum);
	printf("MsgSend return status: %d\n", status);
	
	return EXIT_SUCCESS;
}
	
