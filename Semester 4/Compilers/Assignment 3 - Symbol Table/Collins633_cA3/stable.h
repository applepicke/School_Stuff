/* File Name: stable.h
 * Version: 1.0
 * Author: William Collins (040652633)   
 * Course: CST8152 - Compilers
 * Assignment: 3
 * Date: July 22, 2011
 * Professor: Svillen Ranev
 * Purpose: Declarations necessary for the symbol table
 */
#ifndef STABLE_H
#define STABLE_H

#define INIT_CAP 1			/*The initial capacity of the lexeme buffer*/
#define FAIL -1				/*The return value for functions that fail*/
#define STVR_NOT_FOUND -1	/*STVR exists*/
#define TABLE_FULL -1		/*cannot add any more records to the table*/
#define SUCCESS 1			/*SUCCESS :)*/

/*****************************Status Field Masks******************************/
#define STATUS_INIT	0xFFF8		/*The initial value for the status_field*/
#define DATA_TYPE_MASK 0xFFF9	/*Used for resetting the data type bits*/
#define U_FLAG_MASK 0x0001		/*Mask for the update flag bit*/

/*Data Type Masks*/
#define STRING_TYPE_MASK 0x0006	/*Mask for setting string Data type VIDs*/
#define FLOAT_TYPE_MASK 0x0004	/*Mask for float data types VIDs*/
#define INT_TYPE_MASK 0x0002	/*Mask for int data types VIDs*/


/*****************************************************************************/

/*The initial value used for a Symbol Table record*/
typedef union InitialValue {
	int int_val;	/* integer variable initial value */
	float fpl_val;	/* floating-point variable initial value */
	int str_offset;	/* string variable initial vvalue(offset) */
} InitialValue;


/*A structure that holds information about an individual record in the symbol table*/
typedef struct SymbolTableVidRecord {
	unsigned short status_field;	/*variable record status field*/
	char *plex;		/*pointer to lexeme (VID name) in buffer CA*/
	int o_line;		/*line of first occurence*/
	InitialValue i_value;	/*variable initial value */
} STVR;


/*A structure representing the symbol table itself*/
typedef struct SymbolTableDescriptor {
	STVR *pstvr;	/*pointer to array of STVR*/
	int st_size;	/* size in number of STVR elements*/
	int st_offset;	/*offset in number of STVR elements*/
	Buffer *plsBD;	/*pointer to the lexeme storage buffer descriptor*/
} STD;



/*Forward Declarations*/
STD st_create(int st_size);
int st_install(STD sym_table, char *lexeme, int line);
int st_lookup(STD sym_table, char *lexeme);
int st_update_type(STD sym_table, int vid_offset, char v_type);
int st_update_value(STD sym_table, int vid_offset, InitialValue i_value);
char st_get_type (STD sym_table, int vid_offset);
void st_destroy(STD sym_table);
int st_print(STD sym_table);
int st_store(STD sym_table);
int st_sort(STD sym_table, char s_order);

int asc_compare(const void *record1, const void *record2);
int desc_compare(const void *record1, const void *record2);


#endif