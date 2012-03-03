/**header.h*/
/**Includes*/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**Global Variables*/
int flag;
char msg[100];
pid_t child;

/**Functions*/
void handler(int);
