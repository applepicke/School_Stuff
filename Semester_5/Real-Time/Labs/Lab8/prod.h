/*
 * prod.h
 *
 * Created on: 2011-06-26
 * Author: terais
 */

#ifndef PROD_H_
#define PROD_H_

#include <sys/iomsg.h>

struct prod {
	uint16_t msg_type;
	int x;
	int y;
	int product;
};

union my_msg {
	struct prod   msg;
	struct _pulse pulse;
};

#define SERVER_NAME "prod_server_ch1"
#define EXIT_PULSE_CODE 1
#define Y = 1
#define X = 2
#endif /* PROD_H_ */

// eof: prod.h
