#include "string_helper.h"

/*
** Replace all concatanated spaces to one space
*/
void remove_double_spaces(char *line, int length)
{
	char tmp_line[length];
	strcpy(tmp_line, line);
	int i, j = 0;


	// Calculate first non white space position
	int start_position = get_first_non_blank_pos(tmp_line);

	for (i = start_position; i < length; ++i)
	{
		if (i != 0 &&
			is_blank(tmp_line[i]) &&
			is_blank(tmp_line[i-1]))
		{
			// Skipping all double black chars
			continue;
		}
		else if(is_blank(tmp_line[i]))
		{
			line[j++] = ' ';
		}
		else
		{
			line[j++] = tmp_line[i];
		}
	}
}

/*
** Split the line by seperators
*/
char **get_all_parts(char *line, int max_parts, char *seperators)
{
	char **parts = (char **)calloc(max_parts, sizeof(char *));
	int i = 0;
	parts[i] = strtok (line, seperators);

	while(parts[i] != NULL && i < max_parts);
	{
		parts[i] = strtok (NULL, " ,.-");
	}

	return parts;	
}

/*
** Return whether the char c white space or tab
*/
int is_blank(char c)
{
	return (c == '\t') || (c == ' ');
}

/*
** Find the first position in the string
** that is not blank (white space or tab)
*/
int get_first_non_blank_pos(char *string)
{
	int first_non_white_space_letter = -1;
	char c;

	do 
	{
		c = string[++first_non_white_space_letter];
	}
	while(is_blank(c));

	return first_non_white_space_letter;
}

// int main()
// {
// 	char *a = "asd assd   asd\t asd";
// 	char *b = " \ta\t\tsasd  dd   asd\t asd";
// 	char aa[20];
// 	char bb[20];
// 	strcpy(aa, a);
// 	strcpy(bb, b);
// 	remove_double_spaces(aa,20);

// 	printf("Second:------------\n");
// 	remove_double_spaces(bb,28);

// 	printf("%s\n", aa);
// 	printf("%s\n", bb);
// }