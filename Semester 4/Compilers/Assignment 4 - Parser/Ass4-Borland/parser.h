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

/*GLOBAL VARIABLE DEFINITIONS*/
static Token lookahead_token;	/*The next token to be parsed*/
static Buffer *sc_buf;			/*buffer that holds the source*/
extern STD sym_table;			/*symbol table*/
extern Buffer *str_LTBL;		/*Holds string literals found in the source*/
extern int line;				/*Line numbers*/
extern char *kw_table[];		/*The keyword table declared in table.h*/
int synerrno;					/*Number of errors found*/

/*FUNCTION PROTOTYPES*/
void parser(Buffer *);
void match(int, int);
void syn_eh(int);
void syn_printe(void);
void gen_incode(const char *);
Token malpar_next_token(Buffer *);

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
void arithmetic_expression(void);
void unary_arithmetic_expression(void);
void additive_arithmetic_expression(void);
void additive_arithmetic_expression1(void);
void multiplicative_arithmetic_expression(void);
void multiplicative_arithmetic_expression1(void);
void primary_arithmetic_expression(void);
void string_expression(void);
void string_expression1(void);
void primary_string_expression(void);
void conditional_expression(void);
void logical_or_expression(void);
void logical_or_expression1(void);
void logical_and_expression(void);
void logical_and_expression1(void);
void relational_expression(void);
void primary_a_relational_expression(void);
void primary_a_relational_expression1(void);
void primary_s_relational_expression(void);
void primary_s_relational_expression1(void);


#endif