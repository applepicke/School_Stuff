/* File Name: buffer.h
 * Version: 1.12
 * Author: William Collins (040652633) && Svillen Ranev     
 * Course: CST8152 - Compilers
 * Assignment: 1
 * Date: May 18, 2011
 * Professor: Svillen Ranev
 * Purpose: Declarations and prototypes necessary for the buffer utility.
 */

#ifndef BUFFER_H_
#define BUFFER_H_

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type limits */

/* constant definitions */
#define R_FAIL_1 -1			/* fail return value */
#define R_FAIL_2 -2			/* fail return value */
#define LOAD_FAIL -2		/* load fail error */
#define SET_R_FLAG 1		/* realloc flag set value */

#define MULTI_MIN 1			/* minimum allowed increment in multiplicative mode */
#define MULTI_MAX 100		/* maximum allowed increment in multiplicative mode */

#define FIXED 0				/* specifies fixed mode buffer */
#define ADDITIVE 1			/* specifies an additive self-incrementing buffer */
#define MULTIPLICATIVE -1	/* specifies a multiplicative self-incrementing buffer */


/* user data type declarations */
typedef struct BufferDescriptor {
       char *ca_head ;    /* pointer to the beginning of character array (character buffer) */
       int capacity ;      /* current dynamic memory size (in bytes) allocated to character buffer */
       char inc_factor;    /* character array increment factor */
       int addc_offset ;    /* the offset (in char elements) to the app-character location */
       int mark_offset ;   /* the offset (in chars elements) to the mark location */
       char r_flag;        /* reallocation flag */
       char mode;          /* operational mode indicator*/
} Buffer ;



/* function declarations */
Buffer *b_create(int init_capacity, char inc_factor,char o_mode);
Buffer *ca_addc(Buffer *pB, char symbol);
int b_reset (Buffer *pB);
void b_destroy (Buffer *pB);
char ca_isfull (Buffer *pB);
int ca_getsize (Buffer *pB);
int ca_getcapacity (Buffer *pB);
int ca_setmark (Buffer *pB, int mark);
int ca_getmark (Buffer *pB);
int ca_getmode (Buffer *pB);
Buffer *ca_pack( Buffer *pB );
int ca_print (Buffer *pB);
int ca_load (FILE *fi,Buffer *pB);

#endif
