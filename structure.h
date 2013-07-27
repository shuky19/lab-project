/*
** This file declare all needed types for the compiler
** and helper methods for building them
*/

#ifndef STRUCTURE
#define STRUCTURE value

/*
** Represnt a type of line in the source file
** COMMAND - regular line with command and arguments
** INSTRUCTION - compiler instruction line
** COMMENT - comment line
** BLANK - empty line (only with white characters)
*/
enum line_type { COMMAND, INSTRUCTION, COMMENT, BLANK };

/*
** Binary representation a compiled line
*/
struct command
{
	unsigned int comb : 2;
	unsigned int dest_reg : 3;
	unsigned int dest_add : 2;
	unsigned int source_reg : 2;
	unsigned int source_add : 2;
	unsigned int opcode : 3;
	unsigned int type : 1;
	unsigned int dbl : 1;
	unsigned int : 2;
};

/*
** Structural representation of command type line
*/
struct command_line
{
	char *label;
	char *command;
	char *firstop;
	char *secondop;
};

/*
** Structural representation of instruction type line
*/
struct instruction_line
{
	char *label;
	char *command;
	char *arguements[3];
};

/*
** Structural representation of entry type line
*/
struct entry
{
	char *label;
};

/*
** Create command line from the given arguments
*/
struct command_line make_command_line(char *label, char *command, char *firstop, char *secondop);

/*
** Create instruction line from the given arguments
*/
struct instruction_line make_instruction_line(char *label, char *command, char *arguemtns[]);

#endif