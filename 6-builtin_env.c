#include "shell.h"
/**
 * is_builtin - Checks if a given command is a built-in command.
 * @command: The command to check.
 *
 * Return:  1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(char *command)
{
	for (struct builtin *builtin = builtins; builtin->name != NULL; builtin++)
	{
		if (strcmp(command, builtin->name) == 0)
		{
			return (1);
		}
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
	char *command = args[0];

	for (struct builtin *builtin = builtins; builtin->name != NULL; builtin++)
	{
		if (strcmp(command, builtin->name) == 0)
		{
			builtin->func(args);
			return;
		}
	}
	const char *error_message = "Error: Unknown command '%s'\n";
	sprintf((char *)error_message, error_message, command);	
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
 * @args: The arguments for the 'env' command.
 *
 * Return: void
 */
void builtin_env(char **environ)
{

	while (**environ)
	{
		print_kide((const char *)*environ);
		environ++;
	}
}
/**
 * builtin_setenv - Handles the built-in 'setenv' command.
 * @args: The arguments for the 'setenv' command.
 *
 * Return: void
 */
void builtin_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		my_fprintf(stderr, "setenv: missing arguments\n");
		return;
	}
	char *variable = args[1];
	char *value = args[2];

	if (setenv(variable, value, 1) != 0)
	{
		my_fprintf(stderr, "setenv: unable to set variable '%s'\n", variable);
		return;
	}
	char message[1024];
	sprintf(message, "%s=%s\n", variable, value);
	print_kide((const char *)message);
}

