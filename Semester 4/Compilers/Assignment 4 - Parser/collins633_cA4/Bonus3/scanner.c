/* File Name: buffer.h
 * Version: 1.12
 * Author: William Collins (040652633) && Svillen Ranev     
 * Course: CST8152 - Compilers
 * Assignment: 2
 * Date: June 30, 2011
 * Professor: Svillen Ranev
 * Purpose: A token driven lexical analyzer used to get tokens from a file
 */
#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer type constants */
#include <float.h>   /* floating-point type constants */
#include <math.h>

/*#define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */
#include "buffer.h"
#include "token.h"
#include "table.h"
#include "stable.h"

#define DEBUG  /* for conditional processing */
#undef  DEBUG

/*Globals*/
extern Buffer * str_LTBL;	/*String literal table  */
int line;					/* current line number of the source code */
extern int scerrnum;		/* defined in platy_tt.c - run-time error number */
extern STD sym_table;		/* defined in platy_tt.c - symbol table */
int forward;

/* Function prototypes */
static int char_class(char c);					/* character class function */
static int get_next_state(int, char, int *);	/* state machine function */
static int iskeyword(char * kw_lexeme);			/*keywords lookup functuion */
static long atool(char * lexeme);				/* converts octal string to decimal value */
static int isEOF(unsigned char c);				/*tests a symbol for end of file*/
static int install_vid(char *lexeme);


/*Token generation function prototypes. Lazy people unite! */
/* NOTE: I know you don't like function calls, but I do have a reason for using
them. These functions make the code much easier to read, and promote code resuse.
The performance loss in using function calls where I have used them is very
minimal, and would only be a factor in embedded systems. So please don't take away marks. Sincerely, #V
PS. Thanks for reading my long comment
PPS. Also, to make you even more upset with my program, instead of
returning a pointer to a token I am letting it return a copy of the
token. Again, it makes it look clean and simple, and I like clean and simple.
Just be aware that I understand why my code may lose performance.
If n is the number of tokens in a file, then my functions are called once per token. 
O(n). It's scalable.
I'll be quiet now. And yes, I am aware of the irony of having a super long ugly
comment telling you how I like my code to look pretty.*/
Token createErrorToken(unsigned int msg_len, const char *err_msg);
Token createIntValToken(int code, int attribute);
Token createRelOpToken(Rel_Op attribute);
Token createEmptyToken(int code);
Token createArrOpToken(Arr_Op attribute);
Token createLogOpToken(Log_Op attribute);
Token createFltValToken(float attribute);

/*
 * Purpose: Initialized the scanner for use
 * Author: Svillen Ranev
 * History/Versions: 1.0
 * Parameters:	buf - a pointer to the buffer to initialize the scanner with
 */
void scanner_init(Buffer *buf)
{
	ca_addc(buf, '\0'); /* in case EOF is not in the buffer */
	b_reset(str_LTBL);  /* reset the string literal table */
	line = 1;           /*set the source code line number to 1*/
}

/*
 * Purpose: Scans the buffer and returns the next token
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pB - pointer to the buffer to scan			   
 * Return value: The token found
 */
Token malpar_next_token(Buffer * sc_buf)
{
	Token t;         /*token to be returned */
	unsigned char c; /* input symbol */
	Buffer *lex_buf; /* temporary buffer for holding lexemes */       
	int accept = NOAS; /* Not Accepting State */
	int state = 0;     /* Start state in the Transition Table */
	int lexstart;      /* current lexeme start offset */ 
	char *text = sc_buf->ca_head; /*A shortcut to the data in the buffer*/
	char re_msg[] = "RUN TIME ERROR: "; /*runtime error message*/
    
	t.code = -1;
	/* An assertion seems most appropriate. No buffer coming in here should ever be NULL*/
	assert(sc_buf != NULL);
	
    while (1) {

		c = text[forward++];

		/*Handle white space*/
		if (c == ' ' || c == '\t'){
			continue;
		}

		/*Handle the new line*/
		if (c == '\n'){
			line++;
			continue;
		}

		/*Handle Comments*/
		if (c == '!'){

			/*Handle the "Not equals" case*/
			if (text[forward] == '='){
				forward++;
				return createRelOpToken(NE);
			}
         
      		/*If not a comment, then we have an error*/
			if (text[forward] != '<'){
				t = createErrorToken(2, text + forward -1);
				forward++;
			}
         
			/*It is a comment, skip everything until we reach a new line*/
			while (text[forward] != '\n' && !isEOF(text[forward])){
				forward++;
			}

			/*Now if we had an error, let's return the token*/
			if (t.code == ERR_T) {
				printf("the spot is %c\n",c);
         		return t;
			}
			continue;
		}

		/*Check to see if we're at end of file. */
		if (isEOF(c)){
			return createEmptyToken(SEOF_T);
		}

		/*Logical Operators*/
		if (c == '.') {
			int i = forward;

			/* We found .AND.*/
			if (text[i++] == 'A' && text[i++] == 'N' && text[i++] == 'D' && text[i++] == '.'){
         		forward = i;
				return createLogOpToken(AND);
			}
			i = forward; /*need to reset our offset*/
			
			/* We found .OR. */
			if (text[i++] == 'O' && text[i++] == 'R' && text[i++] == '.'){
         		forward = i;
				return createLogOpToken(OR);
			}

			/*We have an error*/
			return createErrorToken(1, text + forward-1);
		}
		/*String Literal*/
		if (c == '"'){
			int i;
 
			/*Find out if we have a good string or a bad string*/
			for (i = forward; !isEOF(text[i]) && text[i] != '"'; i++);

			/* The string is a good string, so add it to our literal table*/
			if (text[i] == '"'){
         		int j;

				/*Add the string to the literal table, taking into account line numbers*/
				for (j = 1; forward < i; forward++, j++){
					if (text[forward] == '\n') { 
						line++; 
					}
					str_LTBL = ca_addc(str_LTBL, text[forward]);
				}
				forward++;

				/*Every string literal has a null terminator*/
				str_LTBL = ca_addc(str_LTBL, '\0');

				/*catch any run-time errors*/
				if (str_LTBL == NULL){
					scerrnum = 1;
					return createErrorToken(strlen(re_msg), re_msg);
				}
				
				/*Set up the mark for the next string literal*/
				ca_setmark(str_LTBL, str_LTBL->addc_offset);
				
				return createIntValToken(STR_T, ca_getmark(str_LTBL) - j);

			}
			forward--; /* For a bad string we need to include the front quote*/

			/*Now we can handle a string literal error */
			for (i = 0; !isEOF(text[forward]); i++, forward++){
				if (text[forward] == '\n') {
					line++;
				}
			}
         
			t = createErrorToken(i, text+forward-i);

			/*Now that we have the string, if it is too long we substitute some dots*/ 
			if (i >= ERR_LEN){
      			t.attribute.err_lex[ERR_LEN - 3] = '.';
				t.attribute.err_lex[ERR_LEN - 2] = '.';
				t.attribute.err_lex[ERR_LEN - 1] = '.';
			}
			return t;				
		}
               
		/* Variable Identifiers, Integer Literals, Octal Literals*/
		if (isalnum(c)){
			int i;

			ca_setmark(sc_buf, forward-1);

			/*Finite state machine*/
			for (i = forward; !accept; i++) {
				state = get_next_state(state, c, &accept);
				c = text[i];
			}

			/*The value of ASWR and ASNR will decide how far to go back*/
			forward = i - as_table[state];
         
			/*create the buffer to hold the lexeme temporarily*/
			lex_buf = b_create(VID_LEN, 10, 'a');

			/*Add the lexeme to the buffer*/
			for(lexstart = ca_getmark(sc_buf) ; lexstart < forward; lexstart++){
         		lex_buf = ca_addc(lex_buf, text[lexstart]);
			}
			lex_buf = ca_addc(lex_buf, '\0');

			/*Make sure we didn't have any problems with our buffer*/
			if (lex_buf == NULL){
				scerrnum = 1;
				return createErrorToken(strlen(re_msg), re_msg);
			}

			/*Go to our appropriate accepting state function */
			t = aa_table[state](lex_buf->ca_head);
			b_destroy(lex_buf);

			return t;
		}   
      
		/*Equals sign*/
		if (c == '='){
      
			/*If followed by another, we have a relational op*/
			if (text[forward] == '='){
				forward++;
				return createRelOpToken(EQ);
			}
         
			/*It is an assignment operator*/
			return createEmptyToken(ASS_OP_T);
		}
      
		/*Some Relational Operators*/
		if (c == '<') { 

			/*We have a string catenation operator*/
			if (text[forward] == '<') {
         		forward++;
				return createEmptyToken(SCC_OP_T);
			}
         
			/*We have a relational operator*/
			return createRelOpToken(LT);
		}
		if (c == '>') { return createRelOpToken(GT); }
	
		/*Parentheses and braces*/
		if (c == '('){ return createEmptyToken(LPR_T); }
		if (c == ')'){ return createEmptyToken(RPR_T); }
		if (c == '{'){ return createEmptyToken(LBR_T); }
		if (c == '}'){ return createEmptyToken(RBR_T); }

		/*Arithmetic Operators*/
		if (c == '+') { return createArrOpToken(PLUS); }
		if (c == '-') { return createArrOpToken(MINUS); }
		if (c == '/') { return createArrOpToken(DIV); }
		if (c == '*') { return createArrOpToken(MULT); }

		/*Assorted characters. 50% off*/
		if (c == ',') { return createEmptyToken(COM_T); }
		if (c == ';') { return createEmptyToken(EOS_T); }

		/*All other characters are not allowed*/
		return createErrorToken(1,(char *) &c);
	}
}

/*
 * Purpose: Gets the next state in the transition table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters: state - the current state of the DFA. Must be an existing state.
 					c - The symbol to be analyzed
               accept - points to the current type of state we are in
 * Return value: The next state in the DFA
 */
int get_next_state(int state, char c, int *accept)
{
	int col;
	int next;
	col = char_class(c);
	next = st_table[state][col];

	#ifdef DEBUG
	printf("Input symbol: %c Row: %d Column: %d Next: %d \n",c,state,col,next);
	#endif
    assert(next != IS);

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

/*
 * Purpose: Determine what column of the transition table a symbol represents
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	c - The symbol to be checked			   
 * Return value: A column of the transition table
 */
int char_class (char c)
{
	int val;

	if (isalpha(c)){ val = 0; }					/* COLUMN 0: ascii letter */
	else if (c == '0') { val = 1; }				/* COLUMN 1: zero */
	else if (c == '8' || c == '9'){ val = 2; }	/* COLUMN 2: 8 or 9 */
	else if (isdigit(c)) { val = 3; }			/* COLUMN 3: 1-7 */
	else if (c == '.') { val = 4; }				/* COLUMN 4: . */
	else if (c == '#') { val = 5; }				/* COLUMN 5: # */
	else { val = 6; }							/* COLUMN 6: other */
        
	return val;
}

/*
 * Purpose: Accepting state function for variables and keywords
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme produced by the finite state machine
 * Return value: A token representing the variable or keyword
 */
Token aa_func02(char *lexeme){
	int i, offset;
   
	/*Lexeme is a keyword*/
	if ( (i = iskeyword(lexeme)) != -1){ 
   		return createIntValToken(KW_T, i);
	}

	/*Lexeme is an SVID*/
	if (lexeme[strlen(lexeme)-1] == '#'){

		/*Make sure we keep the '#' if the variable is longer than VID_LEN*/
		lexeme[VID_LEN-1] = '#';
		lexeme[VID_LEN] = '\0';

		offset = install_vid(lexeme);
   		return createIntValToken(SVID_T, offset);
	}

	/*Lexeme is an AVID*/
	lexeme[VID_LEN] = '\0';
	offset = install_vid(lexeme);

	return createIntValToken(AVID_T, offset);
}

/*
 * Purpose: Accepting state function for Integer Literals
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme produced by the finite state machine			   
 * Return value: A token representing the Integer Literal
 */
Token aa_func07(char *lexeme){
	long decimal = atol(lexeme);

	/*In case of overflow or underflow. */
	if (decimal < 0 || decimal > PLATY_INT_MAX || strlen(lexeme) > INL_LEN){
		return createErrorToken(strlen(lexeme), lexeme);
	}

	return createIntValToken(INL_T, (int)decimal);
}

/*
 * Purpose: Accepting state function for Floating Point Literals
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme produced by the finite state machine			   
 * Return value: A token representing the floating point literal
 */
Token aa_func08(char *lexeme){

	double flt = atof(lexeme);

	/*Check for float overflow. 4 bytes is all we allow */
	if (flt < FLT_MIN && flt > 0 || flt > FLT_MAX){
		return createErrorToken(strlen(lexeme), lexeme);
	}

	return createFltValToken((float)flt);

}

/*
 * Purpose: Accepting state function for Octal Literals
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme produced by the finite state machine			   
 * Return value: A token representing the octal literal
 */
Token aa_func09(char *lexeme){

	long octal = atool(lexeme);  /* Just using "a tool" of mine ;) */

	if ( octal < 0 || octal > SHRT_MAX){
		return createErrorToken(strlen(lexeme), lexeme);
	}
	return createIntValToken(INL_T, (int) octal);

}

/*
 * Purpose: Accepting state function for Errors
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme produced by the finite state machine
 * Return value: An error Token
 */
Token aa_func11(char *lexeme){
	return createErrorToken(strlen(lexeme), lexeme);
}

/*
 * Purpose: Converts an octal number in the form of a string to its integer value
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - The lexeme to be converted
 * Return value: The integer value of the octal string
 */
long atool(char * lexeme){
	/*The second argument is NULL because we don't need an end pointer*/
	return strtol(lexeme, NULL, 8);
}

/*
 * Purpose: Determines whether a string is in the keyword table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	kw_lexeme - The string to be checked
 * Return value: If the lexeme is a keyword, this returns the position in the array
 						of the keyword, otherwise -1 for error
 */
int iskeyword(char * kw_lexeme){
	int i;
	
	/* Check the keyword table to see if it contains lexeme */
	for (i = 0; i < KWT_SIZE; i++){
		if (!strcmp(kw_lexeme, kw_table[i])){
			return i;
		}
	}

	return -1;
}

/*
 * Purpose: An easy way of creating an error token from a subset of a long string
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	msg_len - the number of characters to copy into the error token
 				err_msg - the string that contains the error message. Must be longer
               	than the msg_len.
 * Return value: An error token with the specified message
 */
Token createErrorToken(unsigned int msg_len, const char *err_msg){
	Token t;
	unsigned int i;

	/* Make sure we don't send in a stupid msg_len*/
	assert(strlen(err_msg) >= msg_len);

	t.code = ERR_T;
	for (i = 0 ; i < msg_len && i < ERR_LEN; i++){
   		t.attribute.err_lex[i] = err_msg[i];
	}
	t.attribute.err_lex[i] = '\0';

	return t;
}

/*
 * Purpose: To ease the creation of tokens with integer attributes
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	code - The code to represent the type of token
 					attribute - An integer attribute for the code
 * Return value: A token with your specified values
 */
Token createIntValToken(int code, int attribute){
	Token t;

	t.code = code;
	t.attribute.int_value = attribute;

	return t;
}

/*
 * Purpose: To ease the creation of tokens with rel_op attributes
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters: attribute - A rel_op attribute for the token
 * Return value: A token with your specified values
 */
Token createRelOpToken(Rel_Op attribute){
	Token t;

	t.code = REL_OP_T;
	t.attribute.rel_op = attribute;

	return t;
}

/*
 * Purpose: To ease the creation of empty tokens
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	code - The code to represent the type of token
 * Return value: A token with your specified values
 */
Token createEmptyToken(int code){
	Token t;
	t.code = code;
	return t;
}

/*
 * Purpose: To ease the creation of arr_op tokens
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	attribute - An arr_op attribute for the token
 * Return value: A token with your specified values
 */
Token createArrOpToken(Arr_Op attribute){
 	Token t;

	t.code = ART_OP_T;
	t.attribute.arr_op = attribute;

   return t;
}

/*
 * Purpose: To ease the creation of log_op tokens
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	attribute - A log_op attribute for the token
 * Return value: A token with your specified values
 */
Token createLogOpToken(Log_Op attribute){
 	Token t;

	t.code = LOG_OP_T;
	t.attribute.log_op = attribute;

	return t;
}


/*
 * Purpose: To ease the creation of tokens with float attributes
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters: attribute - A float attribute for the token
 * Return value: A token with your specified values
 */
Token createFltValToken(float attribute){
 	Token t;

	t.code = FPL_T;
	t.attribute.flt_value = attribute;

   return t;
}

/*
 * Purpose: Tests a symbol to see if it is end of file. 
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	c - the symbol to be tested. EOF will be either 0 or 255
 * Return value: true (1) if the symbol is EOF, false(0) otherwise
 */
static int isEOF(unsigned char c){
	if (c == 0 || c == 255){
    	return 1;
	}
	return 0;
}

/*
 * Purpose: Installs a VID into the symbol table, handling failure 
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	lexeme - the lexeme to be installed into the symbol table
 */
static int install_vid(char *lexeme) {
	int offset;	

	offset = st_install(sym_table, lexeme, line);

	if (offset == FAIL){
		printf("\nError: The Symbol Table is full - install failed.\n");
		st_store(sym_table);
		exit(1);
	}

	return offset;
}


