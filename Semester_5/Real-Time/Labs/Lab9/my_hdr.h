/*
 * my_hdr.h
 *
 *  Created on: 2012-03-19
 *      Author: Willy Collins
 */

#ifndef MY_HDR_H_
#define MY_HDR_H_


#endif /* MY_HDR_H_ */

struct my_msg
{
   short type;
   struct sigevent event;
};

#define MY_PULSE_CODE _PULSE_CODE_MINAVAIL+5
#define MSG_GIVE_PULSE _IO_MAX+4
#define MY_SERV "my_server_name"

//EOF: my_hdr.h
