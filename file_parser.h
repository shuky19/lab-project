#include "stdio.h"
// #include "counter.h"
#include "counter.c"
#include "stdlib.h"
/*
** Compile file
*/
void parse_file(char *filename);

/*
** Get next line in the file
*/
char *next_line(FILE *file);

void handle_line(char *line);

void handle_command(char *line);

void handle_instruction(char *line);