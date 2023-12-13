#include "shell.h"

/**
 * prompt - displays the shell command prompt
 * Return: void
 */
char *prompt(void)
{
	char *command = NULL;

	size_t buffer = 0;
	size_t length = strlen(command);

	print_kide("(simple_shell)$");

	my_getline(&command, &buffer);

	if (length > 0 && command[length - 1] == '\n')
	{
		command[length - 1] = '\0';
	}

	return (command);
	free(command);
}

