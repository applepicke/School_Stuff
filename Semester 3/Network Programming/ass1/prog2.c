/**prog2.c
 * Assignment 1
 * CST8217
 * By: William Collins
 * Purpose: Get a message from the queue and put it in shared memory.
 */
#include "header.h"

int main(int argc, char *argv[])
{
	struct mymesg mymsg;
	char *shm_p;
	key_t msg_key;
	key_t shm_key;

	int msqid;
	int shmid;
	int semid;

	struct sembuf semset = { 0, -1, 0 };

	/*check args*/
	if (argc != 3)
	{
		printf("syntax: ./prog2 file1 file2\n");
		return 1;
	}

	/*generate key*/
	if ((msg_key = ftok(argv[1], ID)) == -1 || (shm_key = ftok(argv[2], ID)) == -1)
	{
		perror("ftok: ");
		return 1;
	}

	/*set up semaphore set*/
    if ((semid = semget(msg_key, 1, 0666L)) == -1)
    {
        perror("semget: ");
        return 1;
    }

	/*access message queue*/
	if ((msqid = msgget(msg_key, 0666)) == -1)
	{
		perror("msgget ");
		return 1;
	}

	/*put message from queue into local variable*/
	if (msgrcv(msqid, &mymsg, MAX_FILE, TYPE, IPC_NOWAIT) == -1)
	{
		perror("msgrcv: ");
		return 1;
	}

    /*decrement semeaphore to control access to shared memory*/
    if (semop(semid, &semset, 1) == -1)
    {
        perror("semop: ");
        return 1;
    }

	/*get shared memory address*/
	if ((shmid = shmget(shm_key, sizeof(mymsg), 0666 | IPC_CREAT | IPC_EXCL)) == -1)
	{
		perror("shmget: ");
		return 1;
	}	

	if ((shm_p = shmat(shmid, NULL, 0)) == (void *) -1)
	{
		perror("shmat: ");
		return 1;
	}

	/*put message from queue into shared memory*/	
	strcpy(shm_p, mymsg.msg);

	/*remove message queue from the system*/
	if (msgctl(msqid, IPC_RMID, NULL) == -1)
	{
		perror("msgctl: ");
		return 1;
	}

    /*increment semaphore to allow access again*/
    semset.sem_op = 1;
    if (semop(semid, &semset, 1) == -1)
    {
        perror("semop: ");
        return 1;
    }

	return 0;	
}
