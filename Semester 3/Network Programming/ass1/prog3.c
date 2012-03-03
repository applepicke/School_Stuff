/**prog3.c
 * Assignment 1
 * CST8217
 * By: William Collins
 * Purpose: Accesses two shared memory locations and puts the data together.
 */
#include "header.h"

int main(int argc, char *argv[])
{
	FILE *file;		/*file stream to send data to file*/
	
	struct sembuf semset = { 0, -1, 0 };

	char *shm_p1;	/*pointer to shared memory1*/
	char *shm_p2;	/*pointer to shared memory2*/
	char output[32] = "output1";

	key_t key1;	
	key_t key2;

	int shmid1;
	int shmid2;
	int semid;
	int fd; 		/*file descriptor for the combined data*/
	int i;

	/*check args*/
	if (argc != 3)
	{
		printf("syntax: ./prog3 file1 file2");
		return 1;
	}

	/*open file with the name output1. if output1 exists call it output2..etc*/
	for (i = 2; ;i++)
	{
		if ((fd = open(output, O_RDWR | O_EXCL | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH )) == -1)
		{
			if (errno == EEXIST)
			{
				output[strlen(output)-1] = '\0';
				sprintf(output, "%s%d", output, i);
			}
			else
			{
				perror("open: ");
				return 1;
			}
		}
		else
		{ 	
			break;
		}
	} 
	if ((file = fdopen(fd, "r+")) == NULL)
	{
		perror("fdopen: ");
		return 1;
	}

	/*generate keys*/
	if ((key1 = ftok(argv[1], ID)) == -1 || (key2 = ftok(argv[2], ID)) == -1)
	{
		perror("ftok: ");
		return 1;
	}
	/* get semephore set*/
	if ((semid = semget(key1, 1, 0666)) == -1)
	{
		perror("semget: ");
		return 1;
	}

	/* decrement semaphore set while memory in use*/
	if (semop(semid, &semset, 1) == -1)
	{
		perror("semop decrement: ");
		return 1;
	}	
	
	/*access and attach shared memory 1*/
	if ((shmid1 = shmget(key1, MAX_FILE, 0666)) == -1)
	{
		perror("shmget1: ");
		return 1;
	}
	if ((shm_p1 = shmat(shmid1, NULL, 0)) == (void *) -1)
	{
		perror("shmat1: ");
		return 1;
	}

	/*access and attach shared memory 2*/
	if ((shmid2 = shmget(key2, MAX_FILE, 0666)) == -1)
	{
		perror("shmget2: ");
		return 1;
	}
	if ((shm_p2 = shmat(shmid2, NULL, 0)) == (void *) -1)
	{
		perror("shmat2: ");
		return 1;
	}
	
	/*send information to file*/
	while (shm_p1[0] != '\0' || shm_p2[0] != '\0')
	{
		if (shm_p1[0] != '\0')
		{
			while (shm_p1[0] != '\n')
			{
				fputc(shm_p1[0], file);
				shm_p1++;
			}
			shm_p1++;	
			fputc('\n', file);
		}
		if (shm_p2[0] != '\0')
		{
			while (shm_p2[0] != '\n')
			{
				fputc(shm_p2[0], file);
				shm_p2++;
			}
			shm_p2++;
			fputc('\n', file);	
		}	
	}

	/*remove shared memory*/
	if (shmctl(shmid1, IPC_RMID, NULL) == -1)
	{
		perror("shmctl1: ");
		return 1;
	}
	if (shmctl(shmid2, IPC_RMID, NULL) == -1)
	{
		perror("shmctl2: ");
		return 1;
	}

	/*release the semaphore*/
	semset.sem_op = 1;
	if (semop(semid, &semset, 1) == -1)
	{
		perror("semop release: ");
		return 1;
	}	

	/*remove semapohore set*/
	if (semctl(semid, 0, IPC_RMID, NULL) == -1)
	{
		perror("semctl remove: ");
		return 1;
	}

	return 0;
}
