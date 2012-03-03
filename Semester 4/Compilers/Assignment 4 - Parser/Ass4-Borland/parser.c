/* File Name: parser.c
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 4
 * Date: August 12, 2011
 * Professor: Svillen Ranev
 * Purpose: Parses a token represented source file
 */
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "token.h"
#include "stable.h"
#include "parser.h"

/*
 * Purpose: scans and parses the source file contained in a buffer
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	in_buf - The buffer containing the source file
*/
void parser(Buffer *in_buf){
	sc_buf = in_buf; 
	lookahead_token = malpar_next_token(sc_buf);
	program();
	match(SEOF_T,NO_ATTR);
	gen_incode("PLATY: Source file parsed");
}

/*
 * Purpose: Matches the lookahead token with the expected token
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	pr_token_code - The expected token
				pr_token_attribute - the expected attribute of the token
*/
void match(int pr_token_code,int pr_token_attribute) {
	
	int code = lookahead_token.code;		/*makes a shorter if statement*/

	/*We know for sure that there is an error*/
	if (code != pr_token_code) {
		syn_eh(pr_token_code);
		return;
	}

	/*Test further for attribute equality.*/
	if (code == KW_T && pr_token_attribute != lookahead_token.attribute.int_value 
		|| code == REL_OP_T && pr_token_attribute != lookahead_token.attribute.rel_op
		|| code == LOG_OP_T && pr_token_attribute != lookahead_token.attribute.log_op
		|| code == ART_OP_T && pr_token_attribute != lookahead_token.attribute.arr_op )
	{
		syn_eh(pr_token_code);
		return;
	}

	/*Handle End of File before the scanner generates an error*/
	if (code == SEOF_T){
		return;
	}

	lookahead_token = malpar_next_token(sc_buf);

	/*handle errors caught in the scanner*/
	if (lookahead_token.code == ERR_T){
		syn_printe();
		lookahead_token = malpar_next_token(sc_buf);
		synerrno++;
		return;
	}
}

/*
 * Purpose: Handles a panic mode error recovery
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sync_token_code - The code of our safety net token
*/
void syn_eh(int sync_token_code){

	/*Print the error and increment the error count*/
	syn_printe();
	synerrno++;

	/*If we are looking for end of file, let's just leave early*/
	if (sync_token_code == SEOF_T){
		return;
	}

	/*sync up the parser by finding the next occurence of sync token*/
	while (lookahead_token.code != sync_token_code) {

		lookahead_token = malpar_next_token(sc_buf);
		if (lookahead_token.code == SEOF_T){
			exit(synerrno);
		}
	}

	/*let's advance once more now that we know we are safe*/
	lookahead_token = malpar_next_token(sc_buf);
}

/*
 * Purpose: Generates intermediate code. (This implementation only prints)
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	code - A string of code that is added to the generated code
*/
void gen_incode(const char *code){

	printf("%s\n", code);

}



/*
 * Purpose: Prints out an error found by the parser
 * Author: Svillen Ranev
 * History/Versions: Unknown
*/
void syn_printe() {
	Token t = lookahead_token;

	printf("PLATY: Syntax error:  Line:%3d\n",line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch(t.code){
		case  ERR_T: /* ERR_T     0   Error token */
			printf("%s\n",t.attribute.err_lex);
		 break;
		case  SEOF_T: /*SEOF_T    1   Source end-of-file token */
			printf("NA\n" );
		 break;
		case  AVID_T: /* AVID_T    2   Arithmetic Variable identifier token */
		case  SVID_T :/* SVID_T    3  String Variable identifier token */
			printf("%s\n",sym_table.pstvr[t.attribute.get_int].plex);
		 break;
		case  FPL_T: /* FPL_T     4  Floating point literal token */
			printf("%5.1f\n",t.attribute.flt_value);
		 break;
		case INL_T: /* INL_T      5   Integer literal token */
		        printf("%d\n",t.attribute.get_int);
		 break;
		case STR_T:/* STR_T     6   String literal token */
		        printf("%s\n",(str_LTBL->ca_head + t.attribute.get_int));
		break;
	     
	     case SCC_OP_T: /* 7   String concatenation operator token */
		        printf("NA\n" );
		break;
		
		case  ASS_OP_T:/* ASS_OP_T  8   Assignment operator token */
			printf("NA\n" );
		break;
		case  ART_OP_T:/* ART_OP_T  9   Arithmetic operator token */
			printf("%d\n",t.attribute.get_int);
		break;
		case  REL_OP_T: /*REL_OP_T  10   Relational operator token */ 
			printf("%d\n",t.attribute.get_int);
		break;
		case  LOG_OP_T:/*LOG_OP_T 11  Logical operator token */
			printf("%d\n",t.attribute.get_int);
		break;
		
		case  LPR_T: /*LPR_T    12  Left parenthesis token */
			printf("NA\n" );
		break;
		case  RPR_T: /*RPR_T    13  Right parenthesis token */
		        printf("NA\n" );
		break;
		case LBR_T: /*    14   Left brace token */
		        printf("NA\n" );
		break;
		case RBR_T: /*    15  Right brace token */
		        printf("NA\n" );
		break;
			
		case KW_T: /*     16   Keyword token */
		        printf("%s\n",kw_table [t.attribute.get_int]);
		break;
		
		case COM_T: /* 17   Comma token */
		        printf("NA\n");
		break;
		case EOS_T: /*    18  End of statement *(semi - colon) */
		        printf("NA\n" );
		break; 		
		default:
		        printf("PLATY: Scanner error: invalid token code: %d\n", t.code);
	}
}


/************************************************************************************
	A FUNCTION FOR EVERY DEFINED PRODUCTION IN THE GRAMMAR
************************************************************************************/

/*
 * PRODUCTION: <program> -> PLATYPUS {<opt_statements>} 
 *FIRSTS: PLATYPUS
*/
void program() {
	match(KW_T,PLATYPUS);
	match(LBR_T,NO_ATTR);
	opt_statements();
	match(RBR_T,NO_ATTR); 
	gen_incode("PLATY: Program parsed");
}

/*
 * PRODUCTION: <opt_statements> -> <statements> | empty 
 * FIRSTS: AVID_T, SVID_T, IF, USING, INPUT, OUTPUT, empty
*/
void opt_statements(){
	int c = lookahead_token.code;
	int a = lookahead_token.attribute.int_value;

	/*The FIRSTS for opt_statements*/
	if (c == AVID_T || c == SVID_T || c == KW_T && (a == IF || a == USING || a == INPUT || a == OUTPUT)){
		statements();
	}
	/*empty*/
	else {
		gen_incode("PLATY: Opt_statements parsed");	
	}
}

/*
 * PRODUCTION: <statements> -> <statement><statements'> 
 * FIRSTS: AVID_T, SVID_T, IF, USING, INPUT, OUTPUT
*/
void statements(void){
	statement();
	statements1();
}

/*
 * PRODUCTION: <statements1> -> <statement><statements1> | empty
 * FIRSTS: AVID_T, SVID_T, IF, USING, INPUT, OUTPUT
*/
void statements1(void){
	int c = lookahead_token.code;
	int a = lookahead_token.attribute.int_value;

	if (c == AVID_T || c == SVID_T || c == KW_T && (a == IF || a == USING || a == INPUT || a == OUTPUT)){
		statement();
		statements1();
	}
	
	/*empty*/
	
}

/*
 * PRODUCTION: <statement> -> <assignment statement> | <selection statement> |
							<iteration statement> | <input statement> | <output statement>
 * FIRSTS: AVID_T, SVID_T, IF, USING, INPUT, OUTPUT
*/
void statement(void){

	/*Assignment statement*/
	if (lookahead_token.code == AVID_T || lookahead_token.code == SVID_T){
		assignment_statement();
	}

	/*selection statement*/
	else if (lookahead_token.attribute.get_int == IF) {
		selection_statement();
	}

	/*iteration statement*/
	else if (lookahead_token.attribute.get_int == USING){
		iteration_statement();
	}

	/*input statement*/
	else if (lookahead_token.attribute.get_int == INPUT){
		input_statement();
	}

	/*output statement*/
	else if (lookahead_token.attribute.get_int == OUTPUT){
		output_statement();
	}
	/*Error*/
	else {
		syn_printe();
		return;
	}

}


/*
 * PRODUCTION: <assignment statement> -> <assignment expression>
 * FIRSTS: AVID_T, SVID_T
*/
void assignment_statement(){
	assignment_expression();
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: Assignment statement parsed");
}

/*
 * PRODUCTION: <assignment expression> -> AVID = <arithmetic expression>  
										| SVID = <arithmetic expression>
 * FIRSTS: AVID_T, SVID_T
*/
void assignment_expression(){

	/*AVID*/
	if (lookahead_token.code == AVID_T) {
		match(AVID_T, NO_ATTR);
		match(ASS_OP_T, NO_ATTR);
		arithmetic_expression();
		gen_incode("PLATY: Assignment expression (arithmetic) parsed");
	}

	/*SVID*/
	else if (lookahead_token.code == SVID_T){
		match(SVID_T, NO_ATTR);
		match(ASS_OP_T, NO_ATTR);
		string_expression();
		gen_incode("PLATY: Assignment expression (string) parsed");
	}
	/*Error*/
	else {
		syn_printe();
	}
}

/*
 * PRODUCTION: <selection statement> -> IF (<conditional expression>) THEN <opt_statements> 
										ELSE {<opt_statements>};
 * FIRSTS: IF
*/
void selection_statement(){
	match(KW_T, IF);
	match(LPR_T, NO_ATTR);
	conditional_expression();
	match(RPR_T, NO_ATTR);
	match(KW_T, THEN);
	opt_statements();
	match(KW_T, ELSE);
	match(LBR_T, NO_ATTR);
	opt_statements();
	match(RBR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: IF statement parsed");
}

/*
 * PRODUCTION: <iteration statement> -> USING (<assignment expression>,<conditional expression>,<assignment expression>)
										REPEAT { <opt_statements> };
 * FIRSTS: USING
*/
void iteration_statement(){
	match(KW_T, USING);
	match(LPR_T, NO_ATTR);
	assignment_expression();
	match(COM_T, NO_ATTR);
	conditional_expression();
	match(COM_T, NO_ATTR);
	assignment_expression();
	match(RPR_T, NO_ATTR);
	match(KW_T, REPEAT);
	match(LBR_T, NO_ATTR);
	opt_statements();
	match(RBR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: USING statement parsed");
}

/*
 * PRODUCTION: <input statement> -> INPUT(<variable list>);
 * FIRSTS: INPUT
*/
void input_statement(){
	match(KW_T, INPUT);
	match(LPR_T, NO_ATTR);
	variable_list();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: INPUT statement parsed");
}

/*
 * PRODUCTION: <variable list> -> <variable identifier><variable list1> 
 * FIRSTS: AVID_T, SVID_T
*/
void variable_list(){
	variable_identifier();
	variable_list1();
	gen_incode("PLATY: Variable list parsed");
}

/*
 * PRODUCTION: <variable list1> -> ,<variable identifier><variable list1> | empty 
 * FIRSTS: ,, empty
*/
void variable_list1(){

	/*empty*/
	if (lookahead_token.code != COM_T) {
		return;
	}

	match(COM_T, NO_ATTR);
	variable_identifier();
	variable_list1();
}

/*
 * PRODUCTION: <variable identifier> -> AVID_T | SVID_T
 * FIRSTS: AVID_T, SVID_T
*/
void variable_identifier(){

	if (lookahead_token.code == AVID_T){
		match(AVID_T, NO_ATTR);
	}
	else if (lookahead_token.code == SVID_T){
		match(SVID_T, NO_ATTR);
	}
	else {
		syn_printe();
	}
	
}

/*
 * PRODUCTION: <output statement> -> OUTPUT(<output statement1>);
 * FIRSTS: OUTPUT
*/
void output_statement(){
	match(KW_T, OUTPUT);
	match(LPR_T, NO_ATTR);
	output_statement1();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	gen_incode("PLATY: OUTPUT statement parsed");
}

/*
 * PRODUCTION: <output statement1> -> <opt_variable list> | STR_T
 * FIRSTS: AVID_T, SVID_T, STR_T, empty
*/
void output_statement1(){

	/*String literal*/
	if (lookahead_token.code == STR_T){
		match(STR_T, NO_ATTR);
		gen_incode("PLATY: Output list (string literal) parsed");
	}
	/*Optional Variable list*/
	else {
		opt_variable_list();
	}
}

/*
 * PRODUCTION: <opt_variable list> -> <variable list> | empty
 * FIRSTS: AVID_T, SVID_T, empty
*/
void opt_variable_list(){

	/*variable list*/
	if (lookahead_token.code == AVID_T || lookahead_token.code == SVID_T){
		variable_list();
	}
	/*empty*/
	else {
		gen_incode("PLATY: Output list (empty) parsed");
	}
}

/*
 * PRODUCTION: <arithmetic expression> -> <unary arithmetic expression>
										| <additive arithmetic expression>
 * FIRSTS: +, -, AVID_T, FPL_T, INL_T, LPR_T
*/
void arithmetic_expression(){
	int code = lookahead_token.code;
	Arr_Op attrib = lookahead_token.attribute.arr_op;

	/*unary arithmetic expression*/
	if (lookahead_token.code == ART_OP_T && (attrib == PLUS || attrib == MINUS)){
		unary_arithmetic_expression();
	}
	/*additive arithmetic expression*/
	else if (code == AVID_T || code == FPL_T || code == INL_T || code == LPR_T){
		additive_arithmetic_expression();
	}
	/*Otherwise we have an error*/
	else {
		syn_printe();
		return;
	}
}

/*
 * PRODUCTION: <unary arithmetic expression> -> - <primary arithmetic expression> 
												| + <primary arithmetic expression>
 * FIRSTS: +, -
*/
void unary_arithmetic_expression(){

	if (lookahead_token.attribute.arr_op == MINUS){
		match(ART_OP_T, MINUS);
	}
	else if (lookahead_token.attribute.arr_op == PLUS){
		match(ART_OP_T, PLUS);
	}
	primary_arithmetic_expression();
	gen_incode("PLATY: Unary arithmetic expression parsed");
	gen_incode("PLATY: Arithmetic expression parsed");
}

/*
 * PRODUCTION: <additive arithmetic expression> -> <multiplicative arithmetic expression><additive arithmetic expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T, LPR_T
*/
void additive_arithmetic_expression(){
	multiplicative_arithmetic_expression();
	additive_arithmetic_expression1();
	gen_incode("PLATY: Arithmetic expression parsed");
}


/*
 * PRODUCTION: <additive arithmetic expression1> ->   
					  + <multiplicative arithmetic expression><additive arithmetic expression1>
					| - <multiplicative arithmetic expression><additive arithmetic expression1>
					| empty
 * FIRSTS: +, -, empty
*/
void additive_arithmetic_expression1(){

	/*Match the two possible cases*/
	if (lookahead_token.code == ART_OP_T){
		if (lookahead_token.attribute.arr_op == MINUS){
			match(ART_OP_T, MINUS);
		}
		else if (lookahead_token.attribute.arr_op == PLUS){
			match(ART_OP_T, PLUS);
		}
		else {
			return;
		}

		/*Now do the rest*/
		multiplicative_arithmetic_expression();
		additive_arithmetic_expression1();
		gen_incode("PLATY: Additive arithmetic expression parsed");
	}

	/*empty*/

}

/*
 * PRODUCTION: <multiplicative arithmetic expression> -> 
					<primary arithmetic expression><multiplicative arithmetic expression1>	
 * FIRSTS: AVID_T, FPL_T, INL_T, LPR_T
*/
void multiplicative_arithmetic_expression(){
	primary_arithmetic_expression();
	multiplicative_arithmetic_expression1();
}

/*
 * PRODUCTION: <multiplicative arithmetic expression1> ->   
					  * <primary arithmetic expression><multiplicative arithmetic expression1>
					| / <primary arithmetic expression><multiplicative arithmetic expression1>
					| empty
 * FIRSTS: *, /
*/
void multiplicative_arithmetic_expression1(){

	/*Match one of the two possible cases*/
	if (lookahead_token.code == ART_OP_T){
		if (lookahead_token.attribute.arr_op == MULT){
			match(ART_OP_T, MULT);
		}
		else if (lookahead_token.attribute.arr_op == DIV){
			match(ART_OP_T, DIV);
		}
		else {
			return;
		}

		/*Now do the rest*/
		primary_arithmetic_expression();
		multiplicative_arithmetic_expression1();
		gen_incode("PLATY: Multiplicative arithmetic expression parsed");
	}

	/*empty*/
}

/*
 * PRODUCTION: <primary arithmetic expression> -> 
					AVID_T | FPL_T | INL_T | (<arithmetic expression>)	
 * FIRSTS: AVID_T, FPL_T, INL_T, LPR_T
*/
void primary_arithmetic_expression(){

	if (lookahead_token.code == AVID_T){
		match(AVID_T, NO_ATTR);
	}
	else if (lookahead_token.code == FPL_T){
		match(FPL_T, NO_ATTR);
	}
	else if (lookahead_token.code == INL_T){
		match(INL_T, NO_ATTR);
	}
	else if (lookahead_token.code == LPR_T){
		match(LPR_T, NO_ATTR);
		arithmetic_expression();
		match(RPR_T, NO_ATTR);
	}
	else {
		syn_printe();
		return;
	}
	gen_incode("PLATY: Primary arithmetic expression parsed");
}

/*
 * PRODUCTION: <string expression> ->
					<primary string expression><string expression1>
 * FIRSTS: SVID_T, STR_T
*/
void string_expression(){
	primary_string_expression();
	string_expression1();
	gen_incode("PLATY: String expression parsed");
}

/*
 * PRODUCTION: <string expression1> -> 
					<< <primary string expression><string expression1> | empty
 * FIRSTS: SCC_OP_T
*/
void string_expression1(){

	/*String concatenation*/
	if (lookahead_token.code == SCC_OP_T){
		match(SCC_OP_T, NO_ATTR);
		primary_string_expression();
		string_expression1();
	}

	/*do nothing for empty*/
}

/*
 * PRODUCTION: <primary string expression> -> SVID_T | STR_T	
 * FIRSTS: SVID_T, STR_T
*/
void primary_string_expression(){

	/*SVID*/
	if (lookahead_token.code == SVID_T){
		match(SVID_T, NO_ATTR);
	}
	/*STRING LITERAL*/
	else if (lookahead_token.code == STR_T){
		match(STR_T, NO_ATTR);
	}
	/*NO MATCH*/
	else {
		syn_printe();
		return;
	}
	gen_incode("PLATY: Primary string expression parsed");
}

/*
 * PRODUCTION: <conditional expression> -> <logical OR expression>
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void conditional_expression(){
	logical_or_expression();
	gen_incode("PLATY: Conditional expression parsed");
}

/*
 * PRODUCTION: <logical or expression> -> <logical AND expression> <logical OR expression1>	
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void logical_or_expression(){
	logical_and_expression();
	logical_or_expression1();
}

/*
 * PRODUCTION: <logical or expression1> -> 
					.OR. <logical AND expression> <logical OR expression1> | empty		
 * FIRSTS: .OR., empty
*/
void logical_or_expression1(){

	/*OR*/
	if (lookahead_token.code == LOG_OP_T){
		if (lookahead_token.attribute.log_op == OR) {
			match(LOG_OP_T, OR);
		}
		else if (lookahead_token.attribute.log_op == AND){
			
		}
		else {
			return;
		}

		/*Do common things*/
		logical_and_expression();
		logical_or_expression1();
		gen_incode("PLATY: Logical OR expression parsed");
	}

	/*Do nothing for empty*/
}

/*
 * PRODUCTION: <logical AND expression> -> <relational expression> <logical AND expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T
*/
void logical_and_expression(){
	relational_expression();
	logical_and_expression1();
}

/*
 * PRODUCTION: <logical AND expression1> -> 
					.AND. <relational expression> <logical OR expression1> |empty
 * FIRSTS: .AND., empty
*/
void logical_and_expression1(){
	
	/*AND*/
	if (lookahead_token.code == LOG_OP_T && lookahead_token.attribute.log_op == AND){
		match(LOG_OP_T, AND);
		relational_expression();
		logical_and_expression1();
		gen_incode("PLATY: Logical AND expression parsed");
	}

	/*empty*/
}

/*
 * PRODUCTION: <relational expression> -> 
					<primary a_relational expression><primary a_relational expression1>
					| <primary s_relational expression><primary s_relational expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T
*/
void relational_expression(){
	int code = lookahead_token.code;

	/* A_RELATIONAL*/
	if (code == AVID_T || code == FPL_T || code == INL_T){
		primary_a_relational_expression();
		primary_a_relational_expression1();
	}
	/* S_RELATIONAL*/
	else if (code == SVID_T || code == STR_T){
		primary_s_relational_expression();
		primary_s_relational_expression1();
	}
	/*INVALID*/
	else {
		syn_printe();
	}
	gen_incode("PLATY: Relational expression parsed");
}

/*
 * PRODUCTION: <primary a_relational expression> -> AVID_T | FPL_T | INL_T
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void primary_a_relational_expression(){
	
	/*AVID*/
	if (lookahead_token.code == AVID_T){
		match(AVID_T, NO_ATTR);
	}
	/*FLOATING POINT LITERAL*/
	else if (lookahead_token.code == FPL_T){
		match(FPL_T, NO_ATTR);
	}
	/*INTEGER LITERAL*/
	else if (lookahead_token.code == INL_T){
		match(INL_T, NO_ATTR);
	}
	/*Nothing else allowed*/
	else {
		syn_printe();
	}
	gen_incode("PLATY: Primary a_relational expression parsed");
}

/*
 * PRODUCTION: <primary a_relational expression1> -> 
						== <primary a_relational expression>
						| != <primary a_relational expression>
						| > <primary a_relational expression>
						| < <primary a_relational expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_a_relational_expression1(){
	Rel_Op attrib = lookahead_token.attribute.rel_op;

	/*error*/
	if (lookahead_token.code != REL_OP_T){
		syn_printe();
		return;
	}

	/*IS EQUAL TO*/
	if (attrib == EQ){
		match(REL_OP_T, EQ);
	}
	/*NOT EQUAL*/
	if (attrib == NE){
		match(REL_OP_T, NE);
	}
	/*GREATER THAN*/
	if (attrib == GT){
		match(REL_OP_T, GT);
	}
	/*LESS THAN*/
	if (attrib == LT){
		match(REL_OP_T, LT);
	}
	primary_a_relational_expression();
}

/*
 * PRODUCTION: <primary s_relational expression> -> <primary string expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_s_relational_expression(){
	primary_string_expression();
	gen_incode("PLATY: Primary s_relational expression parsed");
}

/* 
 *PRODUCTION: <primary s_relational expression1> ->
						== <primary s_relational expression>
						| != <primary s_relational expression>
						| > <primary s_relational expression>
						| < <primary s_relational expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_s_relational_expression1(){
	Rel_Op attrib = lookahead_token.attribute.rel_op;

		/*error*/
	if (lookahead_token.code != REL_OP_T){
		syn_printe();
		return;
	}

	/*IS EQUAL TO*/
	if (attrib == EQ){
		match(REL_OP_T, EQ);
	}
	/*NOT EQUAL*/
	if (attrib == NE){
		match(REL_OP_T, NE);
	}
	/*GREATER THAN*/
	if (attrib == GT){
		match(REL_OP_T, GT);
	}
	/*LESS THAN*/
	if (attrib == LT){
		match(REL_OP_T, LT);
	}
	primary_s_relational_expression();
}