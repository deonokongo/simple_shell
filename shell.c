#include "shell.h"
KeyValuePair *alias_table[HASH_TABLE_SIZE];

void main(void)

{
	while (1)
	{
		char line[BUFFER_SIZE];
		char *args[MAX_ARGS];
		int arg_count = 0;
		char *token = strtok(subcommand, " ");
		size_t buffer = BUFFER_SIZE;
		ssize_t bytesRead = my_getline(&line, &buffer);
		printf("Read %lu bytes: %s\n", bytesRead, line);

		char *command = my_strtok(line, ";");
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

				subcommand = my_strtok(NULL, "&|");
			}

			command = my_strtok(NULL, ";");
		}

		free(line);
	}
}


