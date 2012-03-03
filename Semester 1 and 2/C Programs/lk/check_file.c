/**********************************************************************
 * Filename:            check_file.c
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
 * Purpose:
 *    
 **********************************************************************/
#include "lk.h"
/**********************************************************************
 * Function name:   check_file
 * Purpose:         check for link properties in a file
 * Function Inputs: 
 *                  
 * Function Output: returns 0, appropriate error handling is done inside
 * Version:         1.0
 * Author:          William Collins
 **********************************************************************/
int check_file(const char *name, int bFlag, int hFlag, int sFlag)
{
	struct stat buf;
	struct stat linkbuf;
	
	if (stat(name, &linkbuf) == -1) {
		if (bFlag) {
			lstat(name, &buf);
			printf("%d: %s: broken link\n", buf.st_ino, name);
		}
	}
	else if	(lstat(name, &buf) == -1)
		fprintf(stderr, "stat error");
	else if (S_ISDIR(buf.st_mode))
		return D;
	else if (buf.st_nlink > 1 && hFlag)
		printf("%d: %s: hard link\n", buf.st_ino, name);
	else if (S_ISLNK(buf.st_mode) && sFlag)
		printf("%d: %s: soft link\n", buf.st_ino, name);
	return 0;
}