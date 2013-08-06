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
#include <stdio.h>
#define MAX_TABLE_LENGTH 100
#define MAX_SYMBOL_LENGTH 50
#define START_ADDRESS 100

/*
** Hold all the instruction in the compiled file
*/
typedef struct
{
	int word_counter; /* Represent the amount of word taken in the table */
	int index; /* Represent the index of the next instruction in table */
	command_ptr *instructions;
} instructions_counter;

/*
** Hold all data in the compiled line
*/
typedef struct
{
	int word_counter; /* Represent the amount of word taken in the table */
	int index; /* Represent the index of the next data in table */
	instruction_line_ptr *data;
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
	symbol_ptr *symbols;
} symbols_table;

/*
** Find the symbol's address
*/
int get_symbol_address(symbols_table *table, char *symbol_name, int data_start_address);

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

/*
** Create and intialize symbol table
*/
symbols_table *create_symbol_table();

/*
** Free symbol table from memory
*/
void free_symbol_table(symbols_table *sym_table);

/*
** Create and intialize instruction counter
*/
instructions_counter *create_instruction_counter();

/*
** Free instruction counter from memory
*/
void free_instruction_counter(instructions_counter *ic);

/*
** Create and intialize instruction counter
*/
data_counter *create_data_counter();

/*
** Free data counter from memory
*/
void free_data_counter(data_counter *ic);
#endif