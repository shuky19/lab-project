/*
** This helper file contains methods for parsing lines
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory_helper.h"

#define MAX_LINE_LENGTH 200
#define MAX_PARTS_IN_LINE 30

/*
** Replace all concatenated spaces to one space
*/
void remove_double_spaces(char *line, int length);

/*
** Split the line by separators
*/
char **get_all_parts(char *line, int max_parts, char *seperators);

/*
** Find the first position in the string
** that is not blank (white space or tab)
*/
int get_first_non_blank_pos(char *string);

/*
** Return whether the char c white space or tab
*/
int is_blank(char c);

/*
 * Frees a double pointer of chars that was created by the function "get_all_parts"
 */
void free_line_parts(char** lineParts, int length);

/*
 * Returns if a char is numeric
 */
int is_numeric(char *str);

/*
 * checks if a given word is a label.
 */
int is_label(char* word);
