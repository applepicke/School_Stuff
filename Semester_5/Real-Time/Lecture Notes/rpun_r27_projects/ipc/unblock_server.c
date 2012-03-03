////////////////////////////////////////////////////////////////////////////////
// unblock_server.c
//
// 
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/neutrino.h>

#include "msg_def.h"
#include <unistd.h>

typedef union
{
	uint16_t type;
	cksum_msg_t cksum_msg;
	struct _pulse pulse;
} msg_buf_t;

int calculate_checksum(char *text);


int 
main(void) {
	int rcvid;
	name_attach_t* attach;
	msg_buf_t msg;
	int status;
	int checksum;
	struct _msg_info msg_info;
	
	attach = name_attach(NULL, UNBLOCK_SERVER, 0);
	if(attach == NULL) {                //was there an error creating the channel?
		perror("name_attach");  //look up the errno code and print
		exit(EXIT_FAILURE);            
	}
	
	while(1) {
		printf("Waiting for a message...\n");
		status = MsgReceive(attach->chid, &msg, sizeof(msg), &msg_info); 	//PUT CODE HERE to receive msg from client
		if(status == -1) {            //was there an error receiving msg?
			perror("MsgReceive");     //look up errno code and print
			continue;                    //try receiving another msg
		}
		else if(status > 0) {  //msg
			rcvid = status;
			switch(msg.type) {
				case _IO_CONNECT:    //name_open() within the client may send this 
					printf("received an _IO_CONNECT msg\n");
					MsgReply(rcvid, EOK, NULL, 0); 
					continue;
				case CKSUM_MSG_TYPE:
					printf("Received a checksum request msg, rcvid: %d\n", rcvid);
					printf("Calculating checksum, but I'm not going to reply....\n");
					checksum = calculate_checksum(msg.cksum_msg.string_to_cksum);
//					status = MsgReply(rcvid, &checksum, sizeof(checksum) );
//					if(-1 == status) {
//						perror("MsgReply");
//					}										

					continue;
				default: 
					MsgError(rcvid, ENOSYS); 
					continue;
			}
		}
		else if(status == 0) { //pulse
			switch(msg.pulse.code) {
				case _PULSE_CODE_DISCONNECT:
					printf("Received disconnect pulse\n");
					ConnectDetach(msg.pulse.scoid);
					break;
				case _PULSE_CODE_UNBLOCK:
					printf("got an unblock pulse, value is %d\n", msg.pulse.value.sival_int);
					printf("will sleep for 20 seconds, then unblock. \n");
					printf("The Signal Information view should show a pending signal\n");
					sleep(20);
					printf("Unblocking the client now.");
					MsgError( msg.pulse.value.sival_int, EINTR);
					break;
				default:
					printf("unknown pulse received, code = %d\n", msg.pulse.code);
			}
		}
		else {
			printf("MsgReceive returned an unexpected value < -1 !!!\n");
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


