#ifndef COUNTER
#define COUNTER value
#include "structure.h"
#define MAX 1000

struct instructions_counter
{
	int counter;
	command instructions[MAX];
};

struct data_counter
{
	int counter;
	int data[MAX];
};

struct symbol
{
	char * name;
	int line_number;
};

struct symbols_table
{
	int counter;
	struct symbol symbols[MAX];
};

struct symbol *get_symbol(symbols_table *table, char *symbol_name);

void add_symbol(symbols_table *table, char *name, int line_number);
#endif