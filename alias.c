#include "shell.h"

/**
 * checkalias - checks for alias match and replaces as needed
 * @args: arguments structure
 */
void checkalias(arguments *args)
{
	size_t i;
	aliases *cur;

	for (i = 0; args->tokarr[i]; ++i)
		for (cur = args->head; cur; cur = cur->next)
			if (!_strcmp(args->tokarr[i], cur->name))
				args->tokarr[i] = cur->value;
}

/**
 * delalias - frees aliases linked list
 * @head: pointer to head node
 */
void delalias(aliases *head)
{
	aliases *cur;

	cur = head;
	while (head)
	{
		head = head->next;
		free(cur->name);
		free(cur->value);
		free(cur);
		cur = head;
	}
}

/**
 * printalias - prints aliases
 * @head: pointer to head of linked list
 * @s: string to compare against alias node names
 *
 * Return: 0 on success, 1 if alias not found
 */
int printalias(aliases *head, char *s)
{
	aliases *cur;

	for (cur = head; !s && cur; cur = cur->next)
		fprintf(stdout, "%s='%s'\n", cur->name, cur->value);
	for (cur = head; s && cur; cur = cur->next)
		if (!_strcmp(s, cur->name))
		{
			fprintf(stdout, "%s='%s'\n", cur->name, cur->value);
			break;
		}
	if (s && !cur)
	{
		fprintf(stderr, "alias: %s not found\n", s);
		return (1);
	}
	return (0);
}

/**
 * aliasnode - creates and initialises new alias node
 * @head: double pointer to head of linked list
 * @tokarr: string to tokenise
 *
 * Return: newly created node or NULL on failure
 */
aliases *aliasnode(aliases **head, char *tokarr)
{
	aliases *new;
	char *token, *s;
	int new_alias;

	new_alias = 0;
	s = _strdup(tokarr);
	if (!s)
		return (NULL);
	token = strtok(s, "=");
	new = overwrite(*head, token);
	if (!new)
	{
		new_alias = 1;
		new = malloc(sizeof(*new));
		if (!new)
			return (NULL);
		new->name = _strdup(token);
		if (!new->name)
			return (NULL);
	}
	token = strtok(NULL, "=");
	new->value = _strdup(token);
	if (!new->value)
		return (NULL);
	if (new_alias)
	{
		new->next = *head;
		*head = new;
	}
	free(s);
	return (new);
}

/**
 * alias - handles aliases
 * @args: arguments structure
 *
 * Return: 0 on success, otherwise 1
 */
int alias(arguments *args)
{
	size_t i, j;
	int new_alias, stat;

	new_alias = stat = 0;
	for (i = 1; args->tokarr[i]; ++i)
	{
		for (j = 0; args->tokarr[i][j]; ++j)
			if (args->tokarr[i][j] == '=')
			{
				aliasnode(&args->head, args->tokarr[i]);
				new_alias = 1;
				break;
			}
		if (!new_alias)
		{
			/* should return 1 if single alias not found or */
			/* overwrite with 0 if another alias further along */
			/* tokarr found? */
			stat = printalias(args->head, args->tokarr[i]);
			new_alias = 0;
		}
	}
	if (i == 1)
		stat = printalias(args->head, NULL);
	return (stat);
}
