#include "shell.h"

/**
 * print_aliases - Print all aliases in the alias table
 * Return: void
 */
void print_aliases(void)
{
	for (KeyValuePair * pair = hash_table_begin(alias_table); pair != NULL;
			pair = hash_table_next(alias_table))
	{
		print_kide("%s='%s'\n", pair->key, pair->value);
	}
}

/**
 * print_alias_not_found - Print a message for an alias not found
 * @alias_name: Name of the alias
 * Return: void
 */
void print_alias_not_found(const char *alias_name)
{
	print_kide("%s: alias not found\n", alias_name);
}

/**
 * update_alias_table - Update the alias table with a new alias definition
 * @definition: Alias definition
 * Return: void
 */
void update_alias_table(const char *definition)
{
	char *name, *value;

	if (strchr(definition, '=') != NULL)
	{
		name = definition;
		value = strchr(definition, '=') + 1;

		if (hash_table_contains(alias_table, name))
		{
			free(hash_table_get(alias_table, name));
		}
		hash_table_put(alias_table, name, strdup(value));
	}
	else
	{
		print_kide("Invalid alias definition: '%s'\n", definition);
	}
}

/**
 * handle_alias_command - Handle the alias built-in command
 * @argv: Array of command-line arguments
 * Return: void
 */
void handle_alias_command(char *argv[])
{
	if (argv[1] == NULL)
	{
		print_aliases();
	}
	else if (argv[2] == NULL)
	{
		for (int i = 1; argv[i] != NULL; ++i)
		{
			char *alias_name = argv[i];
			char *value = hash_table_get(alias_table, alias_name);

			if (value)
			{
				print_kide("%s='%s'\n", alias_name, value);
			}
			else
			{
				print_alias_not_found(alias_name);
			}
		}
	}
	else
	{
		for (int i = 1; argv[i] != NULL; ++i)
		{
			update_alias_table(argv[i]);
		}
	}
}

