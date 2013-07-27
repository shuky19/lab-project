#include "line_parser.h"
#include <stdlib.h>

enum line_type get_line_type(char *line)
{
	return COMMAND;
}

struct command_line get_command(char *line)
{
	struct command_line cl;
	return cl;
}

struct instruction_line get_instruction(char *line)
{
	struct instruction_line il;
	return il;
}

void set_command_data(struct command *comm, char *command_txt)
{
}

void set_command_arguments(struct command *comm,struct symbols_table *sym_table, char *first_argument, char *second_argument)
{

}
