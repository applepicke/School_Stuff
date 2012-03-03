/**********************************************************************
 * Filename:            lk.h
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
 *     #includes and constants for all files
 **********************************************************************/

#define _XOPEN_SOURCE 600
#define D 1

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <strings.h>
#include <string.h>

int check_file(const char *name, int bFlag, int hFlag, int sFlag);
void in_dir(char *dName, int bFlag, int hFlag, int sFlag, int rFlag);

