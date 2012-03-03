#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


int isFile(const char *file);

int main(int argc, char *argv[])
{
	FILE *ifp;
	FILE *fifop = 0;
	FILE *ofp;
	char buf[100];
	int len;
	int child_pid;
	int child_status = 0;

	if (argc != 4) {
		fprintf(stderr,"./input2 [inputFile] [fifo] [outputFile]\n");
		return 1;
	}
	
	mkfifo(argv[2], 0600);
	
	if (isFile(argv[1]) == 0) {
		fprintf(stderr, "%s: file does not exist\n", argv[1]);
		return 1;
	}
	
	if ((ofp = fopen(argv[3], "w")) == NULL) {
		fprintf(stderr, "%s:cannot open file\n", argv[3]);
		return 1;
	}

	if ((ifp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "%s: cannot open file\n", argv[1]);	
		return 1;
	}

	if ((child_pid = fork()) < 0)
		fprintf(stderr, "error in fork");
	
	else if (child_pid == 0) {
	
		if ((fifop = fopen(argv[2], "w")) == NULL) {
			fprintf(stderr, "%s: cannot open fifo\n", argv[2] );
			return 1;
		}
		
		while ((len = fread(buf, 1, sizeof buf , ifp)) > 0)
    		fwrite(buf, 1, len, fifop);
		fclose(ifp);
		exit(4);
	}
	else {
		if ((fifop = fopen(argv[2], "r")) == NULL) {
			fprintf(stderr, "%s: cannot open fifo\n", argv[2] );
			return 1;
		}
		while ((len = fread(buf, 1,sizeof buf, fifop)) > 0) 
			fwrite(buf, 1, len, ofp);
		fclose(ofp);
		fclose(fifop);
		wait(&child_status);
		
	}
	remove(argv[2]);

	return 0;

	
}

int isFile(const char *fname)
{
	struct stat sbuf;

	if (stat(fname, &sbuf) == -1) {
		fprintf(stderr, "%s: file does not exist\n", fname);
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

