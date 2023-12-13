#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *input;

	initialize_table();

	while (1)
	{
		char *prompt = "$ ";
		input = readline(prompt);

		if (input == NULL)
		{
			printf("\n");
			free(input);
			break;
		}

		if (strlen(input) > 0)
		{
			if (execute_command(input) != 0)
			{
				printf("Command not found: %s\n", input);
			}
		}

		free(input);
	}

	return 0;
}
