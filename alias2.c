#include "shell.h"

/**
 * overwrite - checks if alias should be overwritten
 * @head: pointer to aliases head node
 * @s: string to compare with alias names
 *
 * Return: node to overwrite or NULL if no overwrite needed
 */
aliases *overwrite(aliases *head, char *s)
{
	aliases *cur;

	for (cur = head; cur; cur = cur->next)
		if (!_strcmp(s, cur->name))
		{
			free(cur->value);
			return (cur);
		}
	return (NULL);
}
