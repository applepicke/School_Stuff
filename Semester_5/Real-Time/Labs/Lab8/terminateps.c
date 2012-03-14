/*
 * terminateps.c
 *
 *  Created on: Mar 12, 2012
 *      Author: willy
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include "prod.h"
int main(){
	union my_msg msg;
	int coid = name_open(SERVER_NAME, 0);

	printf("Sending exit pulse\n");
	msg.pulse.code = EXIT_PULSE_CODE;
	MsgSendPulse(coid,getprio(0),msg.pulse.code, 0);

	name_close(coid);

	return 0;
}
