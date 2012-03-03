////////////////////////////////////////////////////////////////////////////////
// server.c
//
// A QNX msg passing server.  It should receive a string from a client,
// calculate a checksum on it, and reply back the client with the checksum.
//
// The server prints out its pid and chid so that the client can be made aware
// of them.
//
// Using the comments below, put code in to complete the program.  Look up 
// function arguments in the course book or the QNX documentation.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <process.h>

#include "msg_def.h"  //layout of msg's should always defined by a struct, here's its definition


int
calculate_checksum(char *text);

int 
main(void) {
	int chid;       
	int pid;	
	int rcvid;
	cksum_msg_t msg; 
	int status;
	int checksum;
	
	//PUT CODE HERE to create a channel, store channel id in the chid variable
	chid = ChannelCreate(0);

	if(-1 == chid) {                //was there an error creating the channel?
		perror("ChannelCreate()");  //look up the errno code and print
		exit(EXIT_FAILURE);            
	} else {
		printf( "Channel successfully created, id = %d\n", chid );
	}
	
	pid = getpid();                 //get our own pid
	printf("Server's pid: %d, chid: %d\n", pid, chid); //print our pid/chid so
	                                             //client can be told where to
	                                             //connect
	while(1) {
		//PUT CODE HERE to receive msg from client, store the receive id in rcvid
		rcvid = MsgReceive(chid, &msg, sizeof msg, NULL);
		if(rcvid == -1) {            //was there an error receiving msg?
			perror("MsgReceive");     //look up errno code and print
			break;                    //try receiving another msg
		} else {
			//printf( "receive id is %d\n", rcvid );
		}
		
		checksum = calculate_checksum(msg.string_to_cksum);
		
		//PUT CODE HERE TO reply to client with checksum, store the return status in status
		status = MsgReply(rcvid, 0, &checksum, sizeof(int));
		if(-1 == status) {
			perror("MsgReply");
		} else {
			//printf( "status is %d\n", status );
		}
	}  
	return 0;		 
}


int
calculate_checksum(char *text)
{
    char *c;
    int cksum = 0;

    for (c = text; *c != NULL; c++) 
        cksum += *c;
    return cksum;
}

