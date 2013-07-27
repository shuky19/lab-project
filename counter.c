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
	symbol *sym;
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