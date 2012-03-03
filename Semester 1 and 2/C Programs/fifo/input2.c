#include <stdio.h>
#include <sys/stat.h>
#define _XOPEN_SOURCE 600

int isFile(const char *file);

int main(int argc, char *argv[])
{
	FILE *ifp;
	FILE *fifop;
	char buf[100];
	int len;

	if (argc != 2) {
		fprintf(stderr,"./input2 [inputFile] \n");
		return 1;
	}
	
	if (isFile(argv[1]) == 0) {
		fprintf(stderr, "%s: file does not exist\n", argv[2]);
		return 1;
	}
	
	mkfifo("public", 0600);

	if ((fifop = fopen("public", "w")) == NULL) {
		fprintf(stderr, "Cannot create fifo\n");
		return 1;
	}

	if ((ifp = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "%s: cannot open file\n", argv[1]);	
		return 1;
	}
	
	while ((len = fread(buf, 1,sizeof buf, ifp)) > 0) 
		fwrite(buf, 1, len, fifop);

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

