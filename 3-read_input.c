#include "shell.h"
/**
 * my_strtok - that splits a string into tokens
 *
 * @str: string input
 * @delimiter: separator
 *
 * Return: token
 */
char *my_strtok(char *str, char delimiter)
{
	static char *current;

	if (!str)
	{
		current = NULL;
		return (NULL);
	}

	if (!current)
	{
		current = str;
	}
	char *token = current;

	while (*current != delimiter && *current != '\0')
	{
		current++;
	}
	if (*current == '\0')
	{
		current = NULL;
		return (token);
	}
	*current = '\0';
	current++;

	return (token);
}
/**
 * my_getline - Reads a line from stdin
 * @line: A pointer to the buffer
 * @buffer: A pointer to the size of the buffer.
 * Return: bytesRead
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
