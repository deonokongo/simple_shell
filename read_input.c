#include "shell.h"
/**
 * read_line - reads the input string.
 *
 * @my_eof: return value of getline function
 * Return: input string
 */
char *read_line(int *my_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*my_eof = getline(&input, &bufsize, stdin);

	return (input);
}
