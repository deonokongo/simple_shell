#include "shell.h"
#include <stdarg.h>
#include <stdio.h>
/**
 * my_fprintf - for formatted output to a file stream
 * @file: file stream
 * @format: format of the output
 * Return: void
 */
int my_fprintf(FILE *stream, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	int chars_written = 0;

	for (const char *p = format; *p != '\0'; ++p)
	{
		if (*p == '%')
		{
			switch (*++p)
			{
				case 's':
					{
						char *str = va_arg(args, char *);
						chars_written += fputs(str, stream);
						break;
					}
				case 'd':
					{
						int i = va_arg(args, int);
						chars_written += fprintf(stream, "%d", i);
						break;
					}
				default:
					fputc('%', stream);
					break;
			}
		}
		else
		{
			chars_written += fputc(*p, stream);
		}
	}

	va_end(args);
	return (chars_written);
}


