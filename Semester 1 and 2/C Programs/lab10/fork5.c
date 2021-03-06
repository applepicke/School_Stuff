/***
fork 5
   fork a simple child, printf tracks location
   signal handling
 ***/
#define	_XOPEN_SOURCE	600
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
void sig_parent(int);
void sig_child(int);

/* GLOBALS */
int flag = 0;
char msg[256];

int main(void)
{
   struct sigaction act;
   int child_status, child_pid, parent_pid;
   sigemptyset(&act.sa_mask);
   act.sa_flags = 0;
   act.sa_handler = sig_parent;
   sigaction(SIGUSR1, &act, NULL);
   act.sa_handler = sig_parent;
   sigaction(SIGUSR2, &act, NULL);

   parent_pid = getpid();
   printf("original: pid = %d\n", parent_pid);
   switch (child_pid = fork())
   {
      case -1:
         exit(1);
      case 0:           /* child */
         act.sa_handler = sig_child;
         sigaction(SIGUSR2, &act, NULL);
         printf("child: pid = %d/%d\n", child_pid, getpid());
         while (1)
         {
            pause();
            printf("child signal\n");
            if (flag) fputs(msg, stdout);
            flag = 0;
         }
      default:          /* parent */
         printf("parent: pid = %d/%d\n", parent_pid, getpid());
         break;
   }
   printf("after: pid = %d\n", getpid());
   while (1)
   {
      pause();
      printf("parent signal\n");
      if (flag) fputs(msg, stdout);
      flag = 0;
   }

/*** none of the code below will ever execute ***/
   wait(&child_status);  /* wait for the child */
	if (WIFEXITED(child_status)) {
      printf("parent: child status%d\n",
               "WEXITSTATU not exist\n", fname);
		return 0;
	}

	if (S_ISREG(sbuf.st_mode)) {
		return 1;
	}

	if (S_ISFIFO(sbuf.st_mode)) {
		return 1;
	}

	return 0;
}

                                                                                                                                                                                       