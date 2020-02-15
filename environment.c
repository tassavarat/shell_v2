#include "shell.h"

/**
 * arrtol - Converts arrays to linked list
 *
 * Return: Pointer to first node
 */
list *arrtol(void)
{
	int i = 0;
	list *head = NULL;

	while (environ[i])
	{
		add_node_end(&head, environ[i]);
		++i;
	}
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
	list *head = args->head;

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
