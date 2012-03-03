#ifndef _IOV_SERVER_H_
#define _IOV_SERVER_H_

#include <sys/iomsg.h>

#define CKSUM_SERVER_NAME "cksum"
#define CKSUM_MSG_TYPE _IO_MAX + 1

//layout of msg's should always defined by a struct, and ID'd by a msg type 
// number as the first member
typedef struct {
	uint16_t msg_type;
	unsigned data_size;
} cksum_header_t;					

#endif //_IOV_SERVER_H_
