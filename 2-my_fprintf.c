#include "shell.h"

/**
 * my_fprintf - for formatted output to a file stream
 * @file: file stream
 * @format: format of the output
 * Return: void
 */
void my_fprintf(FILE *file, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	vdprintf(fileno(file), format, args);
	va_end(args);
}


