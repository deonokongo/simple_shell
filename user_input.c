#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_length: address of buffer length variable
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buffer, size_t *buffer_length)
{
	ssize_t bytes_read = 0;
	size_t current_buffer_length = 0;

	if (!*buffer_length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytes_read = getline(buffer, &current_buffer_length, stdin);
#else
		bytes_read = _getline(info, buffer, &current_buffer_length);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			remove_comment(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*buffer_length = bytes_read;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (bytes_read);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	char *buffer;
	static size_t buffer_start, buffer_end, buffer_length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *current_position;

	_putchar(BUFFER_FLUSH);
	bytes_read = input_buffer(info, &buffer, &buffer_length);
	if (bytes_read == -1)
		return (-1);
	if (buffer_length)
	{
		buffer_end = buffer_start;
		current_position = buffer + buffer_start;

		check_chain(info, buffer, &buffer_end, buffer_start, buffer_length);
		while (buffer_end < buffer_length)
		{
			if (is_chain(info, buffer, &buffer_end))
				break;
			buffer_end++;
		}

		buffer_start = buffer_end + 1;
		if (buffer_start >= buffer_length)
		{
			buffer_start = buffer_end = buffer_length = 0;
			info->cmd_buffer_type = CMD_NORM;
		}

		*buffer_ptr = current_position;
		return (_strlen(current_position));
	}

	*buffer_ptr = buffer;
	return (bytes_read);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @buffer_length: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *buffer_length)
{
	ssize_t bytes_read = 0;

	if (*buffer_length)
		return (0);
	bytes_read = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*buffer_length = bytes_read;
	return (bytes_read);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t buffer_start, buffer_length;
	size_t k;
	ssize_t bytes_read = 0, size = 0;
	char *current_position = NULL, *new_position = NULL, *c;

	current_position = *ptr;
	if (current_position && length)
		size = *length;
	if (buffer_start == buffer_length)
		buffer_start = buffer_length = 0;

	bytes_read = read_buffer(info, buffer, &buffer_length);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_length == 0))
		return (-1);

	c = _strchr(buffer + buffer_start, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_position = my_realloc(current_position, size, size ? size + k : k + 1);
	if (!new_position)
		return (current_position ? free(current_position), -1 : -1);

	if (size)
		_strncat(new_position, buffer + buffer_start, k - buffer_start);
	else
		_strncpy(new_position, buffer + buffer_start, k - buffer_start + 1);

	size += k - buffer_start;
	buffer_start = k;
	current_position = new_position;

	if (length)
		*length = size;
	*ptr = current_position;
	return (size);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

