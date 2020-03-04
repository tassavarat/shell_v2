#include "shell.h"

/**
 * overwriteval - checks if alias value should be overwritten
 * @head: pointer to aliases head node
 * @name: string to compare with alias names
 *
 * Return: node to overwrite or NULL if no overwrite needed
 */
aliases *overwriteval(aliases *head, char *name)
{
	aliases *cur;

	for (cur = head; cur; cur = cur->next)
		if (!_strcmp(name, cur->name))
		{
			free(cur->value);
			return (cur);
		}
	return (NULL);
}

/**
 * doublealias - checks for double alias
 * @head: pointer to aliases head node
 * @value: string to compare with alias names
 *
 * Return: value
 */
char *doublealias(aliases *head, char *value)
{
	aliases *cur;

	for (cur = head; cur; cur = cur->next)
		if (!_strcmp(value, cur->name))
			return (cur->value);
	return (value);
}
