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
#include "string_helper.h"

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

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
instruction_line *get_instruction_line(char *line);

/*
 ** Create a command from the given command_line
 */
command *get_command(command_line *comm_line);

/*
 * checks if a given word is a label.
 */
int is_label(char* word);

/*
 * Fills the type bit and the comb bits by the command string.
 */
void fill_type_comb(char* commandString, command* comm);

/*
 * Fills the op code bits by the command string
 */
void fill_opcpde(char* commandString, command* comm);

/*
 * Fills a data instruction
 */
void fill_data_instruction(instruction_line *line, char** lineParts, int firstDataIndex);

/*
 * Fills an entry or an extern instruction
 */
void fill_extern_entry_instruction(instruction_line *line, char** lineParts, int firstDataIndex);

/*
 * Fills a string instruction
 */
void fill_string_instruction(instruction_line *line, char** lineParts, int firstDataIndex);

/*
 ** Assign symbol address to the command
 */
void assign_symbol_adderss(command *comm, int symbol_index, int symbol_address);

/*
 * Fills an operand and its miun type
 */
void fill_operand(char* operandString, command* comm, int* miun, int* reg);

/*
 * fills an operand that uses mium miadi
 */
void fill_miun_miadi(char* operandString, command* comm, int* miun);

/*
 * fills an operand that uses miun yashir
 */
void fill_miun_yashir(char* operandString, command* comm, int* miun);

/*
 * fills an operand that uses miun-index-meguvan
 */
void fill_miun_index_meguvan(char* operandString, command* comm, int* miun, int* reg);

/*
 * Gets a register number out of a string, or returns -1 if the strings doesn't represent any register
 */
int get_reg_num(char* reg);

/*
 * Verifies there is no error in the source operand
 */
void verify_source_operand(char* operandString, command *comm);

/*
 * Verifies there is no error in the destination operand
 */
void verify_dest_operand(char* operandString, command *comm);
#endif
