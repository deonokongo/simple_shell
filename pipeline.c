#include "shell.h"
/**
 * create_pipe - Create a pipe and return the file descriptors.
 *
 * Return: An array containing the read and write file descriptors.
 */
int *create_pipe(void)
{
	int *pipe_fds = malloc(2 * sizeof(int));

	if (pipe_fds == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	return (pipe_fds);
}
/**
 * run_single_command - Run a single command.
 * @command: The command to be executed.
 * @write_fd: The write end of the pipe
 *
 * Return: void
 */
void run_single_command(char *command, int write_fd)
{
	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		close(write_fd);
		dup2(write_fd, STDOUT_FILENO);
		close(write_fd);

		if (is_builtin(command))
		{
			char *args[MAX_ARGS];
			int arg_count = 0;
			char *token = strtok(command, " ");

			while (token != NULL && arg_count < MAX_ARGS - 1)
			{
				args[arg_count++] = token;
				token = strtok(NULL, " ");
			}
			args[arg_count] = NULL;

			execute_builtin(args);
		}
		else
		{
			execute_process(command, "");
		}

		exit(EXIT_SUCCESS);
	}
	else if (child_pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	close(write_fd);
	waitpid(child_pid, NULL, 0);
}
/**
 * run_pipeline - Runs a pipeline of shell commands.
 * @command: The command string containing the pipeline.
 * Return: void
 */
void run_pipeline(char *command)
{
	char *commands[MAX_COMMANDS];
	int num_commands;
	int *pipe_fds;

	num_commands = split_pipeline(command, commands);

	if (num_commands > 0)
	{
		pipe_fds = create_pipe();

		run_single_command(commands[0], pipe_fds[1]);
		close(pipe_fds[1]);

		while (*command != '\0' && *command != '|')
		{
			command++;
		}

		if (*command == '|')
		{
			command++;
		}

		close(pipe_fds[0]);
	}
	else
	{
		my_fprintf(stderr, "Error: No commands in the pipeline.\n");
	}
}
/**
 * split_pipeline - Split a command string into individual commands based on '|'.
 * @command: The command string to split.
 * @commands: An array to store the split commands.
 *
 * Return: The number of split commands.
 */
int split_pipeline(const char *command, char *commands[MAX_COMMANDS])
{
	int i = 0;
	const char *delimiter = "|";
	char *token = strtok((char *)command, delimiter);

	while (token != NULL && i < MAX_COMMANDS)
	{
		commands[i++] = token;
		token = strtok(NULL, delimiter);
	}

	return (i);
}
