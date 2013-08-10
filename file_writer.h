/*
** This file resposible on writing the compilation result
** for the input file
*/
#include "counter.h"
#include "structure.h"
#include "file_manager.h"
#include <math.h>
#include <stdio.h>

/*
** Write output files (Object file, Entry file, External file)
*/
void write_files(char *file_name, instructions_counter *ic, data_counter *dc, symbols_table *sym_table, symbols_table *entry_sym_table, symbols_table *external_sym_table);

/*
** Write file_name.obj file using instruciton table and data table
*/
void write_object_file(char *file_name, instructions_counter *ic, data_counter *dc);

/*
** Write file_name.extension file using symbol table
*/
void write_symbol_file(char *file_name, char *extension, symbols_table *sym_table);

/*
** Write a command line to the file
*/
void write_command(FILE *file, command *comm);

/*
** Write a data instruction line to the file
*/
void write_data(FILE *file, instruction_line *instruc);

/*
** Write a symbol to the file
*/
void write_symbol(FILE *file, symbol *sym);

/*
** Write an external symbol to the file
*/
void write_external(FILE *file, symbol *sym);

/*
** Cast int to octal representation and write it as a line
*/
int cast_decimal_to_octal(int data);

/*
** Print octal numbers with '0's before to complete 8 digits
*/
void print_octal(FILE *file, int octal);