/* This program illustrates file output
 * Similar file output should be implemented in
 * int st_store(STD sym_table)
 * Author: Svillen Ranev.
 */
#include <stdio.h>
#include <string.h>
int main(void){

/* Define a file handle - similar to buffer handle */
 FILE *stf; 

/* Define and initialize few variables */
 int size = 10;
 unsigned short int status = 0xaf5e;
 char name[] = "paltypus";
 char length = strlen(name);
 int line = 17;
 float ivalue = 2.3456;
 char type = 'F';

/* define a file name */
 char *fname = "$file.txt";

/* Open a text file for writing ("wt")
 * If the file already exists, it will be overwritten
 */ 
if ((stf = fopen(fname,"wt")) == NULL){
  printf("Cannot create file: %s/n",fname);
  return -1;
}

/* Store some data into the file */
  fprintf(stf,"%d %hX %d %s %d %c %.3f ",size, status,length,name,
                                          line,type,ivalue);
/* Close the file */ 							  									 
  fclose(stf);
  printf("\nFile stored\n");
  return 0;
}