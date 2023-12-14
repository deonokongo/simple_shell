#include "shell.h"

/**
 * my_history - displays the history list, one command per line,
 *              preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets an alias by removing it from the alias list.
 * @info: parameter struct
 * @alias_str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_str)
{
	char *equal_sign_position, saved_char;
	int ret;

	equal_sign_position = _strchr(alias_str, '=');
	if (!equal_sign_position)
		return (1);

	saved_char = *equal_sign_position;
	*equal_sign_position = '\0';

	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

	*equal_sign_position = saved_char;
	return (ret);
}

/**
 * set_alias - sets an alias to a string by adding it to the alias list.
 * @info: parameter struct
 * @alias_str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_str)
{
	char *equal_sign_position;

	equal_sign_position = _strchr(alias_str, '=');
	if (!equal_sign_position)
		return (1);

	if (!*++equal_sign_position)
		return (unset_alias(info, alias_str));

	unset_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_alias - prints an alias string in a readable format.
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *equal_sign_position = NULL, *alias_name = NULL;

	if (node)
	{
		equal_sign_position = _strchr(node->str, '=');
		for (alias_name = node->str; alias_name <= equal_sign_position; alias_name++)
			_putchar(*alias_name);

		_putchar('\'');
		_puts(equal_sign_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *        Used to maintain a constant function prototype.
 *
 * Return: Always 0
 */
int my_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_position = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_position = _strchr(info->argv[i], '=');
		if (equal_sign_position)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

