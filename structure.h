/*
 ** This file declare all needed types for the compiler
 ** and helper methods for building them
 */

#ifndef STRUCTURE
#define STRUCTURE value
#define WORD_LENGTH 3

/*
 ** Represnt a type of line in the source file
 ** COMMAND - regular line with command and arguments
 ** INSTRUCTION - compiler instruction line
 ** COMMENT - comment line
 ** BLANK - empty line (only with white characters)
 */
typedef enum
{
	COMMAND, INSTRUCTION, COMMENT, BLANK
} line_type;

/*
 ** Structural representation of an extra word in a command
 ** for label: use label_name
 ** for a constant number: use number
 */
typedef union
{
	int number;
	char *label_name;
} command_extra_words;

/*
 ** Binary representation a compiled line
 */
typedef struct
{
	unsigned comb :2;
	unsigned dest_reg :3;
	unsigned dest_miun :2;
	unsigned source_reg :3;
	unsigned source_miun :2;
	unsigned opcode :4;
	unsigned type :1;
	unsigned dbl :1;
	unsigned :4;
	unsigned char extra_words_type[4]; /* Represent words type ('a', 'r', 'e') */
	command_extra_words extra_words[4];
	int extra_word_count;
	unsigned error :1;
	int address; /* Represent the starting address of this command */
} command;

typedef command *command_ptr;

/*
 ** Structural representation of command type line
 */
typedef struct
{
	char *label;
	char *command;
	int dbl;
	char *firstop;
	char *secondop;
} command_line;

/*
 ** Structural representation of instruction content
 ** for entry: use symbol_name
 ** for extern: use symbol_name
 ** for data: use data
 ** for string: use strings
 */
typedef union
{
	int *data;
	char *symbol_name;
} instruction_content;

/*
 ** Represnt a type of instruction line in the source file
 ** ENTRY - .entry line
 ** EXTERN - .extern line
 ** DATA - .data line
 ** STRING - .string line
 */
typedef enum
{
	ENTRY, EXTERN, DATA, STRING
} instruction_line_type;

/*
 ** Structural representation of instruction type line
 */
typedef struct
{
	char *label;
	instruction_line_type command;
	instruction_content content;
	int content_length;
} instruction_line;

typedef instruction_line *instruction_line_ptr;

/*
 ** Create command line from the given arguments
 */
command_line make_command_line(char *label, char *command, char *firstop, char *secondop);

/*
 ** Create instruction line from the given arguments
 */
instruction_line make_instruction_line(char *label, char *command, char *arguemtns[]);
#endif
