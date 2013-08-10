#ifndef MEMORY
#define MEMORY value
#include <stddef.h>

/*
** Allocating new array of given count and size
** and validates not null
*/
void *calloc_with_validation(int count, size_t size);

/*
** Allocating new space in memory acourding to size
** and validates not null
*/
void *malloc_with_validation(size_t size);

#endif