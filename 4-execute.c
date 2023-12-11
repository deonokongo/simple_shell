#include "shell.h"
/**
 * execute_command - executes a command using fork and execvp.
 * @args: array of command arguments.
 *Return: 0 or 1 on success
 */
void execute_command(const char *args[])
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
		waitpid(child_pid, &status, 0);

		char status_str[10];
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
 * execute_process - Executes a process by creating a child process and using execv.
 * @command: The command to be executed.
 * @path: The path to search for the executable.
 *Return: 0 or 1 on success
 */
void execute_process(const char *command, const char *path)
{
	pid_t child_p = fork();

	if (child_p == 0)
	{
		char *found_path = search_executable(command, path);
		if (found_path != NULL)
		{
			execv(found_path, (char *const[]){found_path, NULL});

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
 * search_executable - Searches for the executable path of a command in the specified path.
 * @command: The command to find the executable path for.
 * @path: The path to search for the executable.
 *Return: dynamically allocated string
 */
char *search_executable(const char *command, const char *path)
{
	char *token;
	char *path_copy = malloc(strlen(path) + 1);
	if (path_copy == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	copy_string(path_copy, path);

	token = my_strtok(path_copy, ':');
	while (token != NULL)
	{
		char *found_path = malloc(strlen(token) + strlen(command) + 2); 
		if (found_path == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		my_fprintf(found_path, "%s/%s", token, command);

		if (access(found_path, X_OK) == 0)
		{
			free(path_copy);
			return found_path;
		}

		free(found_path);
		token = my_strtok(NULL, ':');
	}

	free(path_copy);
	return NULL;
}
/**
 * free_memory - Frees the allocated memory for command arguments, line, and found_path.
 * @argv: An array of strings representing command arguments.
 * @line: A string representing the command line.
 * @found_path: A string representing the found executable path.
 *Return: void
 */
void free_memory(char **argv, char *line, char *found_path) {
	for (int i = 0; argv[i] != NULL; ++i) 
	{
		free(argv[i]);
	}
	free(line);
	free(found_path);
}

