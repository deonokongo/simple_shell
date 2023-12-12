#include "shell.h"
/**
 * main - Entry point for the shell program.
 * Return: Always return 0
 */
void main(void)
{
	while (1)
	{
		char line[BUFFER_SIZE];
		size_t buffer = BUFFER_SIZE;
		ssize_t bytesRead = my_getline(&line, &buffer);
		char *command = strtok(line, ";");

		while (command != NULL)
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
					char *args[MAX_ARGS];
					int arg_count = 0;
					char *token = strtok(subcommand, " ");

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
					success = execute_process(subcommand, "");
				}

				if ((success && subcommand[0] == '|') || (!success && subcommand[0] == '&'))
				{
					break;
				}

				subcommand = strtok(NULL, "&|");
			}

			command = strtok(NULL, ";");
		}

		free(line);
	}

	return (0);
}

