#include "shell.h"

/**
 * interactive - checks if the shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for an alphabetic character
 * @ch: The character to check
 *
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *str)
{
	int i, sign = 1, digit_found = 0, result = 0;

	for (i = 0; str[i] != '\0' && digit_found != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			digit_found = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (digit_found == 1)
			digit_found = 2;
	}

	if (sign == -1)
		result = -result;

	return (result);
}

