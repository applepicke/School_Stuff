/* 	Assignment 2
	File: functions.c 
	By: William Collins & Nicolas Castilloux
	Purpose: This file contains all the functions used */	
#include "header.h"

/*	Function: send 
	By: William Collins & Nicolas Castilloux
	Purpose: sends the specified message to the message queue */

void send_msg(int msqid, char *cmd, char *msg_buf, struct username_table usernames[])
{
	struct mymsg msg;
	char name[NAME_SIZE];
	char parsed[BUF_SIZE];
	int i;
	
	/*parse the username out of the cmd*/
	parse(cmd, name, parsed);
	
	/*lookup username in name table*/
	for (i = 0; i < MAX_USERS; i++)
	{
		if (strcmp(usernames[i].username, name) == 0)
			msg.mtype = usernames[i].mtype;
	}
	
	/*ready the message to be sent*/
	strcpy(msg.mtext, parsed);
	printf("%s\n", msg.mtext);
	
	/*send the message*/
	if (msgsnd(msqid, &msg, BUF_SIZE, IPC_NOWAIT) == -1)
	{
		strcpy(msg_buf, "Message could not be sent!\n");
		return;
	}
	else
	{
		strcpy(msg_buf, "Message successfuly sent!\n");
		return;
	}
}

/*	Function: receive 
	By: William Collins & Nicolas Castilloux
	Purpose: Recieves the messages for the specified user from the queue */
	
void receive_msg(int msqid, char *msg_buf, long mtype)
{
	struct mymsg msg;
	char buffer[BUF_SIZE][BUF_SIZE];
	int i, num_msgs, check;

	memset(buffer, 0, BUF_SIZE);
	
	/* receive messages */
	for (i = 0; (check = msgrcv(msqid, &msg, sizeof(msg.mtext), mtype, IPC_NOWAIT)) >= 0; i++)
	{
		if (check < 0 && i == 0)
			strcpy(buffer[0], "You do not have any messages!\n");
		else	
			strcpy(buffer[i], msg.mtext);
	}
	num_msgs = i;
	
	strcpy(msg_buf, buffer[0]);
	for (i = 1; i < num_msgs; i++)
		strcat(msg_buf, buffer[i]);

	msg.mtype = mtype;
	/* send the messages back to the queue */
	for (i = 0; i < num_msgs; i++)
	{
		strcpy(msg.mtext, buffer[i]);
		msgsnd(msqid, &msg, BUF_SIZE, IPC_NOWAIT);

	}
}

/*	Function: delete
	By: William Collins & Nicolas Castilloux
	Purpose: Deletes messages of mtype from the message queue */
	
void delete(int msqid, char *msg_buf, long mtype)
{
	while (msgrcv(msqid, msg_buf, BUF_SIZE, mtype, IPC_NOWAIT) != -1)
		;
	strcpy(msg_buf, "Messages succesfully deleted!\n");
}

/*	Function: parse
	By: William Collins & Nicolas Castilloux
	Purpose: returns and removes the first word of a string */
	
void parse(char *cmd, char *cmd_name, char *new_cmd)
{
	int i, j, place = 0, num_words, flag = 0;
	char buffer[BUF_SIZE][NAME_SIZE];
	char holder[BUF_SIZE];
	
	for (i = 0; i < BUF_SIZE; i++)
	{
		memset(buffer[i], '\0', NAME_SIZE);
	}
	
	/*fill the storage with each word*/
	for (j = 0, flag = 0; flag != 1; j++, place++)
	{
		for (i = 0; cmd[place] != ' '; i++, place++)
		{
			if (cmd[place] == '\n' || cmd[place] == '\0')
			{
				flag = 1;
				break;
			}
			buffer[j][i] = cmd[place];
		}	
	}	
	num_words = j;
	
	if (new_cmd != NULL)
	{
		/*copy first word into temporary buffer*/
		strcpy(cmd_name, buffer[0]);
		
		/*copy each elemnt into a holder, then copy holder*/
		for (i = 1; i < num_words; i++)
		{
			if (i == 1)
			{
				strcpy(holder, buffer[i]);
				strcat(holder, " ");
			}
			else
			{
				strcat(holder, buffer[i]);
				strcat(holder, " ");
			}
		}
		holder[strlen(holder)-1] = '\n';
		strcpy(new_cmd, holder);
	}
	
	
}

/*	Function: login
	By: William Collins & Nicolas Castilloux
	Purpose: logs the user in */
	
long login(char *cmd, struct username_table usernames[],char *name) {
	int c;
	long type;

	if (cmd[strlen(cmd) -1] == '\n')
		cmd[strlen(cmd) -1] = '\0';
	/* cycle through the user table*/
	for(c = 0;c < MAX_USERS; c++) {
		/* if user is found, get its username and type*/
		if (strcmp(cmd, usernames[c].username) == 0 ) {
			strcpy(name, usernames[c].username);
			type = usernames[c].mtype;
			return type;
		}
	}
	return -1;
}

