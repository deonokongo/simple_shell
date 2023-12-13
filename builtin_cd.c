#include "shell.h"
#include <limits.h>
/**
 * change_directory - Changes the current working directory.
 * @new_dir: The directory to change to.
 *
 * Return: 0 on success, -1 on failure.
 */
int change_directory(const char *new_dir)
{
	if (access(new_dir, R_OK | X_OK) != 0)
	{
		my_fprintf(stderr, "cd: %s: No such file or directory\n", new_dir);
		return (-1);
	}

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return (-1);
	}

	char old_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", new_dir, 1);

	return (0);
}

/**
 * print_current_directory - Prints the current working directory.
 *
 * Return: void
 */
void print_current_directory(void)
{
	char current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return;
	}

	my_fprintf(stdout, "%s\n", current_dir);
}

/**
 * builtin_cd - Handles the built-in 'cd' command.
 * @args: The arguments for the 'cd' command.
 *
 * Return: void
 */
void builtin_cd(char **args)
{
	char *new_dir;

	if (args[1] == NULL)
	{
		new_dir = getenv("HOME");

		if (new_dir == NULL)
		{
			my_fprintf(stderr, "cd: HOME not set\n");
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");

		if (new_dir == NULL)
		{
			my_fprintf(stderr, "cd: -: OLDPWD not set\n");
			return;
		}
	}
	else
	{
		new_dir = args[1];
	}

	if (change_directory(new_dir) == 0)
	{
		print_current_directory();
	}
}

