#include "hash_table.h"

Node **table;
unsigned int table_size;
unsigned int num_elements;

/**
 * initialize_table - Initializes the hash table.
 */
void initialize_table()
{
	table_size = INITIAL_TABLE_SIZE;
	num_elements = 0;

	table = (Node **)malloc(sizeof(Node *) * table_size);
	if (!table)
	{
		fprintf(stderr, "Failed to initialize hash table.\n");
		exit(EXIT_FAILURE);
	}
	for (unsigned int i = 0; i < table_size; ++i)
	{
		table[i] = NULL;
	}
}

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
	return (hash % table_size);
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
	if (!new_pair)
	{
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	new_pair->key = strdup(key);
	new_pair->value = strdup(value);
	new_pair->next = NULL;

	if (table[index] == NULL)
	{
		Node *new_node = (Node *)malloc(sizeof(Node));
		if (!new_node)
		{
			fprintf(stderr, "Memory allocation error.\n");
			exit(EXIT_FAILURE);
		}
		new_node->head = new_pair;
		table[index] = new_node;
	}
	else
	{
		KeyValuePair *current = table[index]->head;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_pair;
	}
	num_elements++;
}

/**
 * hash_table_get - Retrieves the value associated with a key.
 * @key: The key to search for.
 *
 * Return: The value associated with the key, or NULL if not found.
 */
const char *hash_table_get(const char *key)
{
	unsigned int index = hash_function(key);

	if (table[index] != NULL)
	{
		KeyValuePair *current = table[index]->head;

		while (current != NULL)
		{
			if (strcmp(current->key, key) == 0)
			{
				return current->value;
			}
			current = current->next;
		}
	}
	return (NULL);
}

/**
 * hash_table_contains - Checks if a key is present in the hash table.
 * @key: The key to check.
 *
 * Return: 1 if the key is found, 0 otherwise.
 */
int hash_table_contains(const char *key)
{
	unsigned int index = hash_function(key);

	if (table[index] != NULL)
	{
		KeyValuePair *current = table[index]->head;

		while (current != NULL)
		{
			if (strcmp(current->key, key) == 0)
			{
				return (1);
			}
			current = current->next;
		}
	}
	return (0);
}


