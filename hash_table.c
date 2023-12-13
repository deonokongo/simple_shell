#include "shell.h"
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

/**
 * hash_function - Generates a hash value for a given key.
 * @key: The key to be hashed.
 * Return: The hash value.
 */
unsigned int hash_function(const char *key)
{
	unsigned int hash = 0;
	while (*key)
	{
		hash = (hash << 5) + *key++;
	}
	return (hash % TABLE_SIZE);
}

/**
 * hash_table_contains - Checks if a key is present in the hash table.
 * @key: The key to check.
 * Return: 1 if the key is present, 0 otherwise.
 */
int hash_table_contains(const char *key)
{
	unsigned int index = hash_function(key);
	Node *current = table[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			return (1);
		}
		current = current->next;
	}

	return (0);
}

/**
 * hash_table_get - Retrieves the value associated with a key.
 * @key: The key to retrieve the value for.
 * Return: The value associated with the key, or NULL if the key is not present.
 */
char *hash_table_get(const char *key)
{
	unsigned int index = hash_function(key);
	Node *current = table[index];

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			return (strdup(current->value));
		}
		current = current->next;
	}

	return (NULL);
}

/**
 * hash_table_put - Inserts a key-value pair into the hash table.
 * @key: The key to insert.
 * @value: The value associated with the key.
 * Return: void
 */
void hash_table_put(const char *key, const char *value)
{
	unsigned int index = hash_function(key);
	Node *new_node = malloc(sizeof(Node));

	if (new_node == NULL)
	{
		exit(EXIT_FAILURE);
	}

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;

	new_node->next = table[index];
	table[index] = new_node;
}

