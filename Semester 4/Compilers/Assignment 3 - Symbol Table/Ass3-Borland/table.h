/* File Name: table.h
 * Version: 1.12
 * Author: William Collins (040652633) && Svillen Ranev     
 * Course: CST8152 - Compilers
 * Assignment: 2
 * Date: June 30, 2011
 * Professor: Svillen Ranev
 * Purpose: Transition table and functions used by the scanner
 */

#ifndef  TABLE_H_
#define  TABLE_H_ 

#ifndef BUFFER_H_
#include "buffer.h"
#endif

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

#define ES 11	/* Error state */
#define IS -1   /* Inavalid state */

/* Accepting state function prototypes */
Token aa_func02(char *lexeme);
Token aa_func07(char *lexeme);
Token aa_func08(char *lexeme);
Token aa_func09(char *lexeme);
Token aa_func11(char *lexeme);

/* State transition table definition */ 
#define TABLE_COLUMNS 7

/*transition table - type of states defined in separate table */
int  st_table[ ][TABLE_COLUMNS] = {
/* State 0 */  {1, 4, 3, 3, IS, IS, IS},
/* State 1 */  {1, 1, 1, 1, 2, 10, 2},
/* State 2 */  {IS, IS, IS, IS, IS, IS, IS},
/* State 3 */  {ES, 3, 3, 3, 6, 7, 7},
/* State 4 */  {ES, ES, ES, 5, 6, 7, 7},
/* State 5 */  {ES, 5, ES, 5, ES, ES, 9},
/* State 6 */  {8, 6, 6, 6, 8, 8, 8},
/* State 7 */  {IS, IS, IS, IS, IS, IS, IS},
/* State 8 */  {IS, IS, IS, IS, IS, IS, IS},
/* State 9 */  {IS, IS, IS, IS, IS, IS, IS},
/* State 10 */ {ES, ES, ES, ES, ES, ES, 2},
/* State 11 */ {IS, IS, IS, IS, IS, IS, IS}
};

/* Accepting state table definition */
#define ASWR     2  /* accepting state with retract */
#define ASNR     1  /* accepting state with no retract */
#define NOAS     0  /* not accepting state */

int as_table[ ] = {      
	NOAS,	/*0*/
	NOAS,	/*1*/
	ASWR,	/*2*/
	NOAS,	/*3*/
	NOAS,	/*4*/
	NOAS,	/*5*/
	NOAS,	/*6*/
	ASWR,	/*7*/
	ASWR,	/*8*/
	ASWR,	/*9*/
	NOAS,	/*10*/
	ASNR	/*11*/
};

/* defining a new type: pointer to function (of one char * argument) 
   returning Token*/ 
typedef Token (*PTR_AAF)(char *lexeme);

/* Callback table used to handle accepting states */
PTR_AAF aa_table[ ] ={
	NULL,		/*0*/
	NULL,		/*1*/
	aa_func02,	/*2*/
	NULL,		/*3*/
	NULL,		/*4*/
	NULL,		/*5*/
	NULL,		/*6*/
	aa_func07,	/*7*/
	aa_func08,	/*8*/
	aa_func09,	/*9*/
	NULL,		/*10*/
	aa_func11	/*11*/
};

/* A list of our keywords */
#define KWT_SIZE  8 /* The size of the keyword table */
char * kw_table []= {
	"ELSE",
	"IF",
	"INPUT",
	"OUTPUT",
	"PLATYPUS",
	"REPEAT",
	"THEN",
	"USING"   
};

#endif
                     