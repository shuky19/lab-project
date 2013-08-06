#include "file_manager.h"

/*
** Delete and create file with name: file_name.extension
*/
FILE *recreate_file(char *file_name, char *extension)
{
	char full_name[strlen(file_name) + strlen(extension)+1];
	get_full_file_name(full_name, file_name, extension);
	FILE *file = fopen(full_name, "w");
	return file;
}

/*
** Open file for reading
*/
FILE *open_file(char *file_name, char *extension)
{
	char full_name[strlen(file_name) + strlen(extension)+1];
	get_full_file_name(full_name, file_name, extension);
	FILE *file = fopen(full_name, "r");
	return file;
}

/*
** Close file
*/
void close_file(FILE *file)
{
	fclose(file);
}

/*
** Concate file_name with extenstion into dest
*/
void get_full_file_name(char *dest, char *file_name, char *extension)
{
	strcpy(dest, file_name);
	strcat(dest, ".");
	strcat(dest, extension);
}