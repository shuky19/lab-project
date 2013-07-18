/*
** This helper file contians methods for parsing lines
*/

/*
** Replace all concatanated spaces to one space
*/
void remove_double_spaces(char *line);

/*
** Split the line by seperators and retrieve the part_number index
*/
char *get_line_part(char *line, char seperators[], int part_number);