#include "shell.h"
#include <sys/wait.h>

/**
 * execute_command - Executes a command using fork and execvp.
 *
 * @command: The command to be executed.
 *
 * This function creates a child process to execute the  using execvp.
 *
 * If there is an error during forking or executing the command, an error
 * message is printed.
 */
void execute_command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		kide_print("Error forking process.\n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[128];
		int arg_count = 0;

		char *token = strtok((char *)command, " ");

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}

		args[arg_count] = NULL;
		execvp(args[0], args);

		kide_print("Error executing command.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

