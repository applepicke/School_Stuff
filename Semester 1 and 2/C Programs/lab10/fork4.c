/***
fork 4
   fork a simple child, printf tracks location
   parent waits, WIFEXITED and WEXITSTATUS
 ***/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(void) {
   int child_pid = -1, child_status = -1;

   printf("original %d\n", getpid());
   if ((child_pid = fork()) == -1)
         exit(1);
   else if (child_pid == 0) {     /* child */
      printf("child: %d/%d, status %d\n",
        child_pid, getpid(), child_status);
      sleep(30);      /* simulate action */
      printf("child %d exit\n", getpid());
      exit(123);
   }
   else {                         /* parent */
      wait(&child_status);        /* wait */
      if (WIFEXITED(child_status))
         printf("parent: pid %d exit %d\n",
            child_pid, WEXITSTATUS(child_status));
      else
         printf("no WIFEXITED\n");
   }
   printf("after: pid = %d\n", getpid());
   return 0;
}
