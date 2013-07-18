#ifndef LINE_PARSER
#define LINE_PARSER value
#include "counter.h"

enum line_type get_line_type(char *line);

struct command_line get_command(char *line);

struct instruction_line get_instruction(char *line);

void set_command_data(struct command *comm, char *command_txt);

void set_command_arguments(struct command *comm,struct symbols_table *sym_table, char *first_argument, char *second_argument);

#endif
