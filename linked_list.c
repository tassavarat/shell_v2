#include "shell.h"

/**
 * list_len - counts the number elements of a linked list
 * @h: a pointer to the head of a linked list
 *
 * Return: The number of nodes
 */
size_t list_len(const list *h)
{
	size_t count = 0;

	while (h)
	{
		count++;
		h = h->next;
	}
	return (count);
}

/**
 * delete_node_at_index - deletes nth element
 * @head: a pointer to the head
 * @index: index of a node to be removed
 * Return: Return 1 if succes or -1 when it fails
 */
int delete_node_at_index(list **head, size_t index)
{
	unsigned int i;
	list *current;
	list *forward;

	if (*head == NULL)
		return (-1);
	current = *head;
	if (index == 0)
	{
		*head = current->next;
		return (1);
		free(current->str);
		free(current);
	}
	for (i = 0; i < index - 1; i++)
	{
		if (current->next == NULL)
			return (-1);
		current = current->next;
	}
	forward = *head;
	if (forward->next == NULL)
		return (-1);
	forward = current->next;
	current->next = forward->next;
	free(forward->str);
	free(forward);
	return (1);
}

/**
 * free_list - frees given linked list
 * @head: first element of a linked list
 * Return: Nothing.
 */
void free_list(list *head)
{
	list *current_addr = head;
	list *next_addr = NULL;

	if (head == NULL)
		return;
	while (current_addr != NULL)
	{
		free(current_addr->str);
		next_addr = current_addr->next;
		free(current_addr);
		current_addr = next_addr;
	}
}

/**
 * add_node_end - Adds a node at the end of a list
 * @head: Pointer to address of a list
 * @str: Pointer to string
 *
 * Return: Address of new element
 * On error, NULL
 */
list *add_node_end(list **head, const char *str)
{
	list *new, **cur;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = _strdup(str);
	if (!new->str)
		return (NULL);
	new->next = NULL;

	cur = head;
	while (*cur)
		cur = &(*cur)->next;
	new->next = *cur;
	*cur = new;
	if (!*head)
	{
		*head = new;
		return (*head);
	}
	return (new);
}
