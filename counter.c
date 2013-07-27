#include "stdlib.h"
#include "counter.h"

/*
** Find a symbol in the given symbol table
*/
struct symbol *get_symbol(struct symbols_table *table, char *symbol_name)
{
	return NULL;
}

/*
** add new symbol to the given symbol table
*/
void add_symbol(struct symbols_table *table, char *name, int line_number)
{
}

/*
** add new data to the given data counter
*/
void add_data(struct data_counter *dc, int data)
{
}

/*
** add new symbol to the given instruction counter
*/
void add_instruction(struct instructions_counter *ic, struct command *comm)
{
}