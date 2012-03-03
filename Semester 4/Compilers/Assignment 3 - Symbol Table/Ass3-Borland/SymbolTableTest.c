#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "stable.h"
#include "assert.h"

STD sym_table;
InitialValue updateValue;

int main(){

	/* This Test File performs basic functionality testing
		for the symbol table*/

	/*CREATE BAD STM*/
	sym_table = st_create(-1);
	assert(sym_table.st_size == 0);

	/*DESTROY*/
	st_destroy(sym_table);

	/*CREATE*/
	sym_table = st_create(100);
	assert(sym_table.plsBD != NULL);
	assert(sym_table.pstvr != NULL);
	assert(sym_table.st_size != 0);
	assert(sym_table.st_offset == 0);

	/*INSTALL_INT_VID*/
	st_install(sym_table, "icount", 12);
	assert(sym_table.pstvr[0].o_line == 12);
	assert(st_get_type(sym_table, 0) == 'I' );
	assert(sym_table.pstvr[0].i_value.int_val == 0); 
	assert(!strcmp(sym_table.pstvr[0].plex, "icount"));

	/*INSTALL_FLT_VID*/
	st_install(sym_table, "count", 13);
	assert(sym_table.pstvr[1].o_line == 13);
	assert(sym_table.pstvr[1].i_value.fpl_val == 0.0f);
	assert(st_get_type(sym_table, 1) == 'F');
	assert(!strcmp(sym_table.pstvr[1].plex, "count"));

	/*INSTALL_STRING_VID*/
	st_install(sym_table, "count#", 14);
	assert(sym_table.pstvr[2].o_line == 14);
	assert(sym_table.pstvr[2].i_value.str_offset == -1);
	assert(st_get_type(sym_table, 2) == 'S');
	assert(!strcmp(sym_table.pstvr[2].plex, "count#"));

	/*UPDATE TYPE*/
	st_update_type(sym_table, 0, 'F');
	assert(sym_table.pstvr[0].o_line == 12);
	assert(st_get_type(sym_table, 0) == 'F' );
	assert(sym_table.pstvr[0].i_value.int_val == 0); 
	assert(!strcmp(sym_table.pstvr[0].plex, "icount"));

	/*UPDATE VALUE*/
	updateValue.fpl_val = 12.12f;
	st_update_value(sym_table, 1, updateValue);
	assert(sym_table.pstvr[1].o_line == 13);
	assert(sym_table.pstvr[1].i_value.fpl_val == 12.12f);
	assert(st_get_type(sym_table, 1) == 'F');
	assert(!strcmp(sym_table.pstvr[1].plex, "count"));

	return 0;
}