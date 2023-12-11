#inclyde "shell.h"
/**
 * print_kide = prints data to standart output
 * @message: output to print
 * Return: void
 */
void print_kide(const char *message) {
	write(STDOUT_FILENO, message, strlen(message));
}
