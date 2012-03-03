/* File Name: stable.c
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 3
 * Date: July 22, 2011
 * Professor: Svillen Ranev
 * Purpose: A symbol table 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "buffer.h"
#include "stable.h"

/*Global Variables*/
extern STD sym_table;

/*Static function declarations*/
static void st_setsize(void);
static void st_inc_offset(void);
static void fix_pointers(STD);
static void arrange_lexbuf(STD);

/*
 * Purpose: Creates a Symbol Table for use
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	st_size - The number of records you want the symbol table to hold
 * Return value: The new symbol table descriptor
*/
STD st_create(int st_size){
	STD tempSTD;
	Buffer *stdBuffer;

	/*Make a temporary buffer that will hold the lexemes*/
	stdBuffer = b_create(INIT_CAP, 1, 'a');

	/* Initialize the members of the symbol table*/
	tempSTD.pstvr =  (STVR*) malloc(sizeof(STVR) * st_size);
	tempSTD.plsBD = stdBuffer;
	tempSTD.st_offset = 0;
	tempSTD.st_size = st_size;

	/*Check for problems. A size of 0 will indicate an unusable Symbol Table*/
	if (stdBuffer == NULL || st_size < 0){
		tempSTD.st_size = 0;
	}

	return tempSTD;

}

/*
 * Purpose: Adds a new record to the symbol table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				lexeme - The lexeme you want to add to the table
				line - the line number the lexeme was found
 * Return value: FAIL on fail, otherwise the offset of the lexeme in the lexeme buffer
*/
int st_install(STD sym_table, char *lexeme, int line){
	STVR new_record;	/*The new record to be added to the table*/
	Buffer *st_buf;
	int offset;
	int i, len;
	char c = lexeme[0]; /*The first letter of the lexeme determines the type*/

	/*Make sure we have a valid Symbol Table*/
	if (sym_table.st_size == 0){
		return FAIL;
	}

	st_buf = sym_table.plsBD; /*Strip out reoccuring calls to sym_table*/

	/*First let us check to see if the lexeme is already in the table*/
	offset = st_lookup(sym_table, lexeme);	/*if the lexeme exists, this is its location*/
	if (offset != STVR_NOT_FOUND){
		return offset;
	}

	/*Check to make sure we have enough room for a new record*/
	if (sym_table.st_offset == sym_table.st_size){
		return TABLE_FULL;
	}

	/*The table doesn't have the lexeme, so let's add it*/
	new_record.o_line = line;
	new_record.status_field = STATUS_INIT;

	/*Set the mark so that we know where we entered the lexeme*/
	ca_setmark(st_buf, ca_getsize(st_buf));

	/*Add the lexeme to the buffer*/
	len = strlen(lexeme);
	for (i = 0; i <= len; i++){
		st_buf = ca_addc(st_buf, lexeme[i]);
		/*If the buffer moved, fix the pointers in the records*/
		if (st_buf->r_flag) {
			fix_pointers(sym_table);
		}
	}

	/*Check for runtime errors*/
	if (st_buf == NULL){
		return FAIL;
	}

	/*Now assign the pointer to the lexeme*/
	new_record.plex = st_buf->ca_head + ca_getmark(st_buf);

	/*If the lexeme is a string type, set its update flag and default type value*/
	if (lexeme[len-1] == '#'){
		new_record.status_field |= U_FLAG_MASK;
		new_record.status_field |= STRING_TYPE_MASK;
		new_record.i_value.str_offset = -1;
	}
	/* Check for an integer VID*/
	else if (c == 'i' || c == 'j' || c == 'm' || c == 'n'){
		new_record.status_field |= INT_TYPE_MASK;
		new_record.i_value.int_val = 0;
	}
	/*Must be floating point*/
	else {
		new_record.status_field |= FLOAT_TYPE_MASK;
		new_record.i_value.fpl_val = 0.0f;
	}

	/*Install the new record in the table*/
	sym_table.pstvr[sym_table.st_offset] = new_record; 

	/* Now we have to increment our offset in the "global" symbol table*/
	st_inc_offset();

	return sym_table.st_offset;

}

/*
 * Purpose: Searches for a lexeme in the symbol table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				lexeme - The lexeme being looked for
 * Return value: STRVR_FOUND if not found, meaning an entry was added, otherwise the offset of the entry in the array of STVRs
*/
int st_lookup(STD sym_table, char *lexeme){
	int i;

	/*Make sure we have a valid symbol table*/
	if (sym_table.st_size == 0){
		return FAIL;
	}

	/*Perform a backwards search of the symbol table*/
	for (i = sym_table.st_offset - 1; i >= 0; i--) {
		/*If we find the lexeme, it already exists, so don't add it*/
		if (strcmp(sym_table.pstvr[i].plex, lexeme) == 0) {
			return i;
		}
	}

	return STVR_NOT_FOUND;
}

/*
 * Purpose: Update the data type indicator for a specific STVR
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				vid_offset - The offset of the record to update
				v_type - The new variable type
 * Return value: FAIL if cannot be updated, otherwise returns the vid_offset
*/
int st_update_type(STD sym_table, int vid_offset, char v_type){
	unsigned short *status; 

	/*Let's make sure the offset is valid*/
	if (sym_table.st_size == 0 || vid_offset >= sym_table.st_size || vid_offset <= 0){
		return FAIL;
	}

	status = &sym_table.pstvr[vid_offset].status_field; /* Shortcut ;) */

	/*The update flag has already been set*/
	if ( (*status & U_FLAG_MASK) == U_FLAG_MASK) {
		return FAIL;
	}

	/*Now we can do some updating. Check if the type is a float*/
	if (v_type == 'F'){
		*status &= DATA_TYPE_MASK;	/*reset the data type bits*/ 
		*status |= FLOAT_TYPE_MASK; /*set the float type bit*/
		*status |= U_FLAG_MASK;		/*could do (*status)++, but not as readable*/
	}
	/*Check if the type is an int*/
	if (v_type == 'I'){
		*status &= DATA_TYPE_MASK;	/*reset the data type bits*/
		*status |= INT_TYPE_MASK;	/*set the int type bit*/
		*status |= U_FLAG_MASK;		
	}

	return vid_offset;
}

/*
 * Purpose: Update the value of an STVR
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				vid_offset - The offset of the record to update
				i_value - The new value of the record
 * Return value: FAIL if cannot be updated, otherwise returns the vid_offset
*/
int st_update_value(STD sym_table, int vid_offset, InitialValue i_value){
	
	/*make sure the offset is valid*/
	if (sym_table.st_size == 0 || vid_offset >= sym_table.st_size || vid_offset <= 0){
		return FAIL;
	}

	/* Update the value*/
	sym_table.pstvr[vid_offset].i_value = i_value;

	return vid_offset;
}

/*
 * Purpose: Retrieve the type of a specified record in the symbol table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				vid_offset - The offset of the record to look at
 * Return value: FAIL if cannot be updated, 'F' for float, 'I' for int, 'S' for string
*/
char st_get_type (STD sym_table, int vid_offset){
	unsigned short status;

	/* Make sure we have a valid offset*/
	if (sym_table.st_size == 0 || vid_offset >= sym_table.st_offset || vid_offset < 0){
		return FAIL;
	}
	status = sym_table.pstvr[vid_offset].status_field;	/*shortcut*/

	/*Find and return the type*/
	if ( (status & STRING_TYPE_MASK) == STRING_TYPE_MASK) return 'S';
	if (status & INT_TYPE_MASK) return 'I'; 
	if (status & FLOAT_TYPE_MASK) return 'F';

	return FAIL;
}

/*
 * Purpose: free the dynamic elements of the symbol table, and designate it as destroyed (size is zero)
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be destroyed
*/
void st_destroy(STD sym_table){

	/*Set the size of the sym_table to 0*/
	st_setsize();

	/*free the array of records*/
	if (sym_table.pstvr != NULL) {
		free(sym_table.pstvr);
	}

	/*destroy the buffer. The destroy function checks for its existence*/
	b_destroy(sym_table.plsBD);

}

/*
 * Purpose: Prints out the contents of the symbol table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
 * Return value: FAIL on error, otherwise number of entries
*/
int st_print(STD sym_table){
	int i;

	/*Let's return early if the sym_table has nothing in it*/
	if (sym_table.st_size == 0){
		return FAIL;
	}

	/*Nice lovely Header*/
	printf("\nSymbol Table\n____________\n\n");
	printf("Line Number Variable Identifier\n");

	/*Print out each VID in the symbol table*/
	for (i = 0; i < sym_table.st_offset; i++) {
		printf("%2d          %s\n", sym_table.pstvr[i].o_line, sym_table.pstvr[i].plex);
	}
	
	return i;
}

/*
 * Purpose: Sets the size of the global symbol table to 0
 * Author: William Collins (040652633)
 * History/Versions: 1.0
*/
static void st_setsize(void){
	sym_table.st_size = 0;
}

/*
 * Purpose: Increments the offset of the global symbol table by 1
 * Author: William Collins (040652633)
 * History/Versions: 1.0
*/
static void st_inc_offset(void){
	sym_table.st_offset++;
}

/*
 * Purpose: Stores the symbol table in a file
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be stored
 * Return value: FAIL on error, otherwise number of records stored
*/
int st_store(STD sym_table){
	int i;
	FILE *st_file;

	/*Can't do much with an empty table*/
	if (sym_table.st_size == 0) {
		return FAIL;
	}

	/*Open a file for writing. Overwrite if it already exists*/
	st_file = fopen("$stable.ste", "w");

	/*Must always check for failure*/
	if (st_file == NULL) {
		return FAIL;
	}

	/*write the size of the symbol table*/
	fprintf(st_file, "%d", sym_table.st_size);

	/*Write each record*/
	for (i = 0; i < sym_table.st_size; i++){
		fprintf(st_file, " %X", sym_table.pstvr[i].status_field);	/*print the status field*/
		fprintf(st_file, " %d", strlen(sym_table.pstvr[i].plex));	/*print the length of the lexeme*/
		fprintf(st_file, " %s", sym_table.pstvr[i].plex);			/*print the lexeme */
		fprintf(st_file, " %d", sym_table.pstvr[i].o_line);			/*print the line number*/

		/*now determine what type it is so that we can print the proper type*/
		if (st_get_type(sym_table, i) == 'F'){
			fprintf(st_file, " %.2f", sym_table.pstvr[i].i_value.fpl_val);
		}
		/*if not float, then we want an int value from the InitialValue*/
		else {
			fprintf(st_file, " %d", sym_table.pstvr[i].i_value.int_val);
		}
	}

	printf("\nSymbol Table stored.\n");

	return i;

}

/*
 * Purpose: Sorts the records in the symbol table 
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
				s_order - The order of sorting we want
 * Return value: FAIL on error, otherwise number of records stored
*/
int st_sort(STD sym_table, char s_order){
	
	/*We need to make sure we have a valid symbol table*/
	if (sym_table.st_size == 0){
		return FAIL;
	}

	if (s_order == 'A'){
		qsort(sym_table.pstvr, sym_table.st_offset, sizeof(STVR), asc_compare);
	}
	if (s_order == 'D'){
		qsort(sym_table.pstvr, sym_table.st_offset, sizeof(STVR), desc_compare);
	}

	arrange_lexbuf(sym_table);

	return SUCCESS;
}

/*
 * Purpose: Arranges the lexeme buffer in the order of the symbol table records
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table to be used
 * Return value: FAIL on error, otherwise the number of records in the table
*/
static void arrange_lexbuf(STD sym_table){
	Buffer *newHead;
	int i, j;

	/*Make sure our sym_table is okay*/
	if (sym_table.st_size == 0){
		return;
	}

	/*Create a new buffer to be used*/
	newHead = b_create(ca_getsize(sym_table.plsBD), 0, 'f');

	if (newHead == NULL){
		return;
	}

	/*Loop through each record in the table*/
	for (i = 0; i < sym_table.st_offset; i++){
		/*add current record lexeme into the new buffer*/
		for (j = 0; sym_table.pstvr[i].plex[j] != '\0'; j++){
			newHead = ca_addc(newHead, sym_table.pstvr[i].plex[j]);
		}
		newHead = ca_addc(newHead, '\0');
	}

	/*Make sure no errors occured*/
	if (newHead == NULL){
		return;
	}

	/*Now swap the heads of the buffers. Sorry SiR, I'm breaching the Buffer data structure ;) */
	sym_table.plsBD->ca_head = newHead->ca_head;

	/*Now make the pointer in each record point to the appropriate lexeme*/
	fix_pointers(sym_table);

}
/*
 * Purpose: Fixes the potential dangling pointers in the STVRs of the symbol table
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	sym_table - The symbol table comntaining the dangling pointers
 * Justify: in my eyes, this abstraction makes its use much more readable. It shortens
			the st_install function, and shorter functions break things down and make them
			easier to understand. Like I said, this is just in my eyes. Wink ;)
*/
static void fix_pointers(STD sym_table) {

	int i, prev_len = 0;	/*The prev_len holds the length of the previous STVR lexeme. Recycled.*/

	if (sym_table.st_size == 0){
		return;
	}

	/*First make sure the first record points to the buffer contents*/
	sym_table.pstvr[0].plex = sym_table.plsBD->ca_head;

	/*Now do the rest of them, calculating offsets by the length of the previous*/
	for (i = 0; i < sym_table.st_offset; i++){
		sym_table.pstvr[i].plex = sym_table.pstvr->plex + prev_len;
		prev_len += strlen(sym_table.pstvr[i].plex) + 1;
	}
}

/*
 * Purpose: A comparator function to help sort records in ascending order
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	record1 - the first record being compared
				record2 - the second record being compared
 * Return value: A positive value if record 1 is greater than record 2, negative otherwise
*/
int asc_compare(const void *record1, const void *record2){
	char *string1 = ((STVR*)record1)->plex;
	char *string2 = ((STVR*)record2)->plex;

	return strcmp(string1, string2);
}

/*
 * Purpose: A comparator function to help sort records in descending order
 * Author: William Collins (040652633)
 * History/Versions: 1.0
 * Parameters:	record1 - the first record being compared
				record2 - the second record being compared
 * Return value: A positive value if record 1 is less than record 2, negative otherwise
*/
int desc_compare(const void *record1, const void *record2){
	char *string1 = ((STVR*)record1)->plex;
	char *string2 = ((STVR*)record2)->plex;

	return strcmp(string1, string2) * -1;
}
