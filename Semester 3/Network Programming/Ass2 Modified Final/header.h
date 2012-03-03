/*header.h*/
/*	Assignment 2 
	By: William Collins & Nicolas Castilloux
	Purpose: this file contains all header information and macros */
	
#define _XOPEN_SOURCE 600	
	
/*includes*/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <strings.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/shm.h>
#include <fcntl.h>


/*macros*/
#define BUF_SIZE 256
#define NAME_SIZE 32
#define KEY 999999
#define PORT 3100
#define MAX_USERS 20
#define MAX_CONS 2

/*structs*/
struct mymsg {
	long mtype;
	char mtext[BUF_SIZE];
};

struct username_table {
	char username[NAME_SIZE];
	long mtype;	 
};

/*functions*/
void receive_msg(int msqid, char *msg_buf, long mtype);
void send_msg(int msqid, char *cmd, char *msg_buf, struct username_table usernames[]);
long login(char *cmd, struct username_table usernames[], char *cmd_name); 
void delete(int msqid, char *msg_buf, long mtype);
void parse(char cmd[],char *cmd_name, char *new_cmd);
