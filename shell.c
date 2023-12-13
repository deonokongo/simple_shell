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
		char line[BUFFER_SIZE];
		char *args[MAX_ARGS];
		int arg_count = 0;
		char *token = strtok(subcommand, " ");
		size_t buffer = BUFFER_SIZE;
		ssize_t bytesRead = my_getline(&line, &buffer);
		printf("Read %lu bytes: %s\n", bytesRead, line);

		char *prompt = "$ ";
		input = readline(prompt);

		if (input == NULL)
		{
			char *subcommand = strtok(command, "&|");
			bool success = true;
			while (subcommand != NULL)
			{
				if (*subcommand == '#')
				{
					subcommand = strtok(NULL, "&|");
					continue;
				}
				if (is_builtin(subcommand))
				{
					while (token != NULL && arg_count < MAX_ARGS - 1)
					{
						args[arg_count++] = token;
						token = my_strtok(NULL, " ");
					}
					args[arg_count] = NULL;

					execute_builtin(args);
				}
				else
				{
					success = execute_process(subcommand, "");
				}

				if ((success && subcommand[0] == '|') || (!success && subcommand[0] == '&'))
				{
					break;
				}
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
		return (0);
	}
