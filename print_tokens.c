#include "shell.h"
char *my_strtok(char *str, char delimiter);
/**
 * print_tokens - Print the tokens in the given command.
 * @command: The command containing tokens.
 * Return: void
 */
void print_tokens(const char *command)
{
	int i;
	char *argv[MAX_TOKENS];

	int argc = 0;

	char *token = my_strtok((char *)command, ' ');

	while (token != NULL && argc < MAX_TOKENS - 1)
	{
		argv[argc] = malloc(strlen(token) + 1);
		if (argv[argc] == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strdup(argv[argc++]);
		token = my_strtok(NULL, ' ');
	}
	argv[argc] = NULL;

	print_kide("Tokens: ");
	for (i = 0; i < argc; ++i)
	{
		print_kide(argv[i]);
	}
	print_kide("\n");

	free_memory(argv, NULL, NULL);
}

