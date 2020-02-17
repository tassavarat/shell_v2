#include "shell.h"

/**
 * arrtol - Converts arrays to linked list
 *
 * Return: Pointer to first node
 */
list *envlist(void)
{
	int i;
	list *head = NULL;

	for (i = 0; environ[i]; ++i)
		if (!add_node_end(&head, environ[i]))
			return (NULL);
	return (head);
}

/**
 * _getenv - Prints environmental variables
 * @name: name of the environmental variable
 * @args: Arguments struct
 * Return: value of variable
 * NULL on failure
 */
char *_getenv(char *name, arguments *args)
{
	size_t len = _strlen(name);
	list *head = args->env;

	while (head)
	{
		if (!_strncmp(name, head->str, len))
		{
			name = head->str + len;
			return (name);
		}
		head = head->next;
	}
	return (NULL);
}
