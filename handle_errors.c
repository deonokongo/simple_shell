#include "shell.h"

/**
 * print_input - prints an input string
 * @input_str: the string to be printed
 *
 * Return: Nothing
 */
void print_input(char *input_str)
{
	int i = 0;

	if (!input_str)
		return;
	while (input_str[i] != '\0')
	{
		_eputchar(input_str[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character to stderr
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * _writefd - writes the character c to the given file descriptor
 * @character: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _writefd(char character, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[index++] = character;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += _putsfd(str++, fd);
	}
	return (count);
}

