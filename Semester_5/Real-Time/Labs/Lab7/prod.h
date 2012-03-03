/*
 * prod.h
 *
 * Created on: 2012-02-22
 * Author: terais
 * for use in lab 7, Winter 2012
 */



#ifndef PROD_H_
#define PROD_H_

struct prod {
	int x;
	int y;
	int product;
};

struct msg {
	int value;
};

#define SERVER_NAME "server"
#define NAME "shm_name"

#endif /* PROD_H_ */

// eof: prod.h
