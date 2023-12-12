#include "shell.h"
/**
 * builtin_unsetenv - Handles the built-in 'unsetenv' command.
 * @args: The arguments for the 'unsetenv' command.
 *
 * Return: void
 */
void builtin_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		my_fprintf(stderr, "unsetenv: missing argument\n");
		return;
	}

	char *variable = args[1];

	if (args[1] == NULL)
	{
		my_fprintf(stderr, "unsetenv: missing argument\n");
		return;
	}
	char *variable = args[1];

	if (unsetenv(variable) != 0)
	{
		my_fprintf(stderr, "unsetenv: unable to unset variable '%s'\n", variable);
		return;
	}

	print_kide("%s unset\n", variable);
}
