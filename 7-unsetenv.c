#include "shell.h"

/**
 * builtin_unsetenv - Handles the built-in 'unsetenv' command.
 * @args: The arguments for the 'unsetenv' command.
 *
 * Return: void
 */
void builtin_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		my_fprintf(stderr, "unsetenv: missing argument\n");
		return;
	}
	char *variable = args[1];
	if (unsetenv(variable) != 0)
	{
		my_fprintf (stderr, "unsetenv: unable to unset variable '%s'\n", variable);
		return;
	}

	print_kide("%s unset\n", variable);
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
	} else if (strcmp(args[1], "-") == 0)
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

	if (access(new_dir, R_OK | X_OK) != 0)
	{
		my_fprintf(stderr, "cd: %s: No such file or directory\n", new_dir);
		return;
	}

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		return;
	}

	char old_pwd[PATH_MAX];
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("getcwd");
		return;
	}

	setenv("OLDPWD", old_pwd, 1);
	setenv("PWD", new_dir, 1);

	my_fprintf(stdout, "%s\n", new_dir);
}

