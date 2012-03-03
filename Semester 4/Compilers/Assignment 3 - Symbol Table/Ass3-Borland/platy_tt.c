/* File name: platy_tt.c
 * Purpose:This is the main program for Assignment #3, CST8152, S11)
 * Version: 1.11.02
 * Author: Svillen Ranev
 * Date: 30 June 2011
 */ 

#include <stdio.h>
#include <stdlib.h> /* Constants for calls to exit()*/

#include <string.h>
#include <stdarg.h>

#include "buffer.h"
#include "token.h"
#include "stable.h" /*Do not remove this line. SiR */
#include "stable.h" /*Do not remove this line. SiR */

/* constant definitions */
/* Input buffer parameters */
#define INIT_CAPACITY 200 /* initial buffer capacity */
#define INC_FACTOR 15       /* increment factor */
/* String Literal Table parameters */
#define STR_INIT_CAPACITY 100 /* initial string literal table capacity */
#define STR_CAPACITY_INC  50   /* initial string literal table capacity inc */
/* Symbol Table default size */
#define ST_DEF_SIZE 100 

/*check for ANSI C compliancy */
#define ANSI_C 0
#if defined(__STDC__)
#undef ANSI_C
#define ANSI_C 1
#endif

/* Global objects - variables */

static Buffer *sc_buf; /* pointer to input (source) buffer */
Buffer * str_LTBL; /* this buffer implements String Literal Table */
                  /* it is used as a repository for string literals */
int scerrnum;     /* run-time error number = 0 by default (ANSI) */
STD sym_table;    /* Symbol Table Descriptor */

/*external objects */
extern int line; /* source code line numbers - defined in scanner.c */
extern void scanner_init(Buffer * sc_buf);
extern Token malpar_next_token(Buffer * sc_buf);
/*function declarations */
void err_printf(char *fmt, ...);
void display (Buffer *ptrBuffer); 
long get_filesize(char *fname);
void garbage_collect(void);

/*  The main function takes a PLATYPUS source file and optional switches
 *  as command line arguments.
 *  usage: platytt source_file_name [-stz size][-sts:A | -sts:D]
 */    
int main(int argc, char ** argv){

	FILE *fi;       /* input file handle */
	Token t;        /* token produced by the scanner */
        int loadsize = 0; /*the size of the file loaded in the buffer */
        int st_def_size = ST_DEF_SIZE; /* Sumbol Table default size */
        char sort_st = 0;      /*Symbol Table sort switch */
        int ansi_c = !ANSI_C; /* ANSI C flag */
/* Check if the compiler option is set to compile ANSI C */
/* __DATE__, __TIME__, __LINE__, __FILE__, __STDC__ are predefined preprocessor macros*/
  if(ansi_c){
    err_printf("Date: %s  Time: %s",__DATE__, __TIME__);
    err_printf("ERROR: Compiler is not ANSI C compliant!\n");
    exit(1);
  }

/*check for correct arrguments - source file name */
      if (argc <= 1){
/* __DATE__, __TIME__, __LINE__, __FILE__ are predefined preprocessor macros*/
       err_printf("Date: %s  Time: %s",__DATE__, __TIME__);
       err_printf("Runtime error at line %d in file %s", __LINE__, __FILE__);
       err_printf("%s%s%s",argv[0],": ","Missing source file name.");
       err_printf("%s%s%s","Usage: ", "platytt", "  source_file_name [-stz size][-sts:A | -sts:D]");
        exit(EXIT_FAILURE);
	}	

 /* check for optional switches - symbol table size and/or sort */
 if (argc == 3){
    if (strcmp(argv[2],"-sts:A") && strcmp(argv[2],"-sts:D") ){
      err_printf("%s%s%s",argv[0],": ","Invalid switch.");
      err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
      exit(EXIT_FAILURE);
    }
/*set sort switch*/
    if(strcmp(argv[2],"-sts:A"))
     sort_st = 'D';
    else 
     sort_st = 'A';
 }
/* symbol table size specified */ 
 if (argc == 4){
   if (strcmp(argv[2],"-stz")){
     err_printf("%s%s%s",argv[0],": ","Invalid switch.");
     err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
     exit(EXIT_FAILURE);
   }
/* convert the symbol table size */
    st_def_size = atoi(argv[3]);
      if (st_def_size <= 0){
	err_printf("%s%s%s",argv[0],": ","Invalid switch.");
	err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
	exit(EXIT_FAILURE);
      }
 }
if (argc == 5){  
    if (strcmp(argv[2],"-stz")){
     err_printf("%s%s%s",argv[0],": ","Invalid switch.");
     err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
     exit(EXIT_FAILURE);
   }
/* convert the symbol table size */
    st_def_size = atoi(argv[3]);
      if (st_def_size <= 0){
	err_printf("%s%s%s",argv[0],": ","Invalid switch.");
	err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
	exit(EXIT_FAILURE);
   }
    
    if (strcmp(argv[4],"-sts:A")&& strcmp(argv[4],"-sts:D") ){
      err_printf("%s%s%s",argv[0],": ","Invalid switch.");
      err_printf("%s%s\b\b\b\b%s","Usage: ", argv[0], " source file name [-stz size][-sts:A | -sts:D]");
      exit(EXIT_FAILURE);
    }

   if(strcmp(argv[4],"-sts:A"))
     sort_st = 'D';
    else 
     sort_st = 'A';
 }

/* create a source code input buffer - multiplicative mode */	
	sc_buf = b_create(INIT_CAPACITY,INC_FACTOR,'m');
	if (sc_buf == NULL){
	  err_printf("%s%s%s",argv[0],": ","Could not create source buffer");
	  exit(EXIT_FAILURE);
	}

/* create symbol table */
  sym_table = st_create(st_def_size);
  if (!sym_table.st_size){
    err_printf("%s%s%s",argv[0],": ","Could not create symbol table");
    exit (EXIT_FAILURE);
  }

/*open source file */
	if ((fi = fopen(argv[1],"r")) == NULL){
		err_printf("%s%s%s%s",argv[0],": ", "Cannot open file: ",argv[1]);
		exit (1);
	}
/* load source file into input buffer  */
     printf("Reading file %s ....Please wait\n",argv[1]);
     loadsize = ca_load (fi,sc_buf);
     if(loadsize == R_FAIL_1)
       err_printf("%s%s%s",argv[0],": ","Error in loading buffer.");

/* close source file */	
 	fclose(fi);
/*find the size of the file  */
    if (loadsize == LOAD_FAIL){
     printf("The input file %s %s\n", argv[1],"is not completely loaded.");
     printf("Input file size: %ld\n", get_filesize(argv[1]));
    }
/* pack and display the source buffer */

       if(ca_pack(sc_buf)){
         display(sc_buf);
  }

/* create string Literal Table */	
  str_LTBL = b_create(INIT_CAPACITY,INC_FACTOR,'a');
	if (str_LTBL == NULL){
	 err_printf("%s%s%s",argv[0],": ","Could not create string buffer");
	 exit(EXIT_FAILURE);
	}

/*registrer exit function */	
 atexit(garbage_collect);
	
/*Testbed for the scanner and the symbol table*/

/* Initialize the scanner input buffer */ 
	scanner_init(sc_buf);
        
        printf("Scanning source file...\n\n");

	do{
	  t= malpar_next_token(sc_buf);
	}while(t.code != SEOF_T);
/* print Symbol Table */      
       if(sym_table.st_size){
         st_print(sym_table);
         if(sort_st){
           printf("\nSorting symbol table...\n");
           st_sort(sym_table,sort_st);
           st_print(sym_table);
         }
       }
/*Testbed for update functions */

	return (0); /* same effect as exit(EXIT_SUCCESS) */
}

/* Error printing function with variable number of arguments
 */
void err_printf( char *fmt, ... ){

  va_list ap;
  va_start(ap, fmt);

  (void)vfprintf(stderr, fmt, ap);
	va_end(ap);

  /* Move to new line */
  if( strchr(fmt,'\n') == NULL )
	  fprintf(stderr,"\n");
}

/* The function return the size of an open file 
 */
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

/* The function display buffer contents 
 */
void display (Buffer *ptrBuffer){
  printf("\nPrinting input buffer parameters:\n\n");
  printf("The capacity of the buffer is:  %d\n",ca_getcapacity(ptrBuffer));
  printf("The current size of the buffer is:  %d\n",ca_getsize(ptrBuffer));
  printf("The reallocation flag is:   %d\n",ptrBuffer->r_flag);
  printf("\nPrinting input buffer contents:\n\n");
  ca_print(ptrBuffer);
}

/* the functions frees the allocated memory */
void garbage_collect(void){
  printf("\nCollecting garbage...\n");
	b_destroy(sc_buf);
	b_destroy(str_LTBL);  
	st_destroy(sym_table);
}


