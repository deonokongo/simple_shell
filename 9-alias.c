#include "shell.h"

/**
 * print_all_aliases - Prints all key-value pairs in the hash table
 * Return: void
 */
void print_all_aliases(void)
{
	for (int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		KeyValuePair *current = hash_table[i];
		while (current != NULL)
		{
			print_kide("%s='%s'\n", current->key, current->value);
			current = current->next;
		}
	}
}
/**
 * builtin_alias - Handles alias built-in command.
 * @argv: Array of command-line arguments
 *Return: void
 */
void builtin_alias(char *argv[])
{
	if (argv[1] == NULL)
	{
		for (KeyValuePair *pair = hash_table_begin(alias_table); pair != NULL; pair = hash_table_next(alias_table))
		{
			print_kide("%s='%s'\n", pair->key, pair->value);
		}
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
				print_kide("%s: alias not found\n", alias_name);
			}
		}
	}
	else
	{
		for (int i = 1; argv[i] != NULL; ++i)
		{
			char *definition = argv[i];
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
	}
}

