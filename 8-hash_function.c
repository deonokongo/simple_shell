#include "shell.h"

/**
 * hash_function - Generates a hash value for a given key.
 * @key: The key to hash.
 *
 * Return: The hash value.
 */
unsigned int hash_function(const char *key)
{
	unsigned int hash = 0;
	while (*key)
	{
		hash = (hash << 5) + *key++;
	}
	return (hash % HASH_TABLE_SIZE);
}
/**
 * hash_table_put - Adds a key-value pair to the hash table.
 * @key: The key to add.
 * @value: The corresponding value.
 */
void hash_table_put(const char *key, const char *value)
{
	unsigned int index = hash_function(key);


	KeyValuePair *new_pair = (KeyValuePair *)malloc(sizeof(KeyValuePair));
	new_pair->key = strdup(key);
	new_pair->value = strdup(value);
	new_pair->next = NULL;

	if (hash_table[index] == NULL)
	{
		hash_table[index] = new_pair;
	}
	else
	{
		KeyValuePair *current = hash_table[index];
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_pair;
	}
}
/**
 * hash_table_get - Retrieves the value associated with a key in the hash table.
 * @key: The key to search for.
 * Return: The value associated with the key, or NULL if not found.
 */
const char *hash_table_get(const char *key)
{
	unsigned int index = hash_function(key);

	KeyValuePair *current = hash_table[index];
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}

	return (NULL);
}


