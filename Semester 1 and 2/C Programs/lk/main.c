/**********************************************************************
 * Filename:            main.c
 * Version:             1.0
 * Author:              William Collins
 * Student Number:      N/A
 * CST8204              Linux C Programming
 * Lab Section:         313
 * Assignment Number:   3
 * Assignment Name:     Links
 * Due Date:            March 30, 2010
 * Submission date:     March 30, 2010
 * Professor:           Robert Allison
 * Purpose: A program that finds and reports links
 **********************************************************************/
#include "lk.h"
/**********************************************************************
 * Function name:   main
 * Purpose:         main driver of the program 
 * Function Inputs: argc and argv
 *                 
 * Function Output: reports all appropriate errors
 * Version:         1.0
 * Author:          William Collins
 **********************************************************************/
int main(int argc, char *argv[])
{
	int bFlag = 0, rFlag = 0, sFlag = 0, hFlag = 0, dFlag = 0;
	int opsExist = 0;
	size_t len, i;
	
	if (argc == 1) {
		bFlag = 1;
		dFlag = 1;
	}
	if (argc > 1 && argv[1][0] == '-') {
		opsExist = 1;
		len = strlen(argv[1]);
		for (i = 1 ;i < len; i++) {
			if (argv[1][i] == 'r') {
				 rFlag = 1;
			}
			else if (argv[1][i] == 's') {
				 sFlag = 1;
			}
			else if (argv[1][i] == 'h') {
				 hFlag = 1;
			}
			else if (argv[1][i] == 'b') {
				 bFlag = 1;
			}
			else if (argv[1][i] == '?') {
				printf("Syntax: lk [-options] [path]\n\n -b    show broken soft links\
					   \n -h    show hard links\n -s    show soft links\n -r    search folders recursively\n\
					   \nWhen no arguments are presented, defaults are -b and current directory\n");
			}
			else {
				fprintf(stderr, "%c: invalid option\n", argv[1][i]);
				return 1;
			}
		}
		if (hFlag == 0 && sFlag == 0)
			bFlag = 1;
		if (argc == 2)
			dFlag = 1;
	}
	
	if (dFlag == 1) {
		in_dir(".", bFlag, hFlag, sFlag, rFlag);
	}
	else {
		if (hFlag == 0 && sFlag == 0)
			bFlag = 1;
		if (opsExist) i = 2;
		else i = 1;
		for ( ; i < argc; i++) {
			in_dir(argv[i], bFlag, hFlag, sFlag, rFlag);
		}
	}

	
	return 0;
 
}