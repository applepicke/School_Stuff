/*  File name: platy_bt.c
 *  Purpose:This is the main program for Assignment #1, CST8152, Summer 2011)
 *  Version; 1.11.02
 *  Author: Svillen Ranev
 *  Date: 9 May 2011
 */   

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "buffer.h"

/* constant definitions */
#define INIT_CAPACITY 200 /* initial buffer capacity */
#define INC_FACTOR 15       /* increment factor */

/*check for ANSI C compliancy */
#define ANSI_C 0
#if defined(__STDC__)
#undef ANSI_C
#define ANSI_C 1
#endif

/*  Declaration of an error printing function with
 *  variable number of arguments
 */
void err_printf(char *fmt, ...);
/*  Declaration of a buffer contents display function */
void display (Buffer *ptr_Buffer); 
long get_filesize(char *fname);

int main(int argc, char **argv){
	
   Buffer *ptr_Buffer;   /* pointer to Buffer structure */
   FILE *fi;             /* input file handle */
   int loadsize = 0;     /*the size of the file loaded in the buffer */
   int ansi_c = !ANSI_C; /* ANSI C compliancy flag */
   int init_capacity;

   if (strcmp(argv[3], "INT_MAX") == 0){
    	init_capacity = INT_MAX;
   }
   else if (strcmp(argv[3], "INT_MAX-10") == 0){
    	init_capacity = INT_MAX - 10;
   }
   else {
    	init_capacity = atoi(argv[3]);
   }

	 /*Check if the compiler option is set to compile ANSI C */
	/* __DATE__, __TIME__, __LINE__, __FILE__, __STDC__ are predefined preprocessor macros*/
	if(ansi_c){
		err_printf("Date: %s  Time: %s",__DATE__, __TIME__);
		err_printf("ERROR: Compiler is not ANSI C compliant!\n");
		exit(1);
	}

/* missing file name or/and mode parameter */
  if (argc <= 4){

     err_printf("\nDate: %s  Time: %s",__DATE__, __TIME__);
     err_printf("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
	  err_printf("%s\b\b\b\b%s%s",argv[0],": ","Missing parameters.");
	  err_printf("Usage: platybt source_file_name mode initcapacity incfactor");
	  exit(1);
	}
	
/* create a source code input buffer */		
	switch(*argv[2]){
	case 'f': case 'a': case 'm': break;
	default:
		err_printf("%s%s%s",argv[0],": ","Wrong mode parameter.");
		exit(1);
	}
/*create the input buffer */
    ptr_Buffer = b_create(init_capacity, atoi(argv[4]),*argv[2]);
	if (ptr_Buffer == NULL){
		err_printf("%s%s%s",argv[0],": ","Could not create buffer.");
		exit(1);
	}

/* open the source file */
	if ((fi = fopen(argv[1],"r")) == NULL){
		err_printf("%s%s%s%s",argv[0],": ", "Cannot open file: ",argv[1]);
		exit (1);
	}

/* load a source file into the input buffer  */
     printf("Reading file %s ....Please wait\n",argv[1]);
     loadsize = ca_load (fi,ptr_Buffer);
     if(loadsize == R_FAIL_1)
       err_printf("%s%s%s",argv[0],": ","Error in loading buffer.");

/* close the source file */	
 	fclose(fi);
/*find the size of the file  */
    if (loadsize == LOAD_FAIL){
     printf("The input file %s %s\n", argv[1],"is not completely loaded.");
     printf("Input file size: %ld\n", get_filesize(argv[1]));
    } 
/* set a mark */
  ca_setmark(ptr_Buffer,ca_getsize(ptr_Buffer));

/* display the contents of the input buffer */	  
   display(ptr_Buffer);

/* pack the buffer 
 * if possible, add end-of-file character (EOF) to the buffer
 * display again
 */
  if(ca_pack(ptr_Buffer)){ 
    if(!ca_addc(ptr_Buffer, EOF))
      err_printf("%s%s%s",argv[0],": ","Error in writing to buffer.");
    display(ptr_Buffer);
  }  


/* destroy the buffer */  
  b_destroy(ptr_Buffer);
/* make the buffer invalid
   It is not necessary here because the function terminates anyway,
   but will prevent run-time errors and crashes in future expansions
*/
  ptr_Buffer = NULL;
/*return success */
  return (0);
}

/* error printing function with variable number of arguments*/
void err_printf( char *fmt, ... ){
/*Initialize variable list */   
  va_list ap;
  va_start(ap, fmt);
     
  (void)vfprintf(stderr, fmt, ap);
   va_end(ap);

  /* Move to new line */
  if( strchr(fmt,'\n') == NULL )
     fprintf(stderr,"\n");
}

void display (Buffer *ptr_Buffer){
  printf("\nPrinting buffer parameters:\n\n");
  printf("The capacity of the buffer is:  %d\n",ca_getcapacity(ptr_Buffer));
  printf("The current size of the buffer is:  %d\n",ca_getsize(ptr_Buffer));
  printf("The operational mode of the buffer is:   %d\n",ca_getmode(ptr_Buffer));
  printf("The increment factor of the buffer is:  %u\n",(unsigned char)ptr_Buffer->inc_factor);
  printf("The current mark of the buffer is:  %d\n",ca_getmark(ptr_Buffer));
/*printf("The reallocation flag is:   %d\n",ptr_Buffer->r_flag);*/
  printf("\nPrinting buffer contents:\n\n");
  ca_print(ptr_Buffer);
}

long get_filesize(char  *fname){
   FILE *input;
   long flength;
   input = fopen(fname, "r");
   if(input == NULL)
      err_printf("%s%s","Cannot open file: ",fname);   
   fseek(input, 0L, SEEK_END);
   flength = ftell(input);   
   fclose(input);
   return flength;
}

