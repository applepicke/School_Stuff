#include <stdio.h>
#include <sys/stat.h>
#define _XOPEN_SOURCE 600

int isFile(const char *file);

int main(int argc, char *argv[])
{
	FILE *ofp;
	FILE *fifop;
	char buf[100];
	int len;

	if (argc != 2) {
		fprintf(stderr, "./output [outputFile]\n");
		return 1;
	}

	if ((ofp = fopen(argv[1], "w+")) == NULL) {
		fprintf(stderr, "%s: cannot open file\n", argv[1]);
		return 1;
	}

	if ((fifop = fopen("public", "r")) == NULL) {
		fprintf(stderr, "Cannot open fifo\n");
		return 1;
	}

	while ((len = fread(buf, 1, sizeof buf , fifop)) > 0)
    		fwrite(buf, 1, len, ofp);

	remove("public");
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
