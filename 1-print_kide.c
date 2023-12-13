#include "shell.h"
#include <errno.h>
#include <unistd.h>
/**
 * print_kide - prints data to standart output
 * @message: output to print
 * Return: void
 */
void print_kide(const char *message)
{
	int message_length = strlen(message);

	ssize_t bytes_written = write(STDOUT_FILENO, message, message_length);

	if (bytes_written == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

