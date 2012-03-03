/* Client Program demonstrating set up for client/server communications */
/* within a single computer using port number provided by user
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int sockfd, portnumber, n;
	struct sockaddr_in server_addr;

	struct hostent *server;

	char buffer[256], newbuf[256];
	if (argc < 2) {
		fprintf(stderr,"ERROR: No port\n");
		exit(1);
	}

	portnumber = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		printf("ERROR: Cannot open socket\n");

	/* get pointer to hostent, details of host */
	/* specify localhost to run server and client on same machine */
	server = gethostbyname("localhost");

	if (server == NULL) {
		fprintf(stderr,"ERROR: Cannot resolve host name\n");
		exit(0);
	}

		/* clear buffer */
	memset (&server_addr,0, sizeof(server_addr));

	/* set address family */
	server_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
	/* better to use memcpy */
	/* convert port number to network byte order */
	server_addr.sin_port = htons(portnumber);

	
	/* connect – fd,address, size */
	if (connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
		printf("ERROR: Cannot connect\n");
	
	/*loop through sending and recieving messages*/
	while (strcmp(buffer, "exit") != 0)
	{
		printf("Please enter the message to send: ");

		/* get message and write out received message */
		memset(buffer, 0, 256);
		fgets(buffer,255,stdin);
		
		/*take out the new line entered*/
		if (buffer[strlen(buffer)-1] == '\n')
     		buffer[strlen(buffer)-1] = '\0';
     		
     	/*write message to socket*/	
		n = write(sockfd, buffer,strlen(buffer));
		if (n < 0)
			printf("ERROR: Cannot write to socket\n");

		/*read message from socket*/
    	n = read(sockfd, newbuf, 255);
    	printf("%s\n", newbuf);
    	
    	memset(newbuf, 0, 256);
    	

	}
	
	return 0;
}
