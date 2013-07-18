#include "line_parser.h"

enum line_type get_line_type(char *line)
{
	return COMMAND;
}

struct command_line get_command(char *line)
{
	command_line cm = {};
	return cm;
}

struct instruction_line get_instruction(char *line)
{
	instruction_line il ={};
	return il;
}

void set_command_data(struct command *comm, char *command_txt)
{
}

void set_command_arguments(struct command *comm,struct symbols_table *sym_table, char *first_argument, char *second_argument)
{

}
