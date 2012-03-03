#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>

int main(int argc, char* argv[]){
	
	char *pathname = malloc (sizeof (pathname));
	int proj_id;
	key_t ipckey;

	if (argc != 3) {
		printf("Not enough arguments\n");
		return 1;
	}

	strcpy(pathname, argv[1]);
	proj_id = atoi(argv[2]);
	
	if ((ipckey = ftok(pathname, proj_id)) == -1){
		printf("Invalid Filename or Id\n");
		return 1;
	}
	else{
		printf("Key: %08X\n", ipckey);
		return 0; 	
	}
}
