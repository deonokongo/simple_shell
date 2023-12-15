#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};

	int fd = STDOUT_FILENO;

	const int EXIT_OPEN_ERROR = 1;
	const int EXIT_NOENT = 127;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fd)
			: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_input(av[0]);
				print_input(": 0: Can't open ");
				print_input(av[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(EXIT_NOENT);
			}
			perror("open");
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}

