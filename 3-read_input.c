#include "shell.h"
/**
 * my_strtok - that splits a string into tokens
 * @str: string input
 * @delimeter: string elements separator
 * Return: token
 */
char *my_strtok(char *str, char delimiter) 
{
	static char *current;

	if (!str) 
	{
		current = NULL;
		return NULL;
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
		return token;
	}

	*current = '\0';
	current++;

	return token;
}
/**
 * my_getline - Reads a line from stdin
 * @line: A pointer to the buffer
 * @buffer: A pointer to the size of the buffer.
 *Return: bytesRead
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
		} else {
			perror("Failed to read input");
			exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < bytesRead; ++i) 
	{
		if (in_comment && (*line)[i] == '\n') 
		{
			in_comment = false;
		} else if (!in_comment && (*line)[i] == '#') 
		{
			in_comment = true;
		}
	}
	remove_newline(*line);

	return bytesRead;
}
/**
 * print_tokens - Tokenizes a command and prints the tokens.
 * @command: The command string to tokenize.
 *Return: void
 */
void print_tokens(const char *command)
{
	char *argv[MAX_TOKENS];
	int argc = 0;

	char *token = strtok((char *)command, " ");
	while (token != NULL && argc < MAX_TOKENS - 1)
	{
		argv[argc] = malloc(strlen(token) + 1);
		if (argv[argc] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		copy_string(argv[argc++], token);
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;

	print_kide("Tokens: ");
	for (int i = 0; i < argc; ++i)
	{
		print_kide("%s ", argv[i]);
	}
	print_kide("\n");

	free_memory(argv);
}
/**
 * copy_string - copies characters from source to destination with a maximum length.
 * @dest: destination string.
 * @src: source string.
 * @max_len: maximum length of characters to copy.
 *Return: void
 */
void copy_string(char *dest, const char *src, size_t max_len) {
	if (!dest) 
	{
		return;
	}

	while (*src && max_len > 1) 
	{
		*dest++ = *src++;
		max_len--;
	}

	*dest = '\0';
}
/**
 * remove_newline - removes the newline character from the end of a string.
 * @str: input string.
 *Return: void
 */
void remove_newline(char *str) 
{
	size_t length = strlen(str);

	if (length > 0 && str[length - 1] == '\n') 
	{
		str[length - 1] = '\0';
	}
}

