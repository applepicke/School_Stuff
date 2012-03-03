////////////////////////////////////////////////////////////////////////////////
// iov_server.c
//
// demonstrates using input/output vector (IOV) messaging
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

#include "iov_server.h"

typedef union {
	uint16_t msg_type;
	struct _pulse pulse;
	cksum_header_t cksum_hdr;
} msg_buf_t;


int calculate_checksum(char *text);

int 
main(void) {
	int rcvid;
	name_attach_t* attach;
	msg_buf_t msg;
	int status;
	int checksum;
	char* data;
	
	attach = name_attach(NULL, CKSUM_SERVER_NAME, 0);
	if(attach == NULL) {                //was there an error creating the channel?
		perror("name_attach");  //look up the errno code and print
		exit(EXIT_FAILURE);            
	}
	
	while(1) {
		printf("Waiting for a message...\n");
		rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL); 	
		if(rcvid == -1) {             //was there an error receiving msg?
			perror("MsgReceive");     //look up errno code and print
			break;                    //try receiving another msg
		}
		else if(rcvid > 0) {  //msg
			switch(msg.msg_type) {
				case _IO_CONNECT:    //name_open() within the client may send this 
					printf("received an _IO_CONNECT msg\n");
					MsgReply(rcvid, EOK, NULL, 0); 
					break;
				case CKSUM_MSG_TYPE:
					printf("Received a checksum request msg, header says the data is %d bytes\n", msg.cksum_hdr.data_size);
					data = malloc(msg.cksum_hdr.data_size);
					if( NULL == data )
					{
						MsgError( rcvid, ENOMEM );
					}
					else
					{
						status = MsgRead(rcvid, data, msg.cksum_hdr.data_size, sizeof(cksum_header_t) );

						checksum = calculate_checksum(data);
						free(data);
						status = MsgReply(rcvid, EOK, &checksum, sizeof(checksum) );
						if(-1 == status) {
							perror("MsgReply");
						}
					}

					break;
				default: 
					MsgError(rcvid, ENOSYS); 
					break;
			}
		}
		else if(0 == rcvid) { //pulse
			switch(msg.pulse.code) {
				case _PULSE_CODE_DISCONNECT:
					printf("Received disconnect pulse\n");
					ConnectDetach(msg.pulse.scoid);
					break;
				case _PULSE_CODE_UNBLOCK:
					printf("Received unblock pulse\n"); 								
					break;

				default:
					printf("unknown pulse received, code = %d\n", msg.pulse.code);
			
			}
		}
		else {
			printf("Receive returned an unexpected value: %d\n", rcvid);
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


