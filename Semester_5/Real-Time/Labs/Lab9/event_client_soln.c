/*
 * event_client.c
 * 
 * This program, along with event_server.c, demonstrate pulses between a
 * server and a client using MsgDeliverEvent().
 * 
 * The client finds the server using name_open(), passing it the name the 
 * server has registered with name_attach().
 * 
 *  To test it, first run event_server and then run the client as follows:
 *  event_client
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/siginfo.h>
#include <sys/neutrino.h>
#include <sys/dispatch.h>

#include "event_server.h"
#include <unistd.h>

#define PROGNAME "event_client: "

// this is the pulse code we'll expect from the server when it notifies us
#define MY_PULSE_CODE (_PULSE_CODE_MINAVAIL + 3)

union recv_msg {
    struct _pulse pulse;
    short type;
} recv_buf;

int main( int argc, char *argv[] ) {
    int server_coid, self_coid, chid, rcvid;
    struct reg_msg msg;

    /* look for server */
    server_coid = name_open( RECV_NAME, 0 );
    while( server_coid == -1 ) {
      sleep(1);
      server_coid = name_open( RECV_NAME, 0 );
    }

	// create a channel on the client for getting pulses from the server
    chid = ChannelCreate(0);
    if( -1 == chid ) {
        perror( PROGNAME "ChannelCreate");
        exit( EXIT_FAILURE );
    }
    
    // create a connection to our own channel for the pulse event structure 
    self_coid = ConnectAttach( 0, 0, chid, _NTO_SIDE_CHANNEL, 0 );
    if( -1 == self_coid ) {
        perror( PROGNAME "ConnectAttach");
        exit( EXIT_FAILURE );
    }
    
    msg.type = REG_MSG;

    /* class: Initialize the sigevent structure (msg.ev) in the message 
     * to be sent to the server.
     */
	
	SIGEV_PULSE_INIT( &msg.ev, self_coid, getprio(0), MY_PULSE_CODE, 0 );
	
	// send our registration message to the server
    if( MsgSend( server_coid, &msg, sizeof( msg ), NULL, 0 ) == -1 ) {
        perror(PROGNAME "MsgSend");
        exit( EXIT_FAILURE );
    }
    
    while( 1 ) {
    	// wait for messages or pulses, we only expect pulses
        rcvid = MsgReceive( chid, &recv_buf, sizeof(recv_buf), NULL );
        if( -1 == rcvid ) {
            perror(PROGNAME "MsgReceive");
            continue;
        }
        if ( 0 == rcvid ) {
            if( MY_PULSE_CODE == recv_buf.pulse.code ) {
                printf(PROGNAME "got my pulse, value is %d\n",
                       recv_buf.pulse.value.sival_int );
            } else {
                printf(PROGNAME "got unexpected pulse with code %d\n", 
                        recv_buf.pulse.code );
            }
            continue;
        }
        printf(PROGNAME "got unexpected message, type: %d\n", recv_buf.type );
        MsgError( rcvid, ENOSYS );
    }
 }

// eof: event_client_soln.c
