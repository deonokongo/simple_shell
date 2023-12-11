#include "shell.h"
/**
 * prompt - displays the shell command prompt
 * Return: void
 */
void prompt(void)
{
	print_kide("(simple_shell) $ ");
	char *command = NULL;
	size_t buffer = 0;
	my_getline(&command, &buffer);
	print_tokens(command);
	execute_process(command, ""); 
	free(command);
}

