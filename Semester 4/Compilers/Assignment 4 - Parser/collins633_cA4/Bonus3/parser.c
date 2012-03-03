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
#include <string.h>
#include <ctype.h>
#include "stack.h"
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

	/*Handle End of File before the scanner generates an error*/
	if (code == SEOF_T){
		return;
	}

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

	/*push items onto the using repeat stack*/
	if (repeat_stack != NULL){
		push(repeat_stack, &lookahead_token);
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
 * Purpose: advances the lookahead token to the next occurrence of code and attribute
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters: code - The expected token
			attribute - the expected attribute of the token
*/
void advance_tokens(int code, int attribute){

	while (lookahead_token.code != SEOF_T){

		/*Leave if we find the token*/
		if ( lookahead_token.code == code && attribute == NO_ATTR
			|| lookahead_token.code == code && lookahead_token.attribute.get_int == attribute){
			break;
		}

		lookahead_token = malpar_next_token(sc_buf);

		/*Handle nested statements. Awful, I know, but it works for the most part*/
		if (code == RBR_T && lookahead_token.code == LBR_T){
			advance_tokens(RBR_T, NO_ATTR);
			lookahead_token = malpar_next_token(sc_buf);
		}
		else if (code == KW_T && attribute == ELSE && lookahead_token.code == KW_T && lookahead_token.attribute.int_value == IF){
			advance_tokens(KW_T, ELSE);
			lookahead_token = malpar_next_token(sc_buf);
		}
		

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
 * Purpose: Takes a stack from the assignment statement and analyzes the tokens
			Also performs the assignment.
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
*/
void assign(Token vid, Token value){
	InitialValue new_val;	/*The new value to assign*/

	/*Integer VID*/
	if (vid.code == AVID_T && st_get_type(sym_table, vid.attribute.vid_offset) == 'I'){	

		/*Assign int*/
		if (value.code == INL_T){
			new_val.int_val = value.attribute.int_value;
			st_update_value(sym_table, vid.attribute.vid_offset, new_val);
		}
		/*Assign float. Update if it can be updated*/
		else if (value.code == FPL_T){
			st_update_type(sym_table, vid.attribute.vid_offset, 'F');
			new_val.fpl_val = value.attribute.flt_value;
			st_update_value(sym_table, vid.attribute.vid_offset, new_val);
		}

		/*Perform_arithmetic() guarantees an int or a float*/
	}
	/*Float VID*/
	else if (vid.code == AVID_T && st_get_type(sym_table, vid.attribute.vid_offset) == 'F'){
		
		/*Cannot assign strings to float*/
		if (value.code == STR_T || value.code == SVID_T){
			syn_printe();
			return;
		}

		/*Assign int*/
		if  (value.code == INL_T){
			new_val.fpl_val = (float) value.attribute.int_value;
			st_update_value(sym_table, vid.attribute.vid_offset, new_val);
		}
		/*Assign float*/
		else if (value.code == FPL_T){
			new_val.fpl_val = value.attribute.flt_value;
			st_update_value(sym_table, vid.attribute.vid_offset, new_val);
		}

		/*Perform_arithmetic() guarantees an int or a float*/
	}
	/*String VID*/
	else if (vid.code == SVID_T){

		/*String Literal*/
		if (value.code == STR_T){
			new_val.str_offset = value.attribute.str_offset;
			st_update_value(sym_table, vid.attribute.vid_offset, new_val);
		}

		/*The concat() function guarantees a string literal will be sent, so no need to check svid*/

	}
}

/*
 * Purpose: Takes a stack of SVIDs or a String literal and outputs them
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
*/
void output(Stack *stack){
	Token token;
	s_reverse(stack);

	/*If we have an empty stack*/
	if (stack->next == 0){
		printf("\n");
	}

	/*Pop all values off of the stack printing them*/
	while (pop(stack, (char*)&token) != NULL){

		/*String constants*/
		if (token.code == STR_T){
			printf("%s", str_LTBL->ca_head + token.attribute.str_offset); 
			return;
		}

		/*String variables*/
		else if (token.code == SVID_T){
			printf("%s", str_LTBL->ca_head + st_get_value(sym_table, token.attribute.vid_offset).str_offset); 
		}
		/*Integer Variables*/
		else if (token.code == AVID_T && st_get_type(sym_table, token.attribute.vid_offset) == 'I'){
			printf("%d", st_get_value(sym_table, token.attribute.vid_offset).int_val);
		}
		/*Floating point Variables*/
		else if (token.code == AVID_T && st_get_type(sym_table, token.attribute.vid_offset) == 'F'){
			printf("%.2f", st_get_value(sym_table, token.attribute.vid_offset).fpl_val);
		}
	}

}

/*
 * Purpose: Takes a stack of tokens from an aritmetic expression and calculates the value
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
 * Returns: The floating point value of the expression
*/
Token perform_arithmetic(Stack *stack){
	int i = 0;
	int array_len;
	Token token;
	Token cmp_token;
	
	Stack *o_stack = s_create(sizeof(Token), STACK_SIZE);	/*Stack used for postfix conversion*/
	Stack *e_stack = s_create(sizeof(float), STACK_SIZE);	/*Stack used for postfix evaluation*/
	char int_flag = 1;	/*set when the result should be of type int*/

	float temp1;	/*temp variable for evaluating*/
	float temp2;	/*temp variable for evaluating*/
	Token result;	/*the result will hold the result of the evaulation*/

	Token *postfix = (Token*)malloc(stack->data_size * stack->next);  /*Array of tokens in postfix form*/

	/*reverse the main arithmetic stack so that we get the first in the expression on top*/
	s_reverse(stack);

	/*Do Infix to Postfix conversion*/
	while (pop(stack, (char*)&token) != NULL){

		/*Handle Parenthesis*/
		if (token.code == LPR_T){
			Stack *temp_stack = s_create(sizeof(Token), STACK_SIZE);		/*The stack to calculate inside the parenthesis*/

			/*Get the tokens in between the parenthesis, and push them to the new stack*/
			while(pop(stack, (char*)&token) != NULL && token.code != RPR_T){
				push(temp_stack, &token);
			}

			/*do our calculation with the new stack, and assign the current token to be a float*/
			token = perform_arithmetic(temp_stack);

			if (token.code == FPL_T){
				int_flag = 0;
			}
			
			s_destroy(temp_stack);
		}

		/*Handle operands*/
		if (token.code == AVID_T || token.code == INL_T || token.code == FPL_T){
			postfix[i++] = token;

			if (token.code == AVID_T && st_get_type(sym_table, token.attribute.vid_offset) == 'F'
				|| token.code == FPL_T)
			{
				int_flag = 0;
			}

		}

		/*Handle the operators*/
		else if (token.code == ART_OP_T){

			/*If the operator stack is empty, then the operator is pushed*/
			if (o_stack->next == 0){
				push(o_stack, &token);
			}
			/*Loop until the top of the stack does not have precedence or it is empty*/
			else {
				while (stack->next != 0){
					cmp_token = *(Token*)peak(o_stack);

					/*mult and div always have precedence*/
					if (cmp_token.attribute.arr_op == MULT || cmp_token.attribute.arr_op == DIV){
						pop(o_stack, (char*)&postfix[i++]);
					}
					/*plus and minus only come out of the stack if the current token is plus or minus*/
					else if (cmp_token.attribute.arr_op == PLUS || cmp_token.attribute.arr_op == MINUS){
						if (token.attribute.arr_op == PLUS || token.attribute.arr_op == MINUS){
							pop(o_stack, (char*)&postfix[i++]);
						}
						/*The currently scanned token has higher precedence so push it to the stack*/
						else {
							push(o_stack, &token);
							break;
						}
					}
					/*currently scanned character has higher precedence*/
					else {
						push(o_stack, &token);
						break;
					}

				}

			}
			
		}

	}
	/*Now add what's left on the stack to the array of tokens*/
	while (pop(o_stack, (char*)&token) != NULL){
		postfix[i++] = token;
	}
	array_len = i;


	/*Perform postfix Evaluation*/
	for (i = 0; i < array_len; i++){

		/*Push operands to the stack*/
		if (postfix[i].code == AVID_T || postfix[i].code == INL_T || postfix[i].code == FPL_T){
			
			if (postfix[i].code == AVID_T && st_get_type(sym_table, postfix[i].attribute.vid_offset) == 'F'){
				push(e_stack, &(sym_table.pstvr[postfix[i].attribute.vid_offset].i_value.fpl_val));
			}
			else if (postfix[i].code == AVID_T && st_get_type(sym_table, postfix[i].attribute.vid_offset) == 'I'){
				float temp = (float) sym_table.pstvr[postfix[i].attribute.vid_offset].i_value.int_val;
				push(e_stack, &temp);
			}
			else if (postfix[i].code == INL_T){
				float temp = (float) postfix[i].attribute.int_value;
				push(e_stack, &temp);
			}
			else if (postfix[i].code == FPL_T){
				push(e_stack, &postfix[i].attribute.flt_value);
			}
		}
		/*For operators, we need to pop the next two operands and evaluate them*/
		else if (postfix[i].code == ART_OP_T){
			pop(e_stack, (char*)&temp1);
			pop(e_stack, (char*)&temp2);

			if (postfix[i].attribute.arr_op == PLUS){
				temp2 += temp1;
			}
			if (postfix[i].attribute.arr_op == MINUS){
				temp2 -= temp1;
			}
			if (postfix[i].attribute.arr_op == MULT){
				temp2 *= temp1;
			}
			if (postfix[i].attribute.arr_op == DIV){
				temp2 /= temp1;
			}	
			push(e_stack, &temp2);

		}
	}
	/*The remaining value in the stack will be the result*/
	pop(e_stack, (char*)&(result.attribute.flt_value));

	free(postfix);
	s_destroy(o_stack);
	s_destroy(e_stack);

	/*Distinguish between float and int VIDs*/
	if (int_flag){
		result.code = INL_T;
		result.attribute.int_value = (int)result.attribute.flt_value;
	}
	else {
		result.code = FPL_T;
	}

	return result;
}

/*
 * Purpose: Takes a stack of tokens from a string expression and concatenates them
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
 * Returns: A token representing a string literal containing the new string
*/
Token concat(Stack *stack){
	int i, offset, len;
	Token token;
	Token result;
	s_reverse(stack);	/*Make sure the stack is in the right order*/

	/*set the offset of the new string and it's type*/
	result.code = STR_T;
	result.attribute.str_offset = str_LTBL->addc_offset;

	/*Keep popping and concatenating until the stack is empty*/
	while (pop(stack, (char*)&token) != NULL){

		/*String Variable*/
		if (token.code == SVID_T){

			offset = sym_table.pstvr[token.attribute.vid_offset].i_value.str_offset;
			len = strlen(str_LTBL->ca_head + offset);
			
			/*Copy the string and add it to the string literal table*/
			for (i = 0; i < len; i++){
				ca_addc(str_LTBL, str_LTBL->ca_head[offset+i]);
			}

		}

		/*String Literal*/
		if (token.code == STR_T){
			offset = token.attribute.str_offset;
			len = strlen(str_LTBL->ca_head + offset);

			/*Copy the contents and add it to the str literal table*/
			for (i = 0; i < len; i++){
				ca_addc(str_LTBL, str_LTBL->ca_head[offset+i]);
			}

		}

	}
	ca_addc(str_LTBL, '\0');

	return result;
}

/*
 * Purpose: Takes a stack of VIDs and assigns user input into them
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
*/
void input(Stack *stack){
	char type, number[FLT_LEN];				/*The type of vid*/
	int c;
	InitialValue new_val;	/*the new value for the vid*/
	Token token;

	s_reverse(stack);
	/*get user input until there are no token left*/
	while (pop(stack, (char*)&token)){
		type = st_get_type(sym_table, token.attribute.vid_offset);

		/*String VIDs*/
		if (token.code == SVID_T){

			/*Update the location of the string in the symbol table*/
			new_val.str_offset = str_LTBL->addc_offset;
			st_update_value(sym_table, token.attribute.vid_offset, new_val);
			
			while ( (c = fgetc(stdin)) != '\n' && c != ' '){
				ca_addc(str_LTBL, (char)c);
			}
			ca_addc(str_LTBL, '\0');
		}
		/*Integer VIDs*/
		else if (token.code == AVID_T && type == 'I'){
			int i_num;
			int i = 0;;

			/*Keep getting input until done, or space, or no more room*/
			while ( (c = fgetc(stdin)) != '\n' && c != ' ' && i < INL_LEN){
				if (isdigit(c)){
					number[i] = (char)c;
					i++;
				}
			}
			number[i] = '\0';

			/*Now convert the string to a number*/
			i_num = (int)atol(number);

			new_val.int_val = i_num;
			st_update_value(sym_table, token.attribute.vid_offset, new_val);
		}
		/*Float VIDs*/
		else if (token.code == AVID_T && type == 'F'){
			float f_num;
			int i = 0;

			/*Keep getting input until done, or space, or no more room*/
			while ( (c = fgetc(stdin)) != '\n' && c != ' ' && i < FLT_LEN){
				if (isdigit(c) || c == '.'){
					number[i] = (char)c;
					i++;
				}
			}
			number[i] = '\0';

			/*Now convert the string to a number*/
			f_num = (float)atof(number);

			new_val.fpl_val = f_num;
			st_update_value(sym_table, token.attribute.vid_offset, new_val);
		}
	}
}

/*
 * Purpose: Takes a stack of arithmetic relational expression tokens and relates them
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
 * Returns: 0 on condition fail, other if it passes
*/
int a_relate(Stack *stack){
	int condition;

	Token l_token;
	Token r_token;
	Token op_token;
	s_reverse(stack);

	/*Convert to postfix*/
	pop(stack, (char*)&l_token);
	pop(stack, (char*)&op_token);
	pop(stack, (char*)&r_token);
	
	/*FIRST RELATIONAL OPERAND*/
	if (l_token.code == AVID_T && st_get_type(sym_table, l_token.attribute.vid_offset) == 'I'){
		l_token.attribute.flt_value = (float)sym_table.pstvr[l_token.attribute.vid_offset].i_value.int_val;
	}
	else if (l_token.code == AVID_T && st_get_type(sym_table, l_token.attribute.vid_offset) == 'F'){
		l_token.attribute.flt_value = sym_table.pstvr[l_token.attribute.vid_offset].i_value.fpl_val;
	}
	else if (l_token.code == INL_T){
		l_token.attribute.flt_value = (float)l_token.attribute.int_value;
	}
	/*FPL will already have a float value*/
	
	/*SECOND RELATIONAL OPERAND*/
	if (r_token.code == AVID_T && st_get_type(sym_table, r_token.attribute.vid_offset) == 'I'){
		r_token.attribute.flt_value = (float)sym_table.pstvr[r_token.attribute.vid_offset].i_value.int_val;
	}
	else if (r_token.code == AVID_T && st_get_type(sym_table, r_token.attribute.vid_offset) == 'F'){
		r_token.attribute.flt_value = sym_table.pstvr[r_token.attribute.vid_offset].i_value.fpl_val;
	}
	else if (r_token.code == INL_T){
		r_token.attribute.flt_value = (float)r_token.attribute.int_value;
	}


	/*Perform the relational operation*/
	if (op_token.attribute.rel_op == EQ){
		condition = (l_token.attribute.flt_value == r_token.attribute.flt_value);
	}
	else if (op_token.attribute.rel_op == NE){
		condition = (l_token.attribute.flt_value != r_token.attribute.flt_value);
	}
	else if (op_token.attribute.rel_op == GT){
		condition = (l_token.attribute.flt_value > r_token.attribute.flt_value);
	}
	else if (op_token.attribute.rel_op == LT){
		condition = (l_token.attribute.flt_value < r_token.attribute.flt_value);
	}	

	return condition;
}


/*
 * Purpose: Takes a stack of string relational expression tokens and relates them
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	stack - the stack containing the tokens in the expression
 * Returns: 0 on condition fail, other if it passes
*/
int s_relate(Stack *stack){
	int condition;
	char *left_string;
	char *right_string;

	Token l_token;
	Token r_token;
	Token op_token;
	s_reverse(stack);

	/*Convert to postfix*/
	pop(stack, (char*)&l_token);
	pop(stack, (char*)&op_token);
	pop(stack, (char*)&r_token);
	
	/*FIRST RELATIONAL OPERAND*/
	if (l_token.code == SVID_T){
		l_token.attribute.str_offset = sym_table.pstvr[l_token.attribute.vid_offset].i_value.str_offset;
	}
	
	/*SECOND RELATIONAL OPERAND*/
	if (r_token.code == SVID_T){
		r_token.attribute.str_offset = sym_table.pstvr[r_token.attribute.vid_offset].i_value.str_offset;
	}

	left_string = str_LTBL->ca_head + l_token.attribute.str_offset;
	right_string = str_LTBL->ca_head + r_token.attribute.str_offset;

	/*Perform the relational operation*/
	if (op_token.attribute.rel_op == EQ){
		condition = (!strcmp(left_string, right_string));
	}
	else if (op_token.attribute.rel_op == NE){
		condition = (strcmp(left_string, right_string));
	}
	else if (op_token.attribute.rel_op == GT){
		condition = (strcmp(left_string, right_string) > 0);
	}
	else if (op_token.attribute.rel_op == LT){
		condition = (strcmp(left_string, right_string) < 0);
	}	

	return condition;
}

int relate(Stack *stack){
	Token token;
	int condition = 0;
	s_reverse(stack);

	while (pop(stack, (char*)&token) != NULL){

		/*OR*/
		if (token.code == LOG_OP_T && token.attribute.log_op == OR){
			if (condition){
				break;
			}
			
		}
		/*AND*/
		else if (token.code == LOG_OP_T && token.attribute.log_op == AND){
			if (!condition) {
				pop(stack, NULL);
			}
			else {
				pop(stack, (char*)&token);
				if (token.attribute.int_value == 0) {
					condition = 0;
				}
			}
		}
		/*Conditional value disguised as an Integer Token*/
		else if (token.code == INL_T){
			condition = token.attribute.int_value;
		}
	}

	return condition;
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

}

/*
 * PRODUCTION: <assignment expression> -> AVID = <arithmetic expression>  
										| SVID = <arithmetic expression>
 * FIRSTS: AVID_T, SVID_T
*/
void assignment_expression(){
	Token vid;	/*VID to be sent to the assign function*/
	Token value;/*Value to be sent to the assign function*/
	Stack *stack = s_create(sizeof(Token), STACK_SIZE);

	/*AVID*/
	if (lookahead_token.code == AVID_T) {
		
		vid = lookahead_token;
		match(AVID_T, NO_ATTR);
		match(ASS_OP_T, NO_ATTR);
		arithmetic_expression(stack);

		/*Get the right side value to assign*/
		value = perform_arithmetic(stack);

		/*perform the actual assignment*/
		assign(vid, value);
	}

	/*SVID*/
	else if (lookahead_token.code == SVID_T){

		vid = lookahead_token;
		match(SVID_T, NO_ATTR);
		match(ASS_OP_T, NO_ATTR);
		string_expression(stack);

		/*Perform any string concatenations needed*/
		value = concat(stack);

		/*Perform the assignment*/
		assign(vid, value);
	}
	/*Error*/
	else {
		syn_printe();
	}

	s_destroy(stack);
}

/*
 * PRODUCTION: <selection statement> -> IF (<conditional expression>) THEN <opt_statements> 
										ELSE {<opt_statements>};
 * FIRSTS: IF
*/
void selection_statement(){
	int condition;
	Stack *stack = s_create(sizeof(Token), STACK_SIZE);

	match(KW_T, IF);
	match(LPR_T, NO_ATTR);

	/*Find out whether to evaluate THEN or ELSE*/
	conditional_expression(stack);
	condition = relate(stack);

	match(RPR_T, NO_ATTR);
	match(KW_T, THEN);

	/*execute statements only if condition is true*/
	if (condition) {
		opt_statements();
	} 
	else {
		advance_tokens(KW_T, ELSE);
	}

	match(KW_T, ELSE);
	match(LBR_T, NO_ATTR);

	/*execute statements only if condition is false*/
	if (!condition) {
		opt_statements();
	} 
	else {
		advance_tokens(RBR_T, NO_ATTR);
	}

	match(RBR_T, NO_ATTR); 
	match(EOS_T, NO_ATTR);

	s_destroy(stack);
}

/*
 * PRODUCTION: <iteration statement> -> USING (<assignment expression>,<conditional expression>,<assignment expression>)
										REPEAT { <opt_statements> };
 * FIRSTS: USING
*/
void iteration_statement(){
	Stack *stack = s_create(sizeof(Token), STACK_SIZE);
	int condition, old_forward, old_line;
	int ass2_marker;

	match(KW_T, USING);
	match(LPR_T, NO_ATTR);
	assignment_expression();

	/*Mark where in the buffer we will go back to*/
	old_forward = forward;
	old_line = line;

	match(COM_T, NO_ATTR);

	while (1) {
		conditional_expression(stack);
		condition = relate(stack);

		/*mark where to go back and perform the second assignment expression*/
		ass2_marker = forward;
		match(COM_T, NO_ATTR);

		advance_tokens(RPR_T, NO_ATTR);

		match(RPR_T, NO_ATTR);
		match(KW_T, REPEAT);
		match(LBR_T, NO_ATTR);

		if (condition) {
			opt_statements();
		}
		else {
			advance_tokens(RBR_T, NO_ATTR);
			break;
		}
		match(RBR_T, NO_ATTR);
		match(EOS_T, NO_ATTR);

		forward = ass2_marker;
		lookahead_token = malpar_next_token(sc_buf);
		assignment_expression();

		line = old_line;
		forward = old_forward;
		lookahead_token = malpar_next_token(sc_buf);	
	

	}
	match(RBR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);

	s_destroy(stack);
}

/*
 * PRODUCTION: <input statement> -> INPUT(<variable list>);
 * FIRSTS: INPUT
*/
void input_statement(){
	gp_stack = s_create(sizeof(Token), STACK_SIZE);

	match(KW_T, INPUT);
	match(LPR_T, NO_ATTR);
	variable_list();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);
	
	/*get the input from the user*/
	input(gp_stack);

	s_destroy(gp_stack);
}

/*
 * PRODUCTION: <variable list> -> <variable identifier><variable list1> 
 * FIRSTS: AVID_T, SVID_T
*/
void variable_list(){
	push(gp_stack, &lookahead_token);
	variable_identifier();
	variable_list1();
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
	push(gp_stack, &lookahead_token);
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
	gp_stack = s_create(sizeof(Token), STACK_SIZE);

	match(KW_T, OUTPUT);
	match(LPR_T, NO_ATTR);
	output_statement1();
	match(RPR_T, NO_ATTR);
	match(EOS_T, NO_ATTR);

	output(gp_stack);
	s_destroy(gp_stack);
}

/*
 * PRODUCTION: <output statement1> -> <opt_variable list> | STR_T
 * FIRSTS: AVID_T, SVID_T, STR_T, empty
*/
void output_statement1(){

	/*String literal*/
	if (lookahead_token.code == STR_T){
		push(gp_stack, &lookahead_token);
		match(STR_T, NO_ATTR);
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

}

/*
 * PRODUCTION: <arithmetic expression> -> <unary arithmetic expression>
										| <additive arithmetic expression>
 * FIRSTS: +, -, AVID_T, FPL_T, INL_T, LPR_T
*/
void arithmetic_expression(Stack *stack){
	int code = lookahead_token.code;
	Arr_Op attrib = lookahead_token.attribute.arr_op;

	/*unary arithmetic expression*/
	if (lookahead_token.code == ART_OP_T && (attrib == PLUS || attrib == MINUS)){
		unary_arithmetic_expression(stack);
	}
	/*additive arithmetic expression*/
	else if (code == AVID_T || code == FPL_T || code == INL_T || code == LPR_T){
		additive_arithmetic_expression(stack);
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
void unary_arithmetic_expression(Stack *stack){

	if (lookahead_token.attribute.arr_op == MINUS){
		push(stack, &lookahead_token);
		match(ART_OP_T, MINUS);
	}
	else if (lookahead_token.attribute.arr_op == PLUS){
		push(stack, &lookahead_token);
		match(ART_OP_T, PLUS);
	}
	primary_arithmetic_expression(stack);
}

/*
 * PRODUCTION: <additive arithmetic expression> -> <multiplicative arithmetic expression><additive arithmetic expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T, LPR_T
*/
void additive_arithmetic_expression(Stack *stack){
	multiplicative_arithmetic_expression(stack);
	additive_arithmetic_expression1(stack);
}


/*
 * PRODUCTION: <additive arithmetic expression1> ->   
					  + <multiplicative arithmetic expression><additive arithmetic expression1>
					| - <multiplicative arithmetic expression><additive arithmetic expression1>
					| empty
 * FIRSTS: +, -, empty
*/
void additive_arithmetic_expression1(Stack *stack){

	/*Match the two possible cases*/
	if (lookahead_token.code == ART_OP_T){
		if (lookahead_token.attribute.arr_op == MINUS){
			push(stack, &lookahead_token);
			match(ART_OP_T, MINUS);
		}
		else if (lookahead_token.attribute.arr_op == PLUS){
			push(stack, &lookahead_token);
			match(ART_OP_T, PLUS);
		}
		else {
			return;
		}

		/*Now do the rest*/
		multiplicative_arithmetic_expression(stack);
		additive_arithmetic_expression1(stack);
	}

	/*empty*/

}

/*
 * PRODUCTION: <multiplicative arithmetic expression> -> 
					<primary arithmetic expression><multiplicative arithmetic expression1>	
 * FIRSTS: AVID_T, FPL_T, INL_T, LPR_T
*/
void multiplicative_arithmetic_expression(Stack *stack){
	primary_arithmetic_expression(stack);
	multiplicative_arithmetic_expression1(stack);
}

/*
 * PRODUCTION: <multiplicative arithmetic expression1> ->   
					  * <primary arithmetic expression><multiplicative arithmetic expression1>
					| / <primary arithmetic expression><multiplicative arithmetic expression1>
					| empty
 * FIRSTS: *, /
*/
void multiplicative_arithmetic_expression1(Stack *stack){

	/*Match one of the two possible cases*/
	if (lookahead_token.code == ART_OP_T){
		if (lookahead_token.attribute.arr_op == MULT){
			push(stack, &lookahead_token);
			match(ART_OP_T, MULT);
		}
		else if (lookahead_token.attribute.arr_op == DIV){
			push(stack, &lookahead_token);
			match(ART_OP_T, DIV);
		}
		else {
			return;
		}

		/*Now do the rest*/
		primary_arithmetic_expression(stack);
		multiplicative_arithmetic_expression1(stack);
	}

	/*empty*/
}

/*
 * PRODUCTION: <primary arithmetic expression> -> 
					AVID_T | FPL_T | INL_T | (<arithmetic expression>)	
 * FIRSTS: AVID_T, FPL_T, INL_T, LPR_T
*/
void primary_arithmetic_expression(Stack *stack){

	if (lookahead_token.code == AVID_T){
		push(stack, &lookahead_token);
		match(AVID_T, NO_ATTR);
	}
	else if (lookahead_token.code == FPL_T){
		push(stack, &lookahead_token);
		match(FPL_T, NO_ATTR);
	}
	else if (lookahead_token.code == INL_T){
		push(stack, &lookahead_token);
		match(INL_T, NO_ATTR);
	}
	else if (lookahead_token.code == LPR_T){
		push(stack, &lookahead_token);
		match(LPR_T, NO_ATTR);
		arithmetic_expression(stack);
		push(stack, &lookahead_token);
		match(RPR_T, NO_ATTR);
	}
	else {
		syn_printe();
		return;
	}
}

/*
 * PRODUCTION: <string expression> ->
					<primary string expression><string expression1>
 * FIRSTS: SVID_T, STR_T
*/
void string_expression(Stack *stack){
	primary_string_expression(stack);
	string_expression1(stack);
}

/*
 * PRODUCTION: <string expression1> -> 
					<< <primary string expression><string expression1> | empty
 * FIRSTS: SCC_OP_T
*/
void string_expression1(Stack *stack){

	/*String concatenation*/
	if (lookahead_token.code == SCC_OP_T){
		match(SCC_OP_T, NO_ATTR);
		primary_string_expression(stack);
		string_expression1(stack);
	}

	/*do nothing for empty*/
}

/*
 * PRODUCTION: <primary string expression> -> SVID_T | STR_T	
 * FIRSTS: SVID_T, STR_T
*/
void primary_string_expression(Stack *stack){

	/*SVID*/
	if (lookahead_token.code == SVID_T){
		push(stack, &lookahead_token);
		match(SVID_T, NO_ATTR);
	}
	/*STRING LITERAL*/
	else {
		push(stack, &lookahead_token);
		match(STR_T, NO_ATTR);
	}
}

/*
 * PRODUCTION: <conditional expression> -> <logical OR expression>
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void conditional_expression(Stack *stack){
	logical_or_expression(stack);
}

/*
 * PRODUCTION: <logical or expression> -> <logical AND expression> <logical OR expression1>	
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void logical_or_expression(Stack *stack){
	logical_and_expression(stack);
	logical_or_expression1(stack);
}

/*
 * PRODUCTION: <logical or expression1> -> 
					.OR. <logical AND expression> <logical OR expression1> | empty		
 * FIRSTS: .OR., empty
*/
void logical_or_expression1(Stack *stack){

	/*OR*/
	if (lookahead_token.code == LOG_OP_T){
		if (lookahead_token.attribute.log_op == OR) {
			push(stack, &lookahead_token);
			match(LOG_OP_T, OR);
		}
		else if (lookahead_token.attribute.log_op == AND){
			
		}
		else {
			return;
		}

		/*Do common things*/
		logical_and_expression(stack);
		logical_or_expression1(stack);
	}

	/*Do nothing for empty*/
}

/*
 * PRODUCTION: <logical AND expression> -> <relational expression> <logical AND expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T
*/
void logical_and_expression(Stack *stack){
	relational_expression(stack);
	logical_and_expression1(stack);
}

/*
 * PRODUCTION: <logical AND expression1> -> 
					.AND. <relational expression> <logical OR expression1> |empty
 * FIRSTS: .AND., empty
*/
void logical_and_expression1(Stack* stack){
	
	/*AND*/
	if (lookahead_token.code == LOG_OP_T && lookahead_token.attribute.log_op == AND){
		push(stack, &lookahead_token);
		match(LOG_OP_T, AND);
		relational_expression(stack);
		logical_and_expression1(stack);
	}

	/*empty*/
}

/*
 * PRODUCTION: <relational expression> -> 
					<primary a_relational expression><primary a_relational expression1>
					| <primary s_relational expression><primary s_relational expression1>
 * FIRSTS: AVID_T, INL_T, FPL_T
*/
void relational_expression(Stack *stack){
	Stack *r_stack = s_create(sizeof(Token), STACK_SIZE);
	int code = lookahead_token.code;
	Token condition;

	/* A_RELATIONAL*/
	if (code == AVID_T || code == FPL_T || code == INL_T){
		primary_a_relational_expression(r_stack);
		primary_a_relational_expression1(r_stack);
		condition.code = INL_T;
		condition.attribute.int_value = a_relate(r_stack);
		push(stack, &condition);
	}
	/* S_RELATIONAL*/
	else if (code == SVID_T || code == STR_T){
		primary_s_relational_expression(r_stack);
		primary_s_relational_expression1(r_stack);
		condition.code = INL_T;
		condition.attribute.int_value = s_relate(r_stack);
		push(stack, &condition);
	}
	/*INVALID*/
	else {
		syn_printe();
	}
	s_destroy(r_stack);
}

/*
 * PRODUCTION: <primary a_relational expression> -> AVID_T | FPL_T | INL_T
 * FIRSTS: AVID_T, FPL_T, INL_T
*/
void primary_a_relational_expression(Stack *r_stack){
	
	/*AVID*/
	if (lookahead_token.code == AVID_T){
		push(r_stack, &lookahead_token);
		match(AVID_T, NO_ATTR);
	}
	/*FLOATING POINT LITERAL*/
	else if (lookahead_token.code == FPL_T){
		push(r_stack, &lookahead_token);
		match(FPL_T, NO_ATTR);
	}
	/*INTEGER LITERAL*/
	else if (lookahead_token.code == INL_T){
		push(r_stack, &lookahead_token);
		match(INL_T, NO_ATTR);
	}
	/*Nothing else allowed*/
	else {
		syn_printe();
	}
}

/*
 * PRODUCTION: <primary a_relational expression1> -> 
						== <primary a_relational expression>
						| != <primary a_relational expression>
						| > <primary a_relational expression>
						| < <primary a_relational expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_a_relational_expression1(Stack *r_stack){
	Rel_Op attrib = lookahead_token.attribute.rel_op;

	/*error*/
	if (lookahead_token.code != REL_OP_T){
		syn_printe();
		return;
	}

	/*IS EQUAL TO*/
	if (attrib == EQ){
		push(r_stack, &lookahead_token);
		match(REL_OP_T, EQ);
	}
	/*NOT EQUAL*/
	if (attrib == NE){
		push(r_stack, &lookahead_token);
		match(REL_OP_T, NE);
	}
	/*GREATER THAN*/
	if (attrib == GT){
		push(r_stack, &lookahead_token);
		match(REL_OP_T, GT);
	}
	/*LESS THAN*/
	if (attrib == LT){
		push(r_stack, &lookahead_token);
		match(REL_OP_T, LT);
	}
	primary_a_relational_expression(r_stack);
}

/*
 * PRODUCTION: <primary s_relational expression> -> <primary string expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_s_relational_expression(Stack *s_stack){
	primary_string_expression(s_stack);
}

/* 
 *PRODUCTION: <primary s_relational expression1> ->
						== <primary s_relational expression>
						| != <primary s_relational expression>
						| > <primary s_relational expression>
						| < <primary s_relational expression>
 * FIRSTS: ==, !=, >, <
*/
void primary_s_relational_expression1(Stack *s_stack){
	Rel_Op attrib = lookahead_token.attribute.rel_op;

		/*error*/
	if (lookahead_token.code != REL_OP_T){
		syn_printe();
		return;
	}

	/*IS EQUAL TO*/
	if (attrib == EQ){
		push(s_stack, &lookahead_token);
		match(REL_OP_T, EQ);
	}
	/*NOT EQUAL*/
	if (attrib == NE){
		push(s_stack, &lookahead_token);
		match(REL_OP_T, NE);
	}
	/*GREATER THAN*/
	if (attrib == GT){
		push(s_stack, &lookahead_token);
		match(REL_OP_T, GT);
	}
	/*LESS THAN*/
	if (attrib == LT){
		push(s_stack, &lookahead_token);
		match(REL_OP_T, LT);
	}
	primary_s_relational_expression(s_stack);
}