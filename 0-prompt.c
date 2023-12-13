#include "shell.h"
/**
 * prompt - displays the shell command prompt
 *
 * Return: void
 */
char *prompt(void)
{
	char *command = NULL;
	size_t buffer = 0;

	print_kide("(simple_shell)$ ");

	ssize_t characters_read = my_getline(&command, &buffer);

	if (characters_read == -1)
	{
		perror("my_getline");
		exit(EXIT_FAILURE);
	}

	size_t length = strlen(command);

	if (length > 0 && command[length - 1] == '\n')
	{
		command[length - 1] = '\0';
	}

	print_tokens(command);
	execute_process(command, "");

	return (command);
}

