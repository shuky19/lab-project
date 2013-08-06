#include "counter.h"

/*
** Find the symbol's index
*/
int get_symbol_address(symbols_table *table, char *symbol_name)
{
	int i;
	int index = -1;

	for (i = 0; i < table->counter; ++i)
	{
		char *current_symbol_name = table->symbols[i]->name;
		if(0 == strncmp(symbol_name, current_symbol_name, MAX_SYMBOL_LENGTH))
		{
			index = i;
			break;
		}
	}

	return index;
}

/*
** add new symbol to the given symbol table
*/
void add_symbol(symbols_table *table, char *name, int address, symbol_source source)
{
	symbol *sym = (symbol *)malloc(sizeof(symbol));
	sym->name = name;
	sym->address = address;
	sym->source = source;
	table->symbols[table->counter++] = sym;
}

/*   
** add new data to the given data counter
*/
void add_data(data_counter *dc, instruction_line_ptr data)
{
	/* Add data to the data table */
	dc->data[dc->index++] = data;

	/* Incerement counter acoutrding to the command size
	   One word for the command + one for each extra word needed */
	dc->word_counter += data->content_length + 1;
}

/*
** add new symbol to the given instruction counter
*/
void add_instruction(instructions_counter *ic, command *comm)
{
	/* Add command to the instructions table */
	ic->instructions[ic->index++] = comm;
	comm->address = ic->index;

	/* Incerement counter acoutrding to the command size
	   One word for the command + one for each extra word needed */
	ic->word_counter += comm->extra_word_count + 1;
}

/*
** Create and intialize symbol table
*/
symbols_table *create_symbol_table()
{
	symbols_table *sym_table = (symbols_table *)malloc(sizeof(symbols_table));
	sym_table->symbols = (symbol **)calloc(MAX_TABLE_LENGTH, sizeof(symbol *));	
	sym_table->counter = 0;
	return sym_table;
}

/*
** Free symbol table from memory
*/
void free_symbol_table(symbols_table *sym_table)
{
	int i;

	for (i = 0; i < sym_table->counter; ++i)
	{
		free(sym_table->symbols[i]->name);
		free(sym_table->symbols[i]);
	}

	free(sym_table->symbols);
	free(sym_table);
}

/*
** Create and intialize instruction counter
*/
instructions_counter *create_instruction_counter()
{
	instructions_counter *ic = (instructions_counter *)malloc(sizeof(instructions_counter));
	ic->instructions = (command **)calloc(MAX_TABLE_LENGTH, sizeof(command *));
	ic->index = 0;
	ic->word_counter = 0;

	return ic;
}

/*
** Free instruction counter from memory
*/
void free_instruction_counter(instructions_counter *ic)
{
}

/*
** Create and intialize instruction counter
*/
data_counter *create_data_counter()
{
	data_counter *dc = (data_counter *)malloc(sizeof(data_counter));
	dc->data = (instruction_line **)calloc(MAX_TABLE_LENGTH, sizeof(instruction_line *));
	dc->index = 0;
	dc->word_counter = 0;

	return dc;
}

/*
** Free data counter from memory
*/
void free_data_counter(data_counter *ic)
{

}
