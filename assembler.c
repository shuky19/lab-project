#include "assembler.h"

/*
** Start point of the assembler
** recieve as input files to compile
*/
int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; ++i)
	{
		parse_file(argv[i]);
	}

	return 1;
}
