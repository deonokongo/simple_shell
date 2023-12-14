#include "shell.h"

/**
 * kide_print - Prints a formatted string to standard output
 * @format: The format string to be printed
 *
 * Description: This function prints a formatted string to the standard output
 * using the write system call.
 */
void kide_print(const char *format)
{
	write(STDOUT_FILENO, format, strlen(format));
}

