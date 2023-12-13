#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * is_builtin - Checks if a given command is a built-in command.
 * @command: The command to check.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(char *command)
{
	struct builtin *builtin;

	for (builtin = builtins; builtin->name != NULL; builtin++)
	{
		if (strcmp(command, builtin->name) == 0)
			return (1);
	}

	return (0);
}

/**
 * execute_builtin - Executes a built-in command.
 * @args: The arguments for the built-in command.
 * Return: void
 */
void execute_builtin(char **args)
{
	struct builtin *builtin;

	char *command = args[0];
	const char *error_message = "Error: Unknown command '%s'\n";

	for (builtin = builtins; builtin->name != NULL; builtin++)
	{
		if (strcmp(command, builtin->name) == 0)
		{
			builtin->func(args);
			return;
		}
	}
	my_fprintf(stderr, error_message, command);
}

/**
 * builtin_exit - Handles the built-in 'exit' command.
 * @args: The arguments for the 'exit' command.
 * Return: void
 */
void builtin_exit(char **args)
{
	if (args[1] != NULL)
	{
		int exit_status = atoi(args[1]);

		exit(exit_status);
	}
	else
	{
		exit(0);
	}
}

/**
 * builtin_env - Handles the built-in 'env' command.
 * @environ: 'env' command.
 * Return: void
 */
void builtin_env(char **environ)
{
	while (*environ)
	{
		print_kide(*environ);
		environ++;
	}
}

/**
 * builtin_setenv - Handles the built-in 'setenv' command.
 * @args: The arguments for the 'setenv' command.
 * Return: void
 */
void builtin_setenv(char **args)
{
	char *variable = args[1];
	char *value = args[2];
	char message[1024];

	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "setenv: missing arguments\n");
		return;
	}

	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "setenv: unable to set variable '%s'\n", variable);
		return;
	}
	sprintf(message, "%s=%s\n", variable, value);
	print_kide(message);
}

