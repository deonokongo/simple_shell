#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
/**
 * my_strtok - Splits a string into tokens based on a delimiter.
 * @str: The input string.
 * @delimiter: The delimiter used for tokenization.
 * Return: A pointer to the next token
 */
char *my_strtok(char *str, char delimiter)
{
	static char *current;
	char *start = current;

	if (str != NULL)
	{
		current = str;
	}

	if (current == NULL || *current == '\0')
	{
		return (NULL);
	}
	while (*current != '\0' && *current != delimiter)
	{
		current++;
	}

	if (*current == delimiter)
	{
		*current = '\0';
		current++;
	}

	return (start);
}

