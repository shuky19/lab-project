#include "memory_helper.h"

/*
** Allocating new array of given count and size
** and validates not null
*/
void *calloc_with_validation(int count, size_t size)
{
	void *result = calloc(count, size);

	if (result == NULL)
	{
		printf("Not enough memory, exiting...\n");
		exit(1);
	}
}

/*
** Allocating new space in memory acourding to size
** and validates not null
*/
void *malloc_with_validation(size_t size)
{
	void *result = malloc(size);

	if (result == NULL)
	{
		printf("Not enough memory, exiting...\n");
		exit(1);
	}
}