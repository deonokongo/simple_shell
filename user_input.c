#include "shell.h"

/**
 * get_input_command - Reads input command from stdin and removes the newline.
 * @command: Pointer to the buffer to store the input command.
 * @size: Size of the buffer.
 */
void get_input_command(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			kide_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			kide_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}

