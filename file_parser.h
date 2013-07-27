/*
** This file resposible on managing file compilation
** line by line
*/
#include <stdio.h>
#include "counter.h"
#include "structure.h"
#include "line_parser.h"
#include <stdlib.h>

/*
** Compile file
*/
void parse_file(char *filename);

/*
** Get next line in the file
*/
char *next_line(FILE *file);

/*
** Handle one line in the file
*/
void handle_line(char *line);

/*
** Handle a command line
*/
void handle_command(char *line);

/*
** Handle an instruction line
*/
void handle_instruction(char *line);