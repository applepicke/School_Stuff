/**handler.c*/
#include "header.h"

/*Global Variables*/
extern int flag;
extern char msg[100];

void handler(int sig){
	if (sig == SIGUSR1){
		flag = SIGUSR1;
		sprintf(msg, "got SIGUSR1");
	}
	else if (sig == SIGUSR2){
		flag = SIGUSR2;
		sprintf(msg, "got SIGUSR2");
	}
	else if (sig == SIGTERM){
		flag = SIGTERM;
		sprintf(msg, "got SIGTERM");
	}

}
