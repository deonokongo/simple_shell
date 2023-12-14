#include "shell.h"

/**
 * my_memset - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @byte: the byte to fill *ptr with
 * @count: the amount of bytes to be filled
 * Return: (ptr) a pointer to the memory area ptr
 */
char *my_memset(char *ptr, char byte, unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++)
		ptr[i] = byte;
	return ptr;
}

/**
 * my_free - frees a string of strings
 * @pp: string of strings
 */
void my_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * my_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to da ol' block nameen.
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return ptr;

	p = malloc(new_size);
	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return p;
}

