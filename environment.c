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

/**
 * var_expansion - Looks for variables in the current
 * environmental  * variables
 * @args: An array of tokenized commands
 */
void var_expansion(arguments *args)
{
	int i, len = 0;
	list *env = args->env;

	for (i = 0; args->tokarr[i]; i++)
	{
		if (args->tokarr[i][0] == '$')
		{
			if (args->tokarr[i][1] == '?')
				args->tokarr[i] = convert(args->exit_status, 10);
			else if (args->tokarr[i][1] == '$')
				args->tokarr[i] = convert(getpid(), 10);
			else
			{
				args->tokarr[i]++;
				len = _strlen(args->tokarr[i]);
				if (!len)
				{
					args->tokarr[i]--;
					continue;
				}
				for (env = args->env; env; env = env->next)
				{
					if (!_strncmp(args->tokarr[i], env->str, len))
					{
						args->tokarr[i] = env->str + len + 1;
						break;
					}
					if (!env->next)
						args->tokarr[i] = NULL;
				}
			}
		}
	}
}
