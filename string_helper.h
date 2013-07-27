/*
** This helper file contians methods for parsing lines
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Replace all concatanated spaces to one space
*/
void remove_double_spaces(char *line, int length);

/*
** Split the line by seperators
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