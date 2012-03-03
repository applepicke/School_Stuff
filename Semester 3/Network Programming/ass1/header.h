/*header.h*/
#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/shm.h>
#include <fcntl.h>

/*Definitions*/
#define ID 3
#define MAX_FILE 2048
#define TYPE 1

/*Structures and Unions*/
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct mymesg{
	long mtype;
	char msg[MAX_FILE];
};

/*functions*/
void wread(FILE *file, char msg[]);
