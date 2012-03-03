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

#include "prod.h"  //layout of msgs should always defined by a struct, here's its definition
#include <sys/iofunc.h>
#include <sys/dispatch.h>


int product( int x, int y ); // modify server to return product of two integers

struct prod msg;

int main(void) {
	int pid;	
	int rcvid;
	int status;

	name_attach_t *att;

	// register our name	
	att = name_attach( NULL, SERVER_NAME, 0 );
	
	if( NULL == att ) {
		perror("name_attach");
		exit( EXIT_FAILURE );
	} else {
		printf( "name attach succeed\n");
	}

	pid = getpid();                 //get our own pid
	printf("Server's pid: %d, chid: %d\n", pid, att->chid); //print our pid/chid so
	                                             //client can be told where to
	                                             //connect
	printf( "size of meg is %d\n", sizeof( msg ) );

	while(1) {
		rcvid = MsgReceive( att->chid, &msg, sizeof(msg), NULL );
		//PUT CODE HERE to receive msg from client, store the receive id in rcvid
		if(rcvid == -1) {            //was there an error receiving msg?
			perror("MsgReceive");     //look up errno code and print
			break;                    //try receiving another msg
		}
		else if( 0 == rcvid ) {
			//printf("we got a pulse with a code of %d, and value of %d\n",
			//      msg.pulse.code, rbuf.pulse.value.sival_int );
			printf("pulse received\n");
		}
		else // we got a message
		{ // rbuf.msg.msg_type
			printf("we got a message with type %d\n", msg.msg_type );
			// fix
			if( 1 ) {
				printf("product computed\n");
				msg.product = product( msg.x, msg.y );
				//= calculate_checksum(rbuf.msg.string_to_cksum);
				
				printf( "product computed as %d", msg.product );

				status = MsgReply( rcvid, EOK, &msg, sizeof( msg ) );
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

int product( int x, int y ) {
	printf( "inside function product\n" );
	printf( "x = %d\n", x );
	printf( "y = %d\n", y );
	return( x * y );
}

// eof: name_lookup_server.c
