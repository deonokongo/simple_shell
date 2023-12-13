#include "shell.h"
#include <stdbool.h>
/**
 * my_strtok - Splits a string into tokens based on a delimiter.
 * @str: The input string.
 * @delimiter: The delimiter used for tokenization.
 * Return: A pointer to the next token, or NULL if no more tokens are available.
 */
char *my_strtok(char *str, char delimiter)
{
	static char *current;

	if (str != NULL)
	{
		current = str;
	}

	if (current == NULL || *current == '\0')
	{
		return (NULL);
	}

	char *start = current;

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

/**
 * my_getline - Read a line from standard input.
 * @line: A pointer to a pointer to the line.
 * @buffer: A pointer to the size of the buffer.
 * Return: The number of bytes read.
 */
int my_getline(char **line, size_t *buffer)
{
	bool in_comment = false;

	ssize_t bytesRead = getline(line, buffer, stdin);

	if (bytesRead == -1)
	{
		if (feof(stdin))
		{
			print_kide("\n");
		}
		else
		{
			perror("Failed to read input");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < bytesRead; ++i)
	{
		if (in_comment && (*line)[i] == '\n')
		{
			in_comment = false;
		}
		else if (!in_comment && (*line)[i] == '#')
		{
			in_comment = true;
		}
	}

	remove_newline(*line);

	return (bytesRead);
}

