/**prog1
 * Assignment 1
 * By: William Collins
 * CST8217
 * Purpose - This program will take in two data files
 * sending one to shared memory, and one to a message queue
 */
#include "header.h"

int main(int argc, char *argv[])
{
	FILE *file1;
	FILE *file2;	
				
	struct mymesg mymsg_data1;	/*Data file 1*/
	struct mymesg mymsg_data2;	/*Data file 2*/ 
	struct msqid_ds msq_ds; 	/*Message queue data structure*/
	struct shmid_ds shm_ds; 	/*Shared memory data structure*/
	union semun setval;	

	char *shm_p;
	key_t key;
	
	int msqid;
	int shmid;
	int semid;

	struct sembuf semset = { 0, -1, 0 };

	mymsg_data2.mtype = TYPE;	/*Set message type*/
	setval.val = 1;				/*set value of semaphore set*/	

	/*check arguments*/
	if (argc != 3)
	{
		printf("syntax: ./prog1 file1 file2\n");
		return 1;
	}

	/*open file1 and file2*/
	if ((file1 = fopen(argv[1], "r")) == NULL)
	{
		perror("fopen1: ");
		return 1;
	}	
	if ((file2 = fopen(argv[2], "r")) == NULL)
	{
		perror("fopen2: ");
		return 1;
	}

	/*create key from file 1*/
	if ((key = ftok(argv[1], ID)) == -1)
	{
		perror("ftok: ");
		return 1;	
	}

	/*set up semaphore set*/
	if ((semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
	{
		perror("semget: ");
		return 1;
	}	

	/*initialize sem set to 1*/
	if (semctl(semid, 0, SETVAL, setval) == -1)
	{
		perror("semctl setval: ");
		return 1;
	}
 
	/*set up the shared memory to be used*/
	if ((shmid = shmget(key, sizeof(mymsg_data1), 0666 | IPC_CREAT | IPC_EXCL)) == -1)	
	{
		perror("shmget: ");
		return 1;
	}

	/*set up the message queue to be used*/
	if ((msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL)) == -1)
	{
		perror("msgget: ");
		return 1;
	}

	/*read in from files write to destinations*/
	wread(file1, mymsg_data1.msg);
	wread(file2, mymsg_data2.msg);

	/*send message to message queue*/
	if (msgsnd(msqid, &mymsg_data2, MAX_FILE, IPC_NOWAIT) == -1)
	{
		perror("msgsnd: ");
		return 1;
	}
	
	/*decrement semeaphore to control access to shared memory*/
	if (semop(semid, &semset, 1) == -1)
	{
		perror("semop: ");
		return 1;
	}

	/*attach message to shared memory then detach*/
	if ((shm_p = shmat(shmid, NULL, 0)) == (void *)-1)
	{
		perror("shmat: ");
		return 1;
	}
	strcpy(shm_p, mymsg_data1.msg);
	if (shmdt(shm_p) == -1)
	{
		perror("shmdt: ");
	}
	
	/*increment semaphore to allow access again*/
	semset.sem_op = 1;
	if (semop(semid, &semset, 1) == -1)
	{
		perror("semop: ");
		return 1;
	} 

	/*set up shared memory structure*/
	if (shmctl(shmid, IPC_STAT, &shm_ds) == -1)
	{
		perror("shmctl: ");
		return 1;	
	}		
	
	/*set up message queue structure*/
	if (msgctl(msqid, IPC_STAT, &msq_ds) == -1)
	{
		perror("msgctl: ");
		return 1;
	}

	/*display information about shared memory and message queue*/

	/*
 	printf("message queue\n*************\nmsqid: %d\nlast message sent at: %s\n",msqid, ctime(&msq_ds.msg_stime));
	printf("shared memory\n*************\nshmid: %d\nLast attach at: %s\n",shmid, ctime(&shm_ds.shm_atime));
	*/

	return 0;	
}

void wread(FILE *file, char *msg)
{
	int c, i= 0;

	while ((c = fgetc(file)) != EOF)
	{
		msg[i] = c;
		i++;		 
	} 

	msg[i] = '\0';
}
