#include "shell.h"

/**
 * my_env - prints the current environment
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int my_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 *        Used to maintain constant function prototype.
 * @name: environment variable name
 *
 * Return: the value of the environment variable
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * populate_env_list - Populates the environment linked list
 * @info: Structure containing potential arguments.
 *          Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

