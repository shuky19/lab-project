#include "string_helper.h"

/*
 ** Replace all concatanated spaces to one space
 */
void remove_double_spaces(char *line, int length) {
	int i, j = 0;
	char* tmp_line = (char*) calloc(length, sizeof(char));
	int start_position;
	strcpy(tmp_line, line);

	/* Calculate first non white space position */
	start_position = get_first_non_blank_pos(tmp_line);

	for (i = start_position; i < length; ++i) {
		if (i != 0 && is_blank(tmp_line[i]) && is_blank(tmp_line[i - 1])) {
			/* Skipping all double black chars */
			continue;
		} else if (is_blank(tmp_line[i])) {
			line[j++] = ' ';
		} else {
			line[j++] = tmp_line[i];
		}
	}

	free(tmp_line);
}

/*
 ** Split the line by separators
 */
char **get_all_parts(char *line, int max_parts, char *seperators) {
	char **parts;
	char* lineCopy, *temp;
	int i = 0, j;

	/* first we will copy the given line to keep it unchanged */
	lineCopy = (char*) calloc(strlen(line)+1, sizeof(char));
	strcpy(lineCopy, line);

	parts = calloc(max_parts, sizeof(char *));
	if (parts == NULL) {
		/* TODO: ERROR: Not ENOUGH MEMORY */
	}

	for (j = 0; j < max_parts; ++j) {
		parts[j] = calloc(MAX_LINE_LENGTH, sizeof(char));
		if (parts[j] == NULL) {
			/* TODO: ERROR: Not ENOUGH MEMORY */
			printf("ERROR");
			exit(-1);
		}
	}

	temp = strtok(lineCopy, seperators);
	if (temp != NULL)
		strcpy(parts[i], temp);

	while (temp != NULL && (++i) < max_parts) {
		temp = strtok(NULL, seperators);
		if (temp != NULL) {
			strcpy(parts[i], temp);
		}
	}

	return parts;
}

/*
 * Frees a double pointer of chars that was created by the function "get_all_parts"
 */
void free_line_parts(char** lineParts, int length) {
	int i;
	for (i = 0; i < length; i++) {
		free(lineParts[i]);
	}

	free(lineParts);
}

/*
 ** Return whether the char c white space or tab
 */
int is_blank(char c) {
	return (c == '\t') || (c == ' ');
}

/*
 ** Find the first position in the string
 ** that is not blank (white space or tab)
 */
int get_first_non_blank_pos(char *string) {
	int first_non_white_space_letter = -1;
	char c;

	do {
		c = string[++first_non_white_space_letter];
	} while (is_blank(c));

	return first_non_white_space_letter;
}

/*
 * Returns if a char is numeric
 */
int is_numeric(char *str)
{
	int i;

	for (i = 0; i < strlen(str); ++i)
	{
		if((i != 0 || str[i] != '-') && (str[i] < 48 || str[i] > 57))
		{
			return 0;
		}
	}

	return 1;
}
