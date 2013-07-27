/*
** This file responsible managing all counters 
** for the compilation calculation and holing all needed tables
** for the compiler
*/

#ifndef COUNTER
#define COUNTER value
#include "structure.h"
#include <string.h>
#include <stdlib.h>
#define MAX_TABLE_LENGTH 1000
#define MAX_SYMBOL_LENGTH 50

/*
** Hold all the instruction in the compiled file
*/
typedef struct
{
	int word_counter; /* Represent the amount of word taken in the table */
	int index; /* Represent the index of the next instruction in table */
	command_ptr instructions[MAX_TABLE_LENGTH];
} instructions_counter;

/*
** Hold all data in the compiled line
*/
typedef struct
{
	int word_counter; /* Represent the amount of word taken in the table */
	int index; /* Represent the index of the next data in table */
	instruction_line_ptr data[MAX_TABLE_LENGTH];
} data_counter;

typedef enum { COMMAND_TABLE, EXTERNAL_TABLE, DATA_TABLE, ENTRY_TABLE } symbol_source;

/*
** Represent a symbol in the compiled file
*/
typedef struct
{
	char *name;
	symbol_source source;
	int address;
} symbol;

typedef symbol *symbol_ptr;

/*
** Symbol table that hold all symbol in the compiled file
*/
typedef struct
{
	int counter;
	symbol_ptr symbols[MAX_TABLE_LENGTH];
} symbols_table;

/*
** Find the symbol's address
*/
int get_symbol_address(symbols_table *table, char *symbol_name);

/*
** add new symbol to the given symbol table
*/
void add_symbol(symbols_table *table, char *name, int address, symbol_source source);

/*
** add new data to the given data counter
*/
void add_data(data_counter *dc, instruction_line_ptr data);

/*
** add new symbol to the given instruction counter
*/
void add_instruction(instructions_counter *ic, command *comm);
#endif