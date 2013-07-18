#ifndef STRUCTURE
#define STRUCTURE value
enum line_type { COMMAND, INSTRUCTION, COMMENT, BLANK };

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

struct command_line
{
	char *label;
	char *command;
	char *firstop;
	char *secondop;
};

struct instruction_line
{
	char *label;
	char *command;
	char *arguements[];
};


struct entry
{
	char *label;
};

struct command_line make_command_line(char *label, char *command, char *firstop, char *secondop);

struct instruction_line make_instruction_line(char *label, char *command, char *arguemtns[]);
#endif