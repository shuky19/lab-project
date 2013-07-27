/*
** This file resposible on managing files with io library
*/
#include <stdio.h>

/*
** Delete and create file with name: file_name.extension
*/
FILE *recreate_file(char *file_name, char *extension);

/*
** Open file for reading
*/
FILE *open_file(char *file_name, char *extension);

/*
** Close file
*/
void close_file(FILE *file);