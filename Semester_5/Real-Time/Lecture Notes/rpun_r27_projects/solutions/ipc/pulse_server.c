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

#include "msg_def.h"  //layout of msgs should always defined by a struct, here's its definition


int
calculate_checksum(char *text);

typedef union
{
	uint16_t type;
	cksum_msg_t msg;
	struct _pulse pulse;
} recv_buf_t;
	
int 
main(void) {
	int chid;       
	int pid;	
	int rcvid;
//	cksum_msg_t msg; 
	recv_buf_t rbuf;
	int status;
	int checksum;
	
	chid = ChannelCreate( 0 );
	//PUT CODE HERE to create a channel, store channel id in the chid variable
	if(-1 == chid) {                //was there an error creating the channel?
		perror("ChannelCreate()");  //look up the errno code and print
		exit(EXIT_FAILURE);            
	}
	
	pid = getpid();                 //get our own pid
	printf("Server's pid: %d, chid: %d\n", pid, chid); //print our pid/chid so
	                                             //client can be told where to
	                                             //connect
	while(1) {
		rcvid = MsgReceive( chid, &rbuf, sizeof(rbuf), NULL );
		//PUT CODE HERE to receive msg from client, store the receive id in rcvid
		if(rcvid == -1) {            //was there an error receiving msg?
			perror("MsgReceive");     //look up errno code and print
			break;                    //try receiving another msg
		}
		else if( 0 == rcvid )
		{
			printf("we got a pulse with a code of %d, and value of %d\n",
			      rbuf.pulse.code, rbuf.pulse.value.sival_int );
		}
		else // we got a message
		{
			if( rbuf.type == CKSUM_MSG_TYPE)
			{
				printf("Got a checksum message\n");
				checksum = calculate_checksum(rbuf.msg.string_to_cksum);
				
				status = MsgReply( rcvid, EOK, &checksum, sizeof( checksum ) );
				//PUT CODE HERE TO reply to client with checksum, store the return status in status
				if(-1 == status) {
					perror("MsgReply");
				}
			}
			else
			{
				// unknown message type, unblock client with an error
				MsgError( rcvid, ENOSYS);
			}
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

