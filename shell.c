#include "shell.h"
/**
 * main - Entry point for the simple shell program.
 * Return: Always 0.
 */
int main(void)
{
	char command[100];
	int my_eof;

	char *input = read_line(&my_eof);

	while (1)
	{
		display_prompt();

		if (my_eof == -1)
		{
			printf("Exiting the shell. Goodbye!\n");
			free(input);
			break;
		}

		if (input[strlen(input) - 1] == '\n')
		{
			input[strlen(input) - 1] = '\0';
		}

		printf("%s\n", input);

		free(input);
	}

	return (0);
}

