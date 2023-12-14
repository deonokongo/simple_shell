#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	if (!info->env || !var)
		return 0;

	size_t i = delete_node_with_prefix(&(info->env), var, '=');
	info->env_changed = (i > 0) ? 1 : 0;
	return info->env_changed;
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	if (!var || !value)
		return 0;

	char *buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return 1;

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	size_t index = update_or_add_node(&(info->env), var, '=', buf);
	free(buf);

	info->env_changed = (index != SIZE_MAX) ? 1 : 0;
	return 0;
}

