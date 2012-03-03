/* File Name: parser.h
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 4
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: Declarations and prototypes for the parser
 */
#ifndef PARSER_H
#define PARSER_H

/*CONSTANT DEFINITIONS*/
#define NO_ATTR -1
#define ELSE 0
#define IF 1
#define INPUT 2
#define OUTPUT 3
#define PLATYPUS 4
#define REPEAT 5
#define THEN 6
#define USING 7

#define STACK_SIZE 100

/*GLOBAL VARIABLE DEFINITIONS*/
static Token lookahead_token;	/*The next token to be parsed*/
static Buffer *sc_buf;			/*buffer that holds the source*/
extern STD sym_table;			/*symbol table*/
extern Buffer *str_LTBL;		/*Holds string literals found in the source*/
extern int line;				/*Line numbers*/
extern char *kw_table[];		/*The keyword table declared in table.h*/
static Stack *gp_stack;			/*A reusable general purpose stack*/
static Stack *repeat_stack;		/*stack used for the USING REPEAT statement*/
extern int forward;
int synerrno;					/*Number of errors found*/

/*FUNCTION PROTOTYPES*/
void parser(Buffer *);
void match(int, int);
void syn_eh(int);
void syn_printe(void);
void gen_incode(const char *);
Token malpar_next_token(Buffer *);
void advance_tokens(int, int);

void assign(Token, Token);
void output(Stack *);
Token perform_arithmetic(Stack *);
Token concat(Stack *);
void input(Stack *);
int a_relate(Stack *);
int s_relate(Stack *);
int relate(Stack *);


/*GRAMMAR FUNCTIONS*/
void program(void);
void opt_statements(void);
void statements(void);
void statements1(void);
void statement(void);
void assignment_statement(void);
void assignment_expression(void);
void selection_statement(void);
void iteration_statement(void);
void input_statement(void);
void variable_list(void);
void variable_list1(void);
void variable_identifier(void);
void output_statement(void);
void output_statement1(void);
void opt_variable_list(void);
void arithmetic_expression(Stack *);
void unary_arithmetic_expression(Stack *);
void additive_arithmetic_expression(Stack *);
void additive_arithmetic_expression1(Stack *);
void multiplicative_arithmetic_expression(Stack *);
void multiplicative_arithmetic_expression1(Stack *);
void primary_arithmetic_expression(Stack *);
void string_expression(Stack *);
void string_expression1(Stack *);
void primary_string_expression(Stack *);
void conditional_expression(Stack *);
void logical_or_expression(Stack *);
void logical_or_expression1(Stack *);
void logical_and_expression(Stack *);
void logical_and_expression1(Stack *);
void relational_expression(Stack *);
void primary_a_relational_expression(Stack *);
void primary_a_relational_expression1(Stack *);
void primary_s_relational_expression(Stack *);
void primary_s_relational_expression1(Stack *);


#endif