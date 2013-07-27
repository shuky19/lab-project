#include "file_writer.h"

/*
** Write output files (Object file, Entry file, External file)
*/
void write_files(char *file_name, instructions_counter *ic, data_counter *dc, symbols_table *sym_table, symbols_table *entry_sym_table, symbols_table *external_sym_table)
{
	write_object_file(file_name, ic, dc);
	write_symbol_file(file_name, "ent", entry_sym_table);
	write_symbol_file(file_name, "ext", external_sym_table);
}

/*
** Write file_name.obj file using instruciton table and data table
*/
void write_object_file(char *file_name, instructions_counter *ic, data_counter *dc)
{
	FILE *obj_file = recreate_file(file_name, "obj");

	/* Writing header */
	fprintf(obj_file, "%d %d\n",ic->word_counter, dc->word_counter);
	int i;

	for (i = 0; i < ic->index; ++i)
	{
		command *current_command = ic->instructions[i];
		write_command(obj_file, current_command);
	}

	for (i = 0; i < dc->index; ++i)
	{
		instruction_line *current_instruction = dc->data[i];
		write_data(obj_file, current_instruction);
	}

	close_file(obj_file);
}

/*
** Write file_name.extension file using symbol table
*/
void write_symbol_file(char *file_name, char *extension, symbols_table *sym_table)
{
	FILE *sym_file = recreate_file(file_name, extension);

	int i;

	for (i = 0; i < sym_table->counter; ++i)
	{
		symbol *current_symbol = sym_table->symbols[i];
		write_symbol(sym_file, current_symbol);
	}

	close_file(sym_file);
}

/*
** Write a command line to the file
*/
void write_command(FILE *file, command *comm)
{
	// Write octal representation of the command
	int i;
	unsigned int command_content;
	command_content = 0;
	memcpy(&command_content,comm, WORD_LENGTH);
	fprintf(file, "%d %c\n",cast_decimal_to_octal(command_content), 'a');

	/* Write all data content */
	for (i = 0; i < comm->extra_word_count; ++i)
	{
		int extra_word = cast_decimal_to_octal(comm->extra_words[i]);
		char extra_word_type = comm->extra_words_type[i];
		fprintf(file, "%d %c\n", extra_word, extra_word_type);
	}
}

/*
** Write a data instruction line to the file
*/
void write_data(FILE *file, instruction_line *instruc)
{
	int i;
	int current_data;

	/* Write all data content */
	for (i = 0; i < instruc->content_length; ++i)
	{
		fprintf(file, "%d\n",cast_decimal_to_octal(instruc->content.data[i]));
	}
}

/*
** Write a symbol to the file
*/
void write_symbol(FILE *file, symbol *sym)
{
	fprintf(file, "%s %d\n",sym->name, sym->address);
}

/*
** Cast unsigned int to octal representation and write it as a line
*/
int cast_decimal_to_octal(unsigned int data)
{
	int digit, digit_count = 0, sum = 0;
	int octal = 0,decimal=0;

	// Get all digits in reverse
	while(data>0)
	{
	    digit = data%8;
	    sum = sum*10+digit;
	    data = data/8;
	    digit_count++;
	}

	// Reverse sum
	while(digit_count>0)
	{
	   digit=sum%10;
	   octal=octal*10+digit;
	   sum=sum/10;
	   digit_count--;
	}

	return octal;
}