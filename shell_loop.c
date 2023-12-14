#include "shell.h"

/**
 * shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(info_t *info, char **argv)
{
	ssize_t input_length = 0;
	int builtin_result = 0;

	while (input_length != -1 && builtin_result != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		input_length = get_input(info);
		if (input_length != -1)
		{
			set_info(info, argv);
			builtin_result = find_builtin_command(info);
			if (builtin_result == -1)
				find_executable_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}
	return (builtin_result);
}

/**
 * find_builtin_command - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", my_env},
		{"help", my_help},
		{"history", _myhistory},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_result = builtintbl[i].func(info);
			break;
		}
	}
	return (builtin_result);
}

/**
 * find_executable_command - finds an executable command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_executable_command(info_t *info)
{
	char *path = NULL;
	int i, argument_count;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, argument_count = 0; info->arg[i]; i++)
	{
		if (!is_delimiter(info->arg[i], " \t\n"))
			argument_count++;
	}

	if (!argument_count)
		return;

	path = find_command_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_executable_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_executable_command(info, info->argv[0]))
			fork_executable_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_executable_command - forks an exec thread to run a command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_executable_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

