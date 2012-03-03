/**program.c*/
#include "header.h"

/**Global Variabls*/
extern int flag;
extern char msg[100];
extern pid_t child;

int main(){
	
	int status = 0;
	/**set up sigaction*/
	struct sigaction action;
	action.sa_handler = &handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	
	if (sigaction(SIGUSR1, &action, NULL) == -1){
		fprintf(stderr, "SIGUSR1 could not be set\n");
	}
	if (sigaction(SIGUSR2, &action, NULL) == -1){
		fprintf(stderr, "SIGUSR2 could not be set\n");
	}
	if (sigaction(SIGTERM, &action, NULL) == -1) {
		fprintf(stderr, "SIGTERM could not be set\n");
	}

	/**fork*/
	if ((child = fork()) == -1) {
		fprintf(stderr, "error in fork\n");
	}
	else if (child == 0){
		/**Child Process*/
		while (1){
			sleep(1);
			if (flag != 0){
				printf("Child %s\n", msg);
				if (flag == SIGTERM){
					printf("Child exiting\n");
					_exit(10);
				}
				else 
					flag = 0;
			}
		}
	}
	else if (child != 0){
		/**Parent Process*/
		while (1){
			sleep(1);
			if (flag != 0) {
				printf("Parent %s\n", msg);
				if (flag == SIGUSR1)
					kill(child, SIGUSR1);
				else if (flag == SIGUSR2)
					kill(child, SIGUSR2);
				else if (flag == SIGTERM){
					kill(child, SIGTERM);
					wait(&status);
					if (WIFEXITED(status)){
						printf("Parent has exited");
						return 0;
					}
				}
				flag = 0;
			}
		}
	}	

}
