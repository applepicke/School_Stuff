/***
fork 3
   fork a simple child, printf tracks location
   exit in child when done, no newline on 1st printf
 ***/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
   printf("from original (pid %d) - no newline - ", getpid());
   switch (fork())
   {
      case -1:
         perror("fork error");
         exit(1);
      case 0:           /* child */
         printf("from the child (pid%d)\n", getpid());
         exit(123);
      default:          /* parent */
         printf("from the parent (pid %d)\n", getpid());
         break;
   }
   printf("after the switch statement (pid %d)\n", getpid());
   return 0;
}
