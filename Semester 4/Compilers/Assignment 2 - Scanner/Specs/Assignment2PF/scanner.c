/* Filename: scanner.c
/* PURPOSE:
 *    SCANNER.C: Functions implementing a Lexical Analyzer (Scanner)
 *    as required for CST8152, Assignment #2, Summer 11
 *    scanner_init() must be called before using the scanner.
 *    The file is incomplete;
 *    Provided by: Svillen Ranev
 *    Version: 1.11.02
 *    Date: 31 May 2011
 *******************************************************************
 *    REPLACE THIS HEADER WITH YOUR HEADER
 *******************************************************************
 */
#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer type constants */
#include <float.h>   /* floating-point type constants */

/*#define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */
#include "buffer.h"
#include "token.h"
#include "table.h"

#define DEBUG  /* for conditional processing */
#undef  DEBUG

/* Global objects - variables */
/* This buffer is used as a repository for string literals.
   It is defined in platy_st.c */
extern Buffer * str_LTBL; /*String literal table  */
int line; /* current line number of the source code */
extern int scerrnum;     /* defined in platy_st.c - run-time error number */

/* No other global variable declarations/definitiond are allowed */

/* Function prototypes */
static int char_class(char c); /* character class function */
static int get_next_state(int, char, int *); /* state machine function */
static int iskeyword(char * kw_lexeme); /*keywords lookup functuion */
static long atool(char * lexeme); /* converts octal string to decimal value */

void scanner_init(Buffer *buf)
{
        ca_addc(buf, '\0'); /* in case EOF is not in the buffer */
        b_reset(str_LTBL);  /* reset the string literal table */
        line = 1;           /*set the source code line number to 1*/
}

Token malpar_next_token(Buffer * sc_buf)
{
        Token t;         /*token to be returned */
        unsigned char c; /* input symbol */
        Buffer *lex_buf; /* temporary buffer for holding lexemes */       
        int accept = NOAS; /* Not Accepting State */
        int state = 0;     /* Start state in the Transition Table */
        int lexstart;      /* current lexeme start offset */ 
 static int forward =INITIALIZE HERE;  /* current input char offset */                                       
/* 
forward is the offset from the beginning of the char buffer of the
input buffer (sc_buf) to the current character, which is to be processed
by the scanner.
lexstart is the offset from the beginning of the char buffer of the
input buffer (sc_buf) to the first character of the current lexeme,
which is being processed by the scanner.
*/ 
        
        
        DECLARE YOUR VARIABLES HERE IF NEEDED 
        
                
        while (1){ /* endless loop broken by token returns */
                
        GET NEXT SYMBOL FROM THE INPUT BUFFER 
        YOU CAN CHANGE ++forward TO forward++ IF YOU DEEM NECESSARY
        YOUR CHOICE WILL DETERMINE HOW TO INITIALIZE the forward VARIABLE
        c = sc_buf->ca_head[++forward];


              
/* special cases or exceptions processing */

WRITE YOUR CODE FOR PROCESSING THE SPECIAL CASES HERE. 
COMMENTS AND STRING LITERALS ARE ALSO PROCESSED HERE.

WHAT FOLLOWS IS A PSEUDO CODE. YOU CAN USE switch STATEMENT
INSTEAD OF if-else TO PROCESS THE SPECIAL CASES
DO NOT FORGET TO COUNT THE PROGRAM LINES
   
             
   IF (c == SOME CHARACTER)  
                       ...
       SKIP CHARACTER (FOR EXAMPLE SPACE)
       continue;      
       OR SET TOKEN (SET TOKEN CODE AND TOKEN ATTRIBUTE(IF AVAILABLE))
       return t;
   EXAMPLE:
   if (c == ' ') continue;
   if (c == '{'){ t.code = RBR_T; /*no attribute */ return t; 
   if (c == '+'){ t.code = ART_OP_T; t.attribute.arr_op = PLUS */ return t;                 
   ...
   
   IF (c == '.') TRY TO PROCESS .AND. or .OR.
   IF SOMETHING ELSE FOLLOWS . OR THE LAST . IS MISSING
   RETURN AN ERROR TOKEN                                               
   IF (c == '!') TRY TO PROCESS COMMENT
   IF THE FOLLOWING IS NOT CHAR IS NOT < REPORT AN ERROR
   ELSE IN A LOOP SKIP CHARACTERS UNTIL \n THEN continue;
   ...
   IF STRING (FOR EXAMPLE, "TEXT") IS FOUND      
      IF THE STRING IS LEGAL   
         COPY THE TEXT AS C-type STRING INTO str_LTBL  USING ca_addc(..)
         SET STRING TOKEN
         (the attribute of the string token is the offset from
         the beginning of the str_LTBL char buffer to the beginning 
         of the string (TEXT in the example)) 
 
         return t;
      ELSE  
        THE STRING LITERAL IS ILLEGAL
        SET ERROR TOKEN FOR ILLEGAL STRING (see assignment)
        DO NOT STORE THE ILLEGAL STRINg IN THE str_LTBL

        return t;
   
   IF (c == ANOTHER CHARACTER)        
     SET TOKEN
     return t;                 
/* Process state transition table */  
        
  IF (c is a digit OR c is a letter){
  
  SET THE MARK AT THE BEGINING OF THE LEXEME
  ca_setmark(sc_buf,forward);                      
    ....
  CODE YOUR FINATE STATE MACHINE HERE (FSM or DFA)
  IT IMPLEMENTS THE FOLLOWING ALGORITHM:
  
  FSM0. Begin with state = 0 and the input character c 
  FSM1. Get the next state from the transition table calling                       
        state = get_next_state(state, c, &accept);
  FSM2. Get the next character
  FSM3. If the state is not accepting (accept == NOAS), go to step FSM1
        If the step is accepting, token is found, leave the machine and
        call the accepting function as described below.     
   
                        
  CREATE  A TEMPORRARY LEXEME BUFFER HERE;
  GET THE BEGINNING OF THE LEXEME
  lexstart = ca_getmark(sc_buf);
  lex_buf = b_create(...);
   . SET forward  IF THE FINAL STATE IS A RETRACTING FINAL STATE
   . COPY THE LEXEME INTO lex_buf USING ca_addc(...),lexstart AND forward
   . WRITE YOUR CODE HERE
   . WHEN VID (KEYWORDS INCLUDED), FPL OR IL IS RECOGNIZED
   . YOU MUST CALL THE ACCEPTING FUNCTION USING THE ARRAY aa_table ,WHICH
   . CONTAINS POINTERS TO FUNCTIONS. THE ARRAY INDEX OF THE FUNCTION TO BE
   . CALLED IS STORED IN THE VARIABLE state.
   . YOU ARE NOT ALLOWED TO CALL ANY OF THE ACCEPTING FUNCTIONS BY NAME.
   . THE ARGUMENT TO THE FUNCTION IS THE STRING STORED IN lex_buf.
   ....
    b_destroy(lex_buf);
   return t;
      
     CHECK OTHER CHARS HERE if NEEDED, SET A TOKEN AND RETURN IT.
     FOR ILLEGAL CHARACTERS SET ERROR TOKEN. 
     THE ILLEGAL CHAR IS THE ATTRIBUTE OF THE ERROR TOKEN 
     IN A CASE OF RUNTIME ERROR, THE FUNCTION MUST STORE 
     A NON-NEGATIVE NUMBER INTO THE GLOBAL VARIABLE scerrnum
     AND RETURN AN ERROR TOKEN. THE ERROR TOKEN ATTRIBUTE MUST
     BE THE STRING "RUN TIME ERROR: "                
   }//end while(1)
}


DO NOT MODIFY THE CODE OF THIS FUNCTION
YOU CAN REMOVE THE COMMENTS

int get_next_state(int state, char c, int *accept)
{
	int col;
	int next;
	col = char_class(c);
	next = st_table[state][col];
#ifdef DEBUG
printf("Input symbol: %c Row: %d Column: %d Next: %d \n",c,state,col,next);
#endif
/*
The assert(int test) macro can be used to add run-time diagnostic to programs
and to "defend" from producing unexpected results.
assert() is a macro that expands to an if statement;
if test evaluates to false (zero) , assert aborts the program
(by calling abort()) and sends the following message on stderr:

Assertion failed: test, file filename, line linenum

The filename and linenum listed in the message are the source file name
and line number where the assert macro appears.
If you place the #define NDEBUG directive ("no debugging")
in the source code before the #include <assert.h> directive,
the effect is to comment out the assert statement.
*/
       assert(next != IS);

/*
The other way to include diagnostics in a program is to use
conditional preprocessing as shown bellow. It allows the programmer
to send more details describing the run-time problem. 
Once the program is tested thoroughly #define DEBUG is commented out
or #undef DEBUF is used - see the top of the file.
*/ 
#ifdef DEBUG
	if(next == IS){
	  printf("Scanner Error: Illegal state:\n");
	  printf("Input symbol: %c Row: %d Column: %d\n",c,state,col);
	  exit(1);
	}
#endif
	*accept = as_table[next];
	return next;
}

int char_class (char c)
{
        int val;

THIS FUNCTION RETURNS THE COLUMN NUMBER IN THE TRANSITION
TABLE st_table FOR THE INPUT CHARACTER c.
SOME COLUMNS MAY REPRESENT A CHARACTER CLASS .
FOR EXAMPLE IF COLUMN 1 REPRESENTS [A-Z]
THE FUNCTION RETURNS 1 EVERY TIME c IS ONE
OF THE LETTERS A,B,...,Z.
        
        return val;
}



HERE YOU WRITE THE DEFINITIONS FOR YOUR ACCEPTING FUNCTIONS. 

ACCEPTING FUNCTION FOR THE variable identifier (VID)
REPLACE XX WITH THE CORRESPONDING ACCEPTING STATE NUMBER

Token aa_funcXX(char lexeme[]){

WHEN CALLED THE FUNCTION MUST
1. CHECK IF THE LEXEME IS A KEYWORD.
   IF YES, IT MUST RETURN A TOKEN WITH THE CORRESPONDING ATTRIBUTE
   FOR THE KEYWORD. THE ATTRIBUTE CODE FOR THE KEYWORD
   IS ITS INDEX IN THE KEYWORD LOOKUP TABLE (kw_table in table.h).
   IF THE LEXEME IS NOT A KEYWORD, GO TO STEP 2.

2. CHECK THE LAST CHARACTER OF THE lexeme.
   IF IT IS # IT SETS a SVID TOKEN, OTHERWISE IT SETS a AVID TOKEN.
   IF THE lexeme IS LONGER than VID_LEN (see token.h) CHARACTERS,
   ONLY FIRST VID_LEN CHARACTERS ARE STORED
   INTO THE VARIABLE ATTRIBUTE ARRAY vid_lex[].
   
   IN THE CASE OF THE SVID (STRING VARIABLE)
   IF THE lexime IS LONGER than VID_LEN characters,
   ONLY FIRST VID_LEN-1 CHARACTERS ARE STORED
   INTO THE VARIABLE ATTRIBUTE ARRAY vid_lex[],
   AND THEN THE # CHARACTER IS APPENDED TO THE NAME.

  return t;
}



ACCEPTING FUNCTION FOR THE floating-point literal (FPL)

Token aa_funcXX(char lexeme[]){

THE FUNCTION MUST CONVERT THE LEXEME TO A FLOATING POINT VALUE,
WHICH IS THE ATTRIBUTE FOR THE TOKEN.
THE VALUE MUST BE IN THE SAME RANGE AS the value of 4-byte float in C.
IN CASE OF ERROR (OUT OF RANGE) THE FUNCTION MUST RETURN ERROR TOKEN
THE ERROR TOKEN ATTRIBUTE IS  lexeme
  return t;
}

ACCEPTING FUNCTION FOR THE integer literal(IL) - decimal constant (DIL)

Token aa_funcXX(char lexeme[]){

THE FUNCTION MUST CONVERT THE LEXEME REPRESENTING A DECIMAL CONSTANT
TO A DECIMAL INTEGER VALUE, WHICH IS THE ATTRIBUTE FOR THE TOKEN.
THE VALUE MUST BE IN THE SAME RANGE AS the value of 2-byte int in C.
IN CASE OF ERROR (OUT OF RANGE) THE FUNCTION MUST RETURN ERROR TOKEN
THE ERROR TOKEN ATTRIBUTE IS  lexeme
  return t;
}

ACCEPTING FUNCTION FOR THE integer literal(IL) - octal constant (OIL)

Token aa_funcXX(char lexeme[]){

THE FUNCTION MUST CONVERT THE LEXEME REPRESENTING AN OCTAL CONSTANT
TO A DECIMAL INTEGER VALUE WHICH IS THE ATTRIBUTE FOR THE TOKEN.
THE VALUE MUST BE IN THE SAME RANGE AS the value of 2-byte int in C.
THIS FUNCTION IS SIMILAR TO THE FUNCTION ABOVE AND THEY CAN BE
COMBINED INTO ONE FUNCTION
THE MAIN DIFFERENCE IE THAT THIS FUNCTION CALLS
THE FUNCTION atool(char * lexeme) WHICH CONVERTS AN ASCII STRING
REPRESENTING AN OCTAL NUMBER TO INTEGER VALUE
IN CASE OF ERROR (OUT OF RANGE) THE FUNCTION MUST RETURN ERROR TOKEN
THE ERROR TOKEN ATTRIBUTE IS  lexeme

  return t;
}

ACCEPTING FUNCTION FOR THE ERROR TOKEN 

Token aa_funcXX(char lexeme[]){

THE FUNCTION SETS THE ERROR TOKEN. lexeme[] CONTAINS THE ERROR
THE ATTRIBUTE OF THE ERROR TOKEN IS THE lexeme ITSELF
AND IT MUST BE STORED in err_lex.  IF THE ERROR LEXEME IS LONGER
than ERR_LEN caharacters, only the first ERR_LEN character are
stored in err_lex.

  return t;
}


CONVERSION FUNCTION

long atool(char * lexeme){

THE FUNCTION CONVERTS AN ASCII STRING
REPRESENTING AN OCTAL INTEGER CONSTANT TO INTEGER VALUE
}

HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
FOR EXAMPLE

int iskeyword(char * kw_lexeme){}