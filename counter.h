/*
** This file responsible managing all counters 
** for the compilation calculation and holing all needed tables
** for the compiler
*/

#ifndef COUNTER
#define COUNTER value
#include "structure.h"
#define MAX 1000

/*
** Hold all the instruction in the compiled file
*/
struct instructions_counter
{
	int counter;
	struct command instructions[MAX];
};

/*
** Hold all data in the compiled line
*/
struct data_counter
{
	int counter;
	int data[MAX];
};

/*
** Represent a symbol in the compiled file
*/
struct symbol
{
	char * name;
	int line_number;
};

/*
** Symbol table that hold all symbol in the compiled file
*/
struct symbols_table
{
	int counter;
	struct symbol symbols[MAX];
};

/*
** Find a symbol in the given symbol table
*/
struct symbol *get_symbol(struct symbols_table *table, char *symbol_name);

/*
** add new symbol to the given symbol table
*/
void add_symbol(struct symbols_table *table, char *name, int line_number);

/*
** add new data to the given data counter
*/
void add_data(struct data_counter *dc, int data);

/*
** add new symbol to the given instruction counter
*/
void add_instruction(struct instructions_counter *ic, struct command *comm);
#endif