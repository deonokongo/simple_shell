#include "shell.h"

/**
 * _strncpy - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @max_characters: the maximum number of characters to be copied
 *
 * Return: the concatenated string
 */
char *_strncpy(char *destination, char *source, int max_characters)
{
	int source_index, destination_index;
	char *result = destination;

	source_index = 0;
	while (source[source_index] != '\0' && source_index < max_characters - 1)
	{
		destination[source_index] = source[source_index];
		source_index++;
	}

	if (source_index < max_characters)
	{
		destination_index = source_index;
		while (destination_index < max_characters)
		{
			destination[destination_index] = '\0';
			destination_index++;
		}
	}
	return (result);
}

/**
 * _strncat - concatenates two strings
 * @destination: the first string
 * @source: the second string
 * @max_characters: the maximum number of characters to be used
 *
 * Return: the concatenated string
 */
char *_strncat(char *destination, char *source, int max_characters)
{
	int destination_index, source_index;
	char *result = destination;

	destination_index = 0;
	while (destination[destination_index] != '\0')
		destination_index++;

	source_index = 0;
	while (source[source_index] != '\0' && source_index < max_characters)
	{
		destination[destination_index] = source[source_index];
		destination_index++;
		source_index++;
	}

	if (source_index < max_characters)
		destination[destination_index] = '\0';

	return (result);
}

/**
 * _strchr - locates a character in a string
 * @string: the string to be parsed
 * @character: the character to look for
 *
 * Return: a pointer to the first occurrence of the character in the string
 */
char *_strchr(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

