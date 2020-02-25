#include "shell.h"

/**
 * ltoa - Converts linked list to array
 * @head: Pointer to first node
 *
 * Return: Converted array
 */
char **ltoa(list *head)
{
	int i = 0, len = list_len(head);
	char **arr = NULL;

	if (!head)
		return (NULL);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);

	while (head)
	{
		arr[i] = head->str;
		head = head->next;
		++i;
	}
	arr[i] = NULL;
	return (arr);
}


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
