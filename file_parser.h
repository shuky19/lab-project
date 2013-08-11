/*
** This file resposible on managing file compilation
** line by line
*/
#include "counter.h"
#include "structure.h"
#include "memory_helper.h"
#include "line_parser.h"
#include "file_writer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_EXTRIES_IN_FILE 80

/*
** Compile file
*/
void parse_file(char *file_name);

/*
** First time the parser is running all over the 
** commands, and filling all necessary tables
*/
void first_round(FILE *file);

/*
** Second time the parser is running all over the 
** commands, and filling symbols holes
*/
void second_round();

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

/*
** Runs over all commands and fill the correct symbol address
** + add all external references
*/
void fix_symbol_references();

/*
** Runs over all entries symbol table and fill the correct symbol address
*/
void fix_entry_symbol_table();

/*
** Handle an external reference inside a command line
*/
void handle_external_reference(char *symbol_name, int line_address);

/**
** Initialize all tables and counters
*/
void initialize();

/*
** Free all counter that was used in parsing process
*/
void free_counters();

/*
** Check that there is no double labels
*/
void check_double_labels();