/*
** This file responsible on parsing one line into 
** a command line or an instruction line
** and finally convert it to a command struct
*/

#ifndef LINE_PARSER
#define LINE_PARSER value
#include "counter.h"
#include "structure.h"
#include <stdio.h>
#define MAX_LINE_LENGTH 80

/*
** Get next line in the file
*/
int next_line(FILE *file, char *buffer, size_t len);

/*
** Return what kind of line represented by 
** the line parameter (COMMAND, INSTRUCTION, COMMENT, BLANK)
*/
line_type get_line_type(char *line);

/*
** Create a command line from the given string
*/
command_line *get_command_line(char *line);

/*
** Create an instruction line from the given string
*/
instruction_line get_instruction_line(char *line);

/*
** Create a command from the given command_line
*/
command *get_command(command_line *comm_line);

/*
** Assign symbol address to the command
*/
void assign_symbol_adderss(command *comm, int symbol_index, int symbol_address);

#endif
