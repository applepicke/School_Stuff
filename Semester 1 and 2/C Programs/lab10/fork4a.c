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
      printf("child %d exit\n", getpid());
      exit(123);
   }
   else {                         /* parent */
      sleep(30);         /* simulate action */
      printf("parent exit without wait\n");
   }
   printf("after: pid = %d\n", getpid());
   return 0;
}
