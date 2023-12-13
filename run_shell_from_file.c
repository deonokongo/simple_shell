#include "shell.h"
/**
 * run_shell_from_file - Runs shell commands from a file.
 * @filename: Name of the file containing shell commands.
 *
 * Return: 0 on success, 1 on failure.
 */
int run_shell_from_file(char *filename)
{
	FILE *file = fopen(filename, "r");

	if (!file)
	{
		print_kide(filename);
		return (1);
	}
	char line[MAX_LINE_LENGTH];

	while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
	{
		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) > 0)
		{
			system(line);
		}
	}
	fclose(file);
	return (0);
}

