#include "line_parser.h"
#include "string_helper.h"

line_type get_line_type(char *line)
{
	int firstNonBlankPos = get_first_non_blank_pos(line);
	char firstNonBlankChar = line[firstNonBlankPos];
	char** lineParts;

	/*find the line type by its first char */
	switch (firstNonBlankChar)
	{
	case '\0':
		return BLANK;
	case ';':
		return COMMENT;
	case '.':
		return INSTRUCTION;
	}

	/*if we haven't returned yet, it means the first word in the line is a label or a command,
	 so we will get the first two words and check them. */
	lineParts = get_all_parts(line, 2, " \t");

	/*If the last char in the first word is a colon, it means we have to return the type
	 by the second word's first char. If it doesn't a colon, then the line type is a command.*/
	if (is_label(lineParts[0]))
	{
		if (lineParts[1][0] == '.')
		{
			free_line_parts(lineParts, 2);
			return INSTRUCTION;
		}
	}

	free_line_parts(lineParts, 2);
	return COMMAND;
}

/*
 ** Create a command line from the given string
 */
command_line *get_command_line(char *line)
{
	command_line *cl = (command_line *) malloc_with_validation(sizeof(command_line));
	/*we will try to get 5 parts: label (if exists), the command, the dbl, the first operand
	 * and the second operand.*/
	char** lineParts = get_all_parts(line, 5, ", \t");
	int commandIndex = 0, labelLength;

	/* set the label (if exists) */
	if (is_label(lineParts[0]))
	{
		labelLength = strlen(lineParts[0]);
		cl->label = (char*) calloc_with_validation(labelLength, sizeof(char));
		strncpy(cl->label, lineParts[0], labelLength - 1);
		cl->label[labelLength - 1] = '\0';
		commandIndex = 1;
	}
	else
	{
		cl->label = NULL;
	}

	/* set the command */
	cl->command = (char*) calloc_with_validation(strlen(lineParts[commandIndex]) + 1, sizeof(char));
	strcpy(cl->command, lineParts[commandIndex]);

	/* set the dbl */
	if (strcmp("0", lineParts[commandIndex + 1]) == 0)
	{
		cl->dbl = 0;
	}
	else
	{
		cl->dbl = 1;
	}

	/* If there is only one operand - we fill the secondOp and leave the firstOp null. If there
	 *  are two operands, we fill both the first and the second operand. */
	if (strlen(lineParts[commandIndex+3]))
	{
		cl->firstop = (char*) calloc_with_validation(strlen(lineParts[commandIndex + 2]) + 1, sizeof(char));
		strcpy(cl->firstop, lineParts[commandIndex + 2]);
		cl->secondop = (char*) calloc_with_validation(strlen(lineParts[commandIndex + 3]) + 1, sizeof(char));
		strcpy(cl->secondop, lineParts[commandIndex + 3]);
	}
	else
	{
		cl->firstop = NULL;
		cl->secondop = (char*) calloc_with_validation(strlen(lineParts[commandIndex + 2]) + 1, sizeof(char));
		strcpy(cl->secondop, lineParts[commandIndex + 2]);
	}

	free_line_parts(lineParts, 5);
	return cl;
}

/*
 ** Create an instruction line from the given string
 */
instruction_line *get_instruction_line(char *line, int *is_error)
{
	instruction_line* il = (instruction_line*)malloc_with_validation(sizeof(instruction_line));
	/* we try to get at most 20 parts - there might be a lot of arguments if its a
	 * data instruction. */
	char** lineParts = get_all_parts(line, 20, ", \t");
	int instructionIndex = 0, labelLength;

	/* set the label (if exists) */
	if (is_label(lineParts[0]))
	{
		labelLength = strlen(lineParts[0]);
		il->label = (char*) calloc_with_validation(labelLength, sizeof(char));
		strncpy(il->label, lineParts[0], labelLength - 1);
		il->label[labelLength - 1] = '\0';
		instructionIndex = 1;
	}
	else
	{
		il->label = NULL;
	}

	/* set the instruction */
	if (strcmp(lineParts[instructionIndex], ".data") == 0)
	{
		il->command = DATA;
		fill_data_instruction(il, lineParts, instructionIndex + 1);
	}
	else if (strcmp(lineParts[instructionIndex], ".string") == 0)
	{
		il->command = STRING;
		fill_string_instruction(il, lineParts, instructionIndex + 1);
	}
	else if (strcmp(lineParts[instructionIndex], ".entry") == 0)
	{
		il->command = ENTRY;
		fill_extern_entry_instruction(il, lineParts, instructionIndex + 1);
	}
	else if (strcmp(lineParts[instructionIndex], ".extern") == 0)
	{
		il->command = EXTERN;
		fill_extern_entry_instruction(il, lineParts, instructionIndex + 1);
	}
	else
	{
		print_error(is_error, "Unknown instruction type");
	}

	free_line_parts(lineParts, 20);
	return il;
}

/*
 * Fills a data instruction
 */
void fill_data_instruction(instruction_line *line, char** lineParts, int firstDataIndex)
{
	int lastDataIndex = firstDataIndex;
	int i;
	/*first we will calculate the number of parts in the data array */
	while (lineParts[(++lastDataIndex)] != NULL && strlen(lineParts[lastDataIndex]) > 0)
	{
	}

	/* then we will set the values from the given string to the struct we build */
	line->content.data = (int*) calloc_with_validation((lastDataIndex - firstDataIndex), sizeof(int));
	for (i = firstDataIndex; i < lastDataIndex; ++i)
	{
		sscanf(lineParts[i], "%d", &(line->content.data[i - firstDataIndex]));
	}
	line->content_length = lastDataIndex - firstDataIndex;
}

/*
 * Fills a string instruction
 */
void fill_string_instruction(instruction_line *line, char** lineParts, int firstDataIndex)
{
	int i;
	/* we subtract 1 from the length of the word because there are two additional quotation marks we
	 * don't need, but we add a 0  char to	mark the end of the string */
	int dataLength = strlen(lineParts[firstDataIndex]) - 1;
	line->content.data = (int*) calloc_with_validation(dataLength, sizeof(int));
	for (i = 1; i < dataLength; ++i)
	{
		line->content.data[i - 1] = lineParts[firstDataIndex][i];
	}
	line->content.data[dataLength - 1] = '\0';
	line->content_length = dataLength;
}

/*
 * Fills an entry or an extern instruction
 */
void fill_extern_entry_instruction(instruction_line *line, char** lineParts, int firstDataIndex)
{
	int dataLength = strlen(lineParts[firstDataIndex]) + 1;
	line->content.symbol_name = (char*) calloc_with_validation(dataLength, sizeof(char));
	strcpy(line->content.symbol_name, lineParts[firstDataIndex]);
	line->content_length = dataLength;
}

/*
 ** Create a command from the given command_line
 */
command *get_command(command_line *comm_line, int *is_error)
{
	int miun, reg;
	command *comm = (command *) calloc_with_validation(1, sizeof(command));

	comm->extra_word_count = 0;

	fill_opcpde(comm_line->command, comm, is_error);
	fill_type_comb(comm_line->command, comm, is_error);
	comm->dbl = comm_line->dbl;

	fill_operand(comm_line->firstop, comm, &miun, &reg);
	comm->source_miun = miun;
	comm->source_reg = reg;
	verify_source_operand(comm_line->firstop, comm, is_error);

	fill_operand(comm_line->secondop, comm, &miun, &reg);
	comm->dest_miun = miun;
	comm->dest_reg = reg;
	verify_dest_operand(comm_line->secondop, comm, is_error);

	return comm;
}

/*
 * Fills the type bit and the comb bits by the command string.
 */
void fill_type_comb(char* commandString, command* comm, int *is_error)
{
	/* we will get the parts in the command, separated by the char '/'. The maximum number
	 *  of parts will be 4. */
	char** commandParts = get_all_parts(commandString, 4, "/");
	int comb = 0;

	/* set the type bit. If it is 0, then the comb has to be 0 as well. */
	if (commandParts[1][0] == '0')
	{
		comm->type = 0;
	}
	else if (commandParts[1][0] == '1')
	{
		/* If the type bit is 1, we have to set the comb bits too */
		comm->type = 1;

		comb = (commandParts[2][0] == '1') << 1;
		comb += commandParts[3][0] == '1';
	}
	else
	{
		print_error(is_error, "Unknown command type (neither 0 nor 1)");
	}


	comm->comb = comb;
	free_line_parts(commandParts, 4);
}

/*
 * Fills the op code bits by the command string
 */
void fill_opcpde(char* commandString, command* comm, int *is_error)
{
	/* we will get the first part only, which will be the command. */
	char** commandParts = get_all_parts(commandString, 1, "/");
	char* commandName = commandParts[0];

	/* set the command */
	if (strcmp(commandName, "mov") == 0)
	{
		comm->opcode = MOV;
	}
	else if (strcmp(commandName, "cmp") == 0)
	{
		comm->opcode = CMP;
	}
	else if (strcmp(commandName, "add") == 0)
	{
		comm->opcode = ADD;
	}
	else if (strcmp(commandName, "sub") == 0)
	{
		comm->opcode = SUB;
	}
	else if (strcmp(commandName, "not") == 0)
	{
		comm->opcode = NOT;
	}
	else if (strcmp(commandName, "clr") == 0)
	{
		comm->opcode = CLR;
	}
	else if (strcmp(commandName, "lea") == 0)
	{
		comm->opcode = LEA;
	}
	else if (strcmp(commandName, "inc") == 0)
	{
		comm->opcode = INC;
	}
	else if (strcmp(commandName, "dec") == 0)
	{
		comm->opcode = DEC;
	}
	else if (strcmp(commandName, "jmp") == 0)
	{
		comm->opcode = JMP;
	}
	else if (strcmp(commandName, "bne") == 0)
	{
		comm->opcode = BNE;
	}
	else if (strcmp(commandName, "red") == 0)
	{
		comm->opcode = RED;
	}
	else if (strcmp(commandName, "prn") == 0)
	{
		comm->opcode = PRN;
	}
	else if (strcmp(commandName, "jsr") == 0)
	{
		comm->opcode = JSR;
	}
	else if (strcmp(commandName, "rts") == 0)
	{
		comm->opcode = RTS;
	}
	else if (strcmp(commandName, "stop") == 0)
	{
		comm->opcode = STOP;
	}
	else
	{
		print_error(is_error, "Unknown command");
	}

	free_line_parts(commandParts, 1);
}

/*
 * Fills an operand and its miun type
 */
void fill_operand(char* operandString, command* comm, int* miun, int* reg)
{
	int reg_num;
	char *miun_index_meguvan, *operandStringCopy;

	/* we don't have to do nothing if the operand is null or if its length is zero */
	if (operandString == NULL || strlen(operandString) == 0)
	{
		*miun = 0;
		*reg = 0;
		return;
	}

	operandStringCopy = (char*) calloc_with_validation(strlen(operandString) + 1, sizeof(char));
	strcpy(operandStringCopy, operandString);

	*reg = 0;
	/* if the first char is #, it means it's a Miun-Miadi. */
	if (operandStringCopy[0] == '#')
	{
		fill_miun_miadi(operandStringCopy, comm, miun);
	}
	else
	{
		miun_index_meguvan = strchr(operandStringCopy, '{');
		/* if the char { exists in the operand, it's a Miun-Index-Meguvan. */
		if (miun_index_meguvan != NULL)
		{
			fill_miun_index_meguvan(operandStringCopy, comm, miun, reg);
		}
		else
		{
			reg_num = get_reg_num(operandStringCopy);
			if (reg_num != -1)
			{
				/* we found a register number, so it's a Miun-Oger-Yashir. */
				*miun = 3;
				*reg = reg_num;
			}
			else
			{
				/* if we got to this line, it means it's a Miun-Yashir. */
				fill_miun_yashir(operandStringCopy, comm, miun);
			}
		}
	}

	free(operandStringCopy);
}

/*
 * fills an operand that uses mium miadi
 */
void fill_miun_miadi(char* operandString, command* comm, int* miun)
{
	int extra_word_count = comm->extra_word_count++;
	*miun = 0;
	sscanf((operandString + 1), "%d", &comm->extra_words[extra_word_count].number);
	comm->extra_words_type[extra_word_count] = 'a';
}

/*
 * fills an operand that uses miun yashir
 */
void fill_miun_yashir(char* operandString, command* comm, int* miun)
{
	int labelLength;
	int extra_word_count = comm->extra_word_count++;
	*miun = 1;
	labelLength = strlen(operandString) + 1;
	comm->extra_words[extra_word_count].label_name = (char*) calloc_with_validation(labelLength, sizeof(char));
	strcpy(comm->extra_words[extra_word_count].label_name, operandString);
	comm->extra_words_type[extra_word_count] = 'r';
}

/*
 * fills an operand that uses miun-index-meguvan
 */
void fill_miun_index_meguvan(char* operandString, command* comm, int* miun, int* reg)
{
	char* label;
	int labelLength, reg_num, constant;
	int extra_word_count = comm->extra_word_count++;
	*miun = 2;

	/* set the first extra word (which is a label name) */
	label = strtok(operandString, "{}*");
	labelLength = strlen(label) + 1;
	comm->extra_words[extra_word_count].label_name = (char*) calloc_with_validation(labelLength, sizeof(char));
	strcpy(comm->extra_words[extra_word_count].label_name, label);
	comm->extra_words[extra_word_count].label_name[labelLength - 1] = '\0';
	comm->extra_words_type[extra_word_count] = 'r';

	/* set the second extra word (which might be a register, a label or a number) */
	label = strtok(NULL, "{}*");
	reg_num = get_reg_num(label);
	/* if we found a register - then the second extra word is a register */
	if (reg_num != -1)
	{
		*reg = reg_num;
	}
	/* check if label represents a number */
	else if (is_numeric(label))
	{
		sscanf(label, "%d", &constant);
		/* if we got to this line, it means the second word is a number */
		extra_word_count = comm->extra_word_count++;
		comm->extra_words[extra_word_count].number = constant;
		comm->extra_words_type[extra_word_count] = 'a';
	}
	else  /* it means the second word is a label */
	{
		extra_word_count = comm->extra_word_count++;
		labelLength = strlen(label) + 1;
		comm->extra_words[extra_word_count].label_name = (char*) calloc_with_validation(labelLength, sizeof(char));
		strcpy(comm->extra_words[extra_word_count].label_name, label);
		comm->extra_words[extra_word_count].label_name[labelLength - 1] = '\0';
		comm->extra_words_type[extra_word_count] = 'd';
	}
}

/*
 * Gets a register number out of a string, or returns -1 if the strings doesn't represent any register
 */
int get_reg_num(char* reg)
{
	if (strcmp(reg, "r0") == 0)
		return 0;
	else if (strcmp(reg, "r1") == 0)
		return 1;
	else if (strcmp(reg, "r2") == 0)
		return 2;
	else if (strcmp(reg, "r3") == 0)
		return 3;
	else if (strcmp(reg, "r4") == 0)
		return 4;
	else if (strcmp(reg, "r5") == 0)
		return 5;
	else if (strcmp(reg, "r6") == 0)
		return 6;
	else if (strcmp(reg, "r7") == 0)
		return 7;
	else if (strcmp(reg, "pc") == 0)
		return 8;
	else if (strcmp(reg, "sp") == 0)
		return 9;
	else if (strcmp(reg, "psw") == 0)
		return 10;
	else
		return -1;

}

/*
 * Verifies there is no error in the source operand
 */
void verify_source_operand(char* operandString, command *comm, int *is_error)
{
	int operandDoesntExist = operandString == NULL || strlen(operandString) == 0;
	switch (comm->opcode)
	{
	case MOV:
	case CMP:
	case ADD:
	case SUB:
		if (operandDoesntExist)
		{
			print_error(is_error, "Wrong number of operands");
		}
		break;
	case LEA:
		if (operandDoesntExist)
		{
			print_error(is_error, "Wrong number of operands");
		}

		else if (comm->source_miun == 0)
		{
			print_error(is_error, "The miun type doesn't can't be used with the command");
		}
		break;
	case NOT:
	case CLR:
	case INC:
	case DEC:
	case JMP:
	case BNE:
	case RED:
	case PRN:
	case JSR:
	case RTS:
	case STOP:
		if (operandDoesntExist != 1)
		{
			print_error(is_error, "Wrong number of operands");
		}
		break;
	}
}

/*
 * Verifies there is no error in the destination operand
 */
void verify_dest_operand(char* operandString, command *comm, int *is_error)
{
	int operandDoesntExist = operandString == NULL || strlen(operandString) == 0;
	switch (comm->opcode)
	{
		case MOV:
		case ADD:
		case SUB:
		case NOT:
		case LEA:
		case INC:
		case DEC:
		case JMP:
		case BNE:
		case RED:
			if (operandDoesntExist)
			{
				print_error(is_error, "Wrong number of operands");
			}
			else if (comm->dest_miun == 0)
			{
				print_error(is_error, "The miun type doesn't can't be used with the command");
			}
			break;
		case CMP:
		case PRN:
			if (operandDoesntExist)
			{
				print_error(is_error, "Wrong number of operands");
			}
			break;
		case JSR:
			if (operandDoesntExist)
			{
				print_error(is_error, "Wrong number of operands");
			}
			else if (comm->dest_miun != 1)
			{
				print_error(is_error, "The miun type doesn't can't be used with the command");
			}
			break;
		case RTS:
		case STOP:
			if (operandDoesntExist != 1)
			{
				print_error(is_error, "Wrong number of operands");
			}
			break;
	}
}

/*
 ** Assign symbol address to the command
 */
void assign_symbol_adderss(command *comm, int symbol_index, int symbol_address)
{
	free(comm->extra_words[symbol_index].label_name);
	comm->extra_words[symbol_index].number = symbol_address;
}

/*
 * prints an error and sets the is_error flag to true
 */
void print_error(int *is_error, const char* error_msg)
{
	/* print the error message */
	printf("Error: %s.\n", error_msg);
	/* set the error to be true */
	(*is_error) = 1;
}

/*
 ** Get next line in the file
 */
int next_line(FILE *file, char *buffer, size_t len)
{
	char c;
	int i;

	memset(buffer, 0, len);

	for (i = 0; i < len; i++)
	{
		c = fgetc(file);

		if (!feof(file))
		{
			if (c == '\r')
			{
				buffer[i] = 0;
			}
			else if (c == '\n')
			{
				buffer[i] = 0;
				return i + 1;
			}
			else
			{
				buffer[i] = c;
			}
		}
		else
		{
			return -1;
		}
	}

	return -1;
}
