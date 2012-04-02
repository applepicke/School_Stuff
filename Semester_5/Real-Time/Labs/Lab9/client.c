/*
 * server.c
 *
 *  Created on: 2012-03-19
 *      Author: Willy Collins
 */

/* client.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iomsg.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>

#include "my_hdr.h"

int main( int argc, char **argv)
{
  int chid, coid, srv_coid, rcvid;
  struct my_msg msg;
  struct _pulse pulse;
  int i = 0;

  /* we need a channel to receive the pulse notification on */
  chid = ChannelCreate( 0 );

  /* and we need a connection to that channel for the pulse to be
     delivered on */
  coid = ConnectAttach( 0, 0, chid, _NTO_SIDE_CHANNEL, 0 );

  /* fill in the event structure for a pulse */
  SIGEV_PULSE_INIT( &msg.event, coid, SIGEV_PULSE_PRIO_INHERIT,
                    MY_PULSE_CODE, 0 );
  msg.type = MSG_GIVE_PULSE;

  /* find the server */
  while (1)
  {
	 srv_coid = name_open( MY_SERV, 0 );
	 if (srv_coid != -1){
		 break;
	 }

	 if (i == 4){
		 printf("can't find server, spawing server..\n");
		 spawnl(P_NOWAIT, "server", "server", NULL);
		 delay(1000);
		 continue;
	 }
	 printf("can't find server, trying again in 1 second...\n");
     delay(1000);
     i++;
  }

  /* give the pulse event we initialized above to the server for
     later delivery */
  MsgSend( srv_coid, &msg, sizeof(msg), NULL, 0 );

  /* wait for the pulse from the server */
  rcvid = MsgReceivePulse( chid, &pulse, sizeof( pulse ), NULL );
  printf("got pulse with code %d, waiting for %d\n", pulse.code,
         MY_PULSE_CODE );

  return 0;
}
// EOF: client.c
