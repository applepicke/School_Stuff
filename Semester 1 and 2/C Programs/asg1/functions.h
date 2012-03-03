/**********************************************************************
 * Filename:            functions.h
 * Version:             1.0
 * Author:              Robert Allison
 * Student Number:      N/A
 * CST8204              Linux C Programming
 * Lab Section:         N/A
 * Assignment Number:   1
 * Assignment Name:     Multibase Calculator
 * Due Date:            N/A
 * Submission date:     N/A
 * Professor:           Robert Allison
 * Purpose:
 *     Function prototypes for all files
 **********************************************************************/

/* input functions */
int in_cvt(char*, int);
int ctob(int, int);

/* WC 1010-01-25 */
char hex_in(char);
char hex_out(int);

/* output functions */
char *out_cvt(int, int, char*, size_t);
char btoc(int, int);

/* other functions */
int get_base(char*);
char *rev_str(char*, char*);
