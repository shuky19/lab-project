/*
** This file responsible on parsing one line into 
** a command line or an instruction line
** and finally convert it to a command struct
*/

#ifndef LINE_PARSER
#define LINE_PARSER value
#include "counter.h"
#include "structure.h"

/*
** Return what kind of line represented by 
** the line parameter (COMMAND, INSTRUCTION, COMMENT, BLANK)
*/
enum line_type get_line_type(char *line);

/*
** Create a command line from the given string
*/
struct command_line get_command(char *line);

/*
** Create an instruction line from the given string
*/
struct instruction_line get_instruction(char *line);

/*
** Convert the command to binary code and
** save it into the given command struct
*/
void set_command_data(struct command *comm, char *command_txt);

/*
** Convert the arguments to binary code and
** save it into the given command struct
*/
void set_command_arguments(struct command *comm,struct symbols_table *sym_table, char *first_argument, char *second_argument);

#endif
