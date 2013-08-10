#include "file_parser.h"

instructions_counter *ic;
data_counter *dc;
data_counter *external_counter;
symbols_table *sym_table;
symbols_table *entry_sym_table;
symbols_table *external_sym_table;

/*
 ** Compile file
 */
void parse_file(char *file_name) {
	FILE *file;

	initialize();

	file = open_file(file_name, "ass");

	if (file == NULL) {
		printf("File not exists: %s.ass\n", file_name);
		return;
	}

	/* This round will parse line by line the file
	 ** and will build all table like that:
	 ** 	- command line : will parsed (symbols referece will be left out as names)
	 **					 and will be saved in 'ic' table
	 **  - data + string: will be parsed and saved in 'dc' table
	 **  - entry lines  : will be saved in entry_sym_table
	 **  - extern lines : will be saved in external_symbols table
	 */
	first_round(file);

	/* This round will fix the following:
	 **  - all symbols references in all 'ic' table rows
	 **  - all symbols references in external_sym_table
	 **  - all symbols references in entry_sym_table
	 */
	second_round();

	/* Write all files acourding to tables */
	write_files(file_name, ic, dc, sym_table, entry_sym_table,
			external_sym_table);

	close_file(file);
}

/*
 ** First time the parser is running all over the
 ** commands, and filling all necessary tables
 */
void first_round(FILE *file) {
	char *line = (char *) calloc(MAX_LINE_LENGTH, sizeof(char));
	while (next_line(file, line, MAX_LINE_LENGTH) != -1) {
		handle_line(line);
	}

	free(line);
}

/*
 ** Second time the parser is running all over the
 ** commands, and filling symbols holes
 */
void second_round() {
	/* This step will fix the following:
	 **  - all symbols references in all 'ic' table rows
	 **  - all symbols addresses in external_sym_table
	 */
	fix_symbol_references();

	/* This step will fix the following:
	 **  - all symbols addresses in entry_sym_table
	 */
	fix_entry_symbol_table();
}

/*
 ** Handle one line in the file
 */
void handle_line(char *line) {
	switch (get_line_type(line)) {
	case COMMAND:
		handle_command(line);
		break;
	case INSTRUCTION:
		handle_instruction(line);
		break;
	case COMMENT:
	case BLANK:
		/* Nothing to do here */
		break;
	default:
		printf("Unknow line type\n");
		exit(1);
		break;
	}
}

/*
 ** Handle a command line
 */
void handle_command(char *line) {
	/* Get the parsed command */
	command_line *comm_line = get_command_line(line);

	/* Compile the command (Symbols references are left with names) */
	command *comm = get_command(comm_line);

	/* If this line contains symbols
	 add them to sym_table */
	if (comm_line->label != NULL) {
		add_symbol(sym_table, comm_line->label, ic->word_counter, COMMAND_TABLE);
	}
	
	/* Add the instruction to the intruction counter */
	add_instruction(ic, comm);
}

/*
 ** Handle an instruction line
 */
void handle_instruction(char *line) {
	/* Get parsed instruction */
	instruction_line *inst_line = get_instruction_line(line);

	if (inst_line->command == DATA || inst_line->command == STRING) {
		/* If this line contains symbols
		 add them to sym_table */
		if (inst_line->label != NULL) {
			add_symbol(sym_table, inst_line->label, dc->word_counter, DATA_TABLE);
		}

		/* Add the instruction to the instruction counter */
		add_data(dc, inst_line);
	} else if (inst_line->command == EXTERN) {
		/* Add external instruction to the external couter */
		add_data(external_counter, inst_line);
	} else if (inst_line->command == ENTRY) {
		/* Add to entry symbols table with no address */
		add_symbol(entry_sym_table, inst_line->content.symbol_name, 0, ENTRY_TABLE);
	} else {
		printf("Unknow instruction type\n");
		exit(1);
	}
}

/*
 ** Runs over all commands and fill the correct symbol address
 ** + add all external references
 */
void fix_symbol_references() {
	int i;

	/* Run over all commands */
	for (i = 0; i < ic->index; ++i) {
		int j;
		command *current_command = ic->instructions[i];

		/* Run over all needed symbols */
		for (j = 0; j < current_command->extra_word_count; ++j) {
			if (current_command->extra_words_type[j] != 'a') {
				char *symbol_name = current_command->extra_words[j].label_name;

				/* Try find symbol in symbol table */
				int address = get_symbol_address(sym_table, symbol_name, ic->word_counter);

				/* If symbol was not found */
				if (current_command->extra_words_type[j] == 'd')
				{
					if(address == -1)
					{
						printf("Error!\n");
					}
					else
					{
						int last_address, current_address;
						assign_symbol_adderss(current_command, j, address);

						current_command->extra_words_type[j] = 'a';
						last_address = current_command->extra_words[j-1].number;
						current_address = current_command->extra_words[j].number;
						current_command->extra_words[j].number = current_address - last_address;
					}
				}
				else if (address == -1) {
					/* It's an external symbol reference */
					handle_external_reference(symbol_name, current_command->address + j + 1);
					current_command->extra_words_type[j] = 'e';
					current_command->extra_word_count = 1;
					current_command->extra_words[j].number = 0;
				} else {
					assign_symbol_adderss(current_command, j, address);
				}
			}
		}
	}
}

/*
 ** Runs over all entries symbol table and fill the correct symbol address
 */
void fix_entry_symbol_table() {
	int i;

	/* Run over all entry symbols */
	for (i = 0; i < entry_sym_table->counter; ++i) {
		symbol *entry_symbol = entry_sym_table->symbols[i];
		entry_symbol->address = get_symbol_address(sym_table,
				entry_symbol->name, ic->word_counter);
	}
}

/*
 ** Handle an external reference inside a command line
 */
void handle_external_reference(char *symbol_name, int line_address) {
	int i;

	/* Run over all entry symbols */
	for (i = 0; i < external_counter->index; ++i) {
		char *external_symbol = external_counter->data[i]->content.symbol_name;

		/* If symbol found in this external symbol */
		if (strncmp(symbol_name, external_symbol, MAX_SYMBOL_LENGTH) == 0) {
			/* Add symbol to the external symbols table */
			add_symbol(external_sym_table, symbol_name, line_address, EXTERNAL_TABLE);
			break;
		}
	}
}

/**
 ** Initialize all tables and counters
 */
void initialize() {
	ic = create_instruction_counter();
	dc = create_data_counter();
	external_counter = create_data_counter();
	sym_table = create_symbol_table();
	entry_sym_table = create_symbol_table();
	external_sym_table = create_symbol_table();
}
