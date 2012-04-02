/*
 * server.c
 *
 *  Created on: 2012-03-19
 *      Author: Willy Collins
 */

/* server.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iomsg.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#include "my_hdr.h"

int main(int argc, char **argv) {
  int             rcvid;
  union {
      struct my_msg   mine;
      struct _pulse   pulse;
  }           msg;
  name_attach_t  *attach;

  /* Attach the name the client will use to find us. */
  /* Our channel will be in the attach structure */
  if ((attach = name_attach(NULL, MY_SERV, 0)) == NULL) {
     printf("server:failed to attach name, errno %d\n", errno);
     exit(1);
  }

  /* Wait for the message from the client. */
  for( ;; ) {
     rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);
     switch(msg.mine.type) {
        case _PULSE_CODE_DISCONNECT:
           ConnectDetach(msg.pulse.scoid);
           break;
        case _IO_CONNECT:
           MsgReply(rcvid, 0, NULL, 0);
           break;
        case MSG_GIVE_PULSE:
           /* Wait until it is time to notify the client */
           sleep(2);

           /*
            * Deliver notification to client that client
            * requested
            */
           MsgDeliverEvent(rcvid, &msg.mine.event);
           printf("server:delivered event\n");
           return 0;
        default:
           printf("server: unexpected message %d\n", msg.mine.type);
           return 0;
     }
  }

  return 0;
}

// EOF: server.c
