#include "file_manager.h"

/*
** Delete and create file with name: file_name.extension
*/
FILE *recreate_file(char *file_name, char *extension)
{
	return fopen(file_name, "w");
}

/*
** Open file for reading
*/
FILE *open_file(char *file_name, char *extension)
{
	return fopen(file_name, "r");
}

/*
** Close file
*/
void close_file(FILE *file)
{
	fclose(file);
}