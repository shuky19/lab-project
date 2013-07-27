#include "file_parser.h"

struct instructions_counter *ic;
struct data_counter *dc;
struct symbols_table *sym_table;

/*
** Compile file
*/
void parse_file(char *filename)
{
	/* Initialize all variables */
	char *line;
	FILE *file;

	while((line = next_line(file)) != NULL)
	{
		handle_line(line);
		free(line);
	}
}

/*
** Get next line in the file
*/
char *next_line(FILE *file)
{

}

void handle_line(char *line)
{
	switch (get_line_type(line))
	{
		case COMMAND:
			handle_command(line);
			break;
		case INSTRUCTION:
			handle_instruction(line);
			break;
		case COMMENT:
		case BLANK:
			/* Nothing to do here */
			break;
		default:
			printf("Unknow line type\n");
			exit(1);
			break;
	}
}


void handle_command(char *line)
{
	struct command comm;
	struct command_line comm_line = get_command(line);
	set_command_data(&comm, comm_line.command);

	set_command_arguments(&comm, sym_table, comm_line.firstop, comm_line.secondop);

	// If this line contains symbols
	// add them to sym_table
	if (comm_line.label != NULL)
	{
		add_symbol(sym_table, comm_line.label, ic->counter);
	}

	// Add command to the instructions table
	ic->instructions[ic->counter++] = comm;
}

void handle_instruction(char *line)
{

}