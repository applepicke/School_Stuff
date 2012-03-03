/*client.c*/
/*	Assignment 2 
	By: William Collins & Nicolas Castilloux
	Purpose: Used to connect to the server and send messages */

#include "header.h"
/*Based upon code by Mitch White*/
int main(int argc, char *argv[])
{

	int sockfd, n;
	char name[NAME_SIZE] = "user>",buffer[BUF_SIZE];
	struct sockaddr_in server_addr;
	struct hostent *server;
	/* if client doesnt have 2 args */
	if (argc != 2) {
		printf("USAGE: ./client IP(0.0.0.0)\n");
		exit(1);
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		printf("ERROR: Cannot open socket\n");

	/* get pointer to hostent, details of host */
	/* specify localhost to run server and client on same machine */
	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr,"ERROR: Cannot resolve host name\n");
		exit(0);
	}

		/* clear buffer */
	memset (&server_addr,0, sizeof(server_addr));

	/* set address family */
	server_addr.sin_family = AF_INET;
	/* better to use memcpy */
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	/* convert port number to network byte order */
	server_addr.sin_port = htons(PORT);

	
	/* connect – fd,address, size */
	if (connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
		perror("connect: ");
	while(1){


		printf("%s",name);
		memset(buffer, 0, BUF_SIZE);
  		fgets(buffer,BUF_SIZE,stdin);
   		
   		/* write to the socket */
		n = write(sockfd,buffer,BUF_SIZE-1);
		
		/*exit command */
		if (strcmp(buffer, "exit\n") == 0)
  	 	{
   			close(sockfd);
   	 		printf("Toodles!!\n");
  		 	break;
  	 	}
		/* read response from the server */
		n = read(sockfd,buffer,BUF_SIZE-1);
		printf("%s", buffer);
	}	

	return 0;
}
