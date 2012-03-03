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
#include <sys/iofunc.h>
#include <sys/dispatch.h>


int
calculate_checksum(char *text);

int product( int x, int y ); // modify server to return product of two integers

typedef union
{
	uint16_t type;
	cksum_msg_t msg;
	struct _pulse pulse;
} recv_buf_t;
	
int 
main(void) {
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

int product( int x, int y ) {
	printf( "inside function product\n" );
	printf( "x = %d\n", x );
	printf( "y = %d\n", y );
	return( x * y );
}

// eof: name_lookup_server.c
