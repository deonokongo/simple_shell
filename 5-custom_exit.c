#include "shell.h"
/**
 * custom_exit - Exits the program with a specified status, closing any open file.
 * @status: The exit status code.
 * Return: void
 */
void custom_exit(int status)
{
	if (file != NULL)
	{
		fflush(file);
		fclose(file);
		print_kide("File closed successfully.\n");
		exit(status);
	}
}
/**
 * is_atty - Checks if a file descriptor corresponds to a terminal.
 * @fd: The file descriptor to check.
 * Return: 1 if the file descriptor corresponds to a terminal, 0 otherwise.
 */
int is_atty(int fd)
{
	if (fd < 0 || fd >= _NFILE)
	{
		return 0;
	}

	if (!_file_table[fd].is_atty)
	{
		return 0;
	}

	if (!_file_table[fd].is_open_read)
	{
		return 0;
	}

	return 1;
}
/**
 * is_open_read - Checks if a file descriptor is open for reading.
 * @fd: The file descriptor to check.
 * Return: 1 if the file descriptor is open for reading, 0 otherwise.
 */
int is_open_read(int fd)
{
	int flags = fcntl(fd, F_GETFL);

	if (flags != -1 && (flags & O_ACCMODE) == O_RDONLY)
	{
		return 1;
	}

	return 0;
}
/**
 * is_interactive_mode - Checks if the program is running in interactive mode.
 *
 * Return: 1 if running in interactive mode, 0 otherwise.
 */
int is_interactive_mode(void)
{
	return is_atty(STDIN_FILENO) && is_atty(STDOUT_FILENO) && is_atty(STDERR_FILENO);
}


