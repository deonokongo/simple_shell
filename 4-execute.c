#include "shell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

char *my_strtok(char *str, char delimiter);
int my_fprintf(FILE *stream, const char *format, ...);
/**
 * execute_command - Executes a command using fork and execvp.
 * @command: Command to execute.
 * Return: void
 */
void execute_command(const char *command)
{
	pid_t child_p = fork();

	if (child_p == 0)
	{
		execlp("/bin/sh", "sh", "-c", command, (char *)NULL);
		perror("Error executing command");
		exit(EXIT_FAILURE);
	}
	else if (child_p > 0)
	{
		int status;
		char status_str[10];

		waitpid(child_p, &status, 0);
		snprintf(status_str, sizeof(status_str), "%d", WEXITSTATUS(status));
		setenv("?", status_str, 1);
	}
	else if (child_p == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("Error forking process");
	}
}
/**
 * execute_process - Executes a process.
 * @command: The command to be executed.
 * @path: The path to search for the executable.
 * Return: void
 */
void execute_process(const char *command, const char *path)
{
	char *found_path = search_executable(command, path);

	pid_t child_p = fork();

	if (child_p == 0)
	{
		char *exec_args[2];

		exec_args[0] = found_path;
		exec_args[1] = NULL;

		if (found_path != NULL)
		{
			execv(found_path, exec_args);
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		else
		{
			my_fprintf(stderr, "Command not found: %s\n", command);
			exit(EXIT_FAILURE);
		}
	}
	else if (child_p > 0)
	{
		wait(NULL);
	}
	else if (child_p == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("Error forking process");
	}
}
/**
 * search_executable - Searches for the executable path of a command.
 * @command: Command to find the executable path for.
 * @path: Path to search for the executable.
 * Return: Dynamically allocated string.
 */
char *search_executable(const char *command, const char *path)
{
	char *token;
	FILE *fp;

	char *found_path = NULL;
	char *path_copy = malloc(strlen(path) + 1);

	if (path_copy == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	copy_string(path_copy, path);
	token = my_strtok(path_copy, ':');

	while (token != NULL)
	{
		found_path = malloc(strlen(token) + strlen(command) + 2);

		if (found_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		fp = fopen(found_path, "w");
		if (!fp)
		{
			perror("fopen");
			free(found_path);
			continue;
		}

		my_fprintf(fp, "%s/%s", token, command);
		fclose(fp);

		if (access(found_path, X_OK) == 0)
		{
			free(path_copy);
			return (found_path);
		}

		free(found_path);
		token = my_strtok(NULL, ':');
	}

	free(path_copy);
	return (NULL);
}
/**
 * free_memory - Frees the allocated memory for command arguments.
 * @argv: An array of strings representing command arguments.
 * @line: A string representing the command line.
 * @found_path: Found executable path.
 * Return: void
 */
void free_memory(char **argv, char *line, char *found_path)
{
	int i;

	for (i = 0; argv[i] != NULL; ++i)
	{
		free(argv[i]);
	}
	free(argv);
	free(line);
	free(found_path);
}


