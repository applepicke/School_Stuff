#ifndef _MSG_DEF_H_
#define _MSG_DEF_H_

#include <sys/iomsg.h>

#define MAX_STRING_LEN    256
#define CKSUM_MSG_TYPE _IO_MAX + 1

//layout of msg's should always defined by a struct, and ID'd by a msg type 
// number as the first member
typedef struct {
	uint16_t msg_type;
	char string_to_cksum[MAX_STRING_LEN + 1];  //ptr to string we're sending to server, to make it
} cksum_msg_t;					//easy, server assumes a max of 256 chars!!!!

// If you are sharing a target with other people, please customize these server names
// so as not to conflict with the other person.

#define SERVER_NAME		"cksum_server"  

#define DISCONNECT_SERVER "disconnect_server"

#define UNBLOCK_SERVER "unblock_server"
                              

#endif //_MSG_DEF_H_
