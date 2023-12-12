#include "shell.h"
/**
 * copy_string - copies characters from source to destination
 * @dest: destination string.
 * @src: source string.
 * @max_len: maximum length of characters to copy.
 * Return: void
 */
void copy_string(char *dest, const char *src, size_t max_len)
{
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
 * Return: void
 */
void remove_newline(char *str)
{
	size_t length = strlen(str);

	if (length > 0 && str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
	}
}
