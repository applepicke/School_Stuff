/* Filename: table.h
 * Transition Table and function declarations necessary for the scanner  
 * as required for CST8152, Assignment #2, Summer 11.
 * Version: 1.11.02
 * The file is incomplete. You are to complete it.
 * Provided by: Svillen Ranev 
 ***************************************************
 * REPLACE THIS HEADER WITH YOUR HEADER
 ***************************************************
 */

#ifndef  TABLE_H_
#define  TABLE_H_ 

#ifndef BUFFER_H_
#include "buffer.h"
#endif

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*   Source end-of-file (SEOF) sentinel symbol
 *    '\0' or 255 or 0xFF or EOF
 */

/*  Single-lexeme tokens processed separately one by one
 *  in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , != , '>' , '<' ,
 *       space
 *  !<comment , ',' , '"' , ';' , '-' , '+' , '*' , '/', << ,
 *  .AND., .OR. , SEOF, 'wrong symbol',
 */
 

REPLACE *ESN* WITH YOUR ERROR STATE NUMBER 
#define ES  *ESN* /* Error state */
#define IS -1    /* Inavalid state */

/* State transition table definition */

REPLACE *CN* WITH YOUR COLUMN NUMBER  

#define TABLE_COLUMNS *CN*
/*transition table - type of states defined in separate table */
int  st_table[ ][TABLE_COLUMNS] = {
/* State 0 */  {YOUR INITIALIZATION},
/* State 1 */  {YOUR INITIALIZATION},
.
. YOUR TABLE INITIALIZATION HERE
.
/* State N */  {YOUR INITIALIZATION}, 
 
/* Accepting state table definition */
REPLACE *N1*, *N2*, and *N3* WITH YOUR NUMBERS
#define ASWR     *N1*  /* accepting state with retract */
#define ASNR     *N2*  /* accepting state with no retract */
#define NOAS     *N3*  /* not accepting state */

int as_table[ ] = {YOUR INITIALIZATION HERE - USE ASWR, ASNR, NOAS };

/* Accepting action function declarations */

FOR EACH OF YOUR ACCEPTING STATES YOU MUST PROVIDE
ONE FUNCTION PROTOTYPE. THEY ALL RETURN Token AND TAKE
ONE ARGUMENT: A string REPRESENTING A TOKEN LEXEME. 

Token aa_funcXX(char *lexeme); 

Replace XX with the number of the accepting state: 01, 03 and so on.

/* defining a new type: pointer to function (of one char * argument) 
   returning Token
*/  

typedef Token (*PTR_AAF)(char *lexeme);


/* Accepting function (action) callback table (array) definition */
/* If you do not want to use the typedef, the equvalent declaration is:
 * Token (*aa_table[])(char lexeme[]) = {
 */

PTR_AAF aa_table[ ] ={


HERE YOU MUST PROVIDE AN INITIALIZATION FOR AN ARRAY OF POINTERS
TO ACCEPTING FUNCTIONS. THE ARRAY HAS THE SAME SIZE AS as_table[ ].
YOU MUST INITIALIZE THE ARRAY ELEMENTS WITH THE CORRESPONDING
ACCEPTING FUNCTIONS (FOR THE STATES MARKED AS ACCEPTING IN as_table[]).
THE REST OF THE ELEMENTS MUST BE SET TO NULL.

};

/* Keyword lookup table (.AND. and .OR. are not keywords) */

#define KWT_SIZE  8

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
                     