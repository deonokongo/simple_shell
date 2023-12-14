#include "shell.h"

/**
 * is_chain - test if current character in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the character buffer
 * @position: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *position)
{
	size_t current_position = *position;

	if (buf[current_position] == '|' && buf[current_position + 1] == '|')
	{
		buf[current_position] = '\0';
		current_position++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[current_position] == '&' && buf[current_position + 1] == '&')
	{
		buf[current_position] = '\0';
		current_position++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[current_position] == ';')
	{
		buf[current_position] = '\0'; 
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return 0;

	*position = current_position;
	return 1;
}

/**
 * check_chain - checks if we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @position: address of current position in buf
 * @start_position: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *position, size_t start_position, size_t length)
{
	size_t current_position = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[start_position] = '\0';
			current_position = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[start_position] = '\0';
			current_position = length;
		}
	}

	*position = current_position;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *alias_node;
	char *alias_value;

	for (i = 0; i < 10; i++)
	{
		alias_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!alias_node)
			return 0;

		free(info->argv[0]);

		alias_value = _strchr(alias_node->str, '=');
		if (!alias_value)
			return 0;

		alias_value = _strdup(alias_value + 1);
		if (!alias_value)
			return 0;

		info->argv[0] = alias_value;
	}

	return 1;
}

/**
 * replace_variables - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_variables(info_t *info)
{
	int i = 0;
	list_t *env_node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		env_node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (env_node)
		{
			replace_string(&(info->argv[i]), _strdup(_strchr(env_node->str, '=') + 1));
			continue;
		}

		replace_string(&info->argv[i], _strdup(""));
	}

	return 0;
}

/**
 * replace_string - replaces string
 * @old_str: address of old string
 * @new_str: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return 1;
}
i
