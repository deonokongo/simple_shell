#include "shell.h"

/**
 * main - Entry point for the shell program.
 *
 * Return: Always 0 (success).
 */
int main(void)
{
	char command[100];

	while (1)
	{
		display_prompt();
		get_input_command(command, sizeof(command));
		execute_command(command);
	}
	return (0);
}
