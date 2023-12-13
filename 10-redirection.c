#include "shell.h"
/**
 * my_redirection - Redirects input/output/error for a command.
 * @command: Command to execute.
 * @output_file: File to redirect standard output to
 * @error_file: File to redirect standard error to
 *Return: void
 */
void my_redirection(char *command, char *output_file, char *error_file)
{
	int pid = fork();

	if (pid == 0)
	{
		if (output_file)
		{
			int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);

			if (fd < 0)
			{
				perror(output_file);
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (error_file)
		{
			int fd = open(error_file, O_WRONLY | O_CREAT | O_APPEND, 0666);

			if (fd < 0)
			{
				perror(error_file);
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDERR_FILENO);
			close(fd);
		}

		execlp("/bin/bash", "bash", "-c", command, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
}
/**
 * replace_variable - Replaces occurrences of a variable in a command
 * @command: Command string to modify.
 * @variable: Variable to replace.
 * @value: New value for the variable.
 * Return: A newly allocated string with the variable replaced
 */
char *replace_variable(char *command, const char *variable, const char *value)
{
	char *pos = strstr(command, variable);
	char *result = malloc(strlen(command) + strlen(value) - strlen(variable) + 1);

	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (pos != NULL)
	{
		copy_string(result, command, pos - command);
		result[pos - command] = '\0';
		strcat(result, value);
		strcat(result, pos + strlen(variable));
	}
	else
	{
		copy_string(result, command);
	}

	return (result);
}


