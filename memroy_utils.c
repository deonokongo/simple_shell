#include "shell.h"

/**
 * free_env_list - Frees the memory associated with the environment list.
 * @env: Pointer to the head of the environment list.
 *
 * Return: Always 0.
 */
int free_env_list(list_t *env)
{
	list_t *current = env;
	list_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->str);  
		free(current);
		current = next;
	}
	return 0;
}

