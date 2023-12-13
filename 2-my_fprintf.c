#include "shell.h"
#include <stdarg.h>
#include <stdio.h>
/**
 * my_fprintf - prints output to a file stream
 * @stream: file stream
 * @format: format of the output
 * Return: number of characters written
 */
int my_fprintf(FILE *stream, const char *format, ...)
{
	const char *p;
	va_list args;

	int chars_written = 0;

	va_start(args, format);

	for (p = format; *p != '\0'; ++p)
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

