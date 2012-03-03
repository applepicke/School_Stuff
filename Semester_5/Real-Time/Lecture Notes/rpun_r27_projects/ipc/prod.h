/*
 * prod.h
 *
 *  Created on: 2011-06-26
 *      Author: terais
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

#define SERVER_NAME		  "prod_server"
#define DISCONNECT_SERVER "disconnect_server"
#define UNBLOCK_SERVER    "unblock_server"

#endif /* PROD_H_ */
