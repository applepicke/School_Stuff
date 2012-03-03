/**********************************************************************
 * Filename:            in_dir.c
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
 * 
 *   
 **********************************************************************/
#include "lk.h"
/**********************************************************************
 * Function name:   in_dir
 * Purpose:         to search through directory entries
 * Function Inputs: directory name and flags
 *                 
 * Function Output: reports all appropriate errors
 * Version:         1.0
 * Author:          William Collins
 **********************************************************************/
void in_dir(char *dName, int bFlag, int hFlag, int sFlag, int rFlag)
{
	struct dirent *dp;
	DIR *dirp;
	char path[100];
	
	if (check_file(dName, bFlag, hFlag, sFlag) == D) {
		if ((dirp = opendir(dName)) == NULL)
			fprintf(stderr, "%s: could not open directory\n", dName);
		while ((dp = readdir(dirp)) != NULL) {
			
			strcpy(path, dName);
			strcat(path, "/");
			strcat(path, dp->d_name);
			
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && 
				check_file(path, bFlag, hFlag, sFlag) == D && rFlag == 1) {
					
					in_dir(path, bFlag, hFlag, sFlag, rFlag);
			}
		}
	}
	else fprintf(stderr, "%s: not a directory\n", dName);
}