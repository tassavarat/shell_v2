#include "shell.h"

/**
 * create_queue - Creates an empty queue
 * Return: new queue
*/
queue *create_queue()
{
	queue *q = malloc(sizeof(queue));

	if (!q)
		exit(EXIT_FAILURE);

	q->first = q->last = NULL;
	q->size = 0;
	q->pos = 0;

	return (q);
}

/**
 * en_queue - en_queue
 * @queue: queue
 * @node: LL node
 */
void en_queue(queue *queue, char *cmd)
{
	list *new_node = malloc(sizeof(*new_node));
	list *tmp = NULL;

	if (!new_node)
		exit(EXIT_FAILURE);

	new_node->str = _strdup(cmd);
	new_node->next = NULL;
	queue->size++;
	if (queue->last == NULL)
	{
		queue->first = queue->last = new_node;
	}
	else
	{
		if (queue->size == HISTORY_SIZE + 1)
		{
			tmp = queue->first;
			queue->first = queue->first->next;
			free(tmp->str);
			free(tmp);
			queue->pos++;
			queue->size--;
		}
		queue->last->next = new_node;
		queue->last = new_node;
	}
}

/**
* free_queue - frees a queue
* @q: pointer to head of queue
* Return: Nothing.
*/
void free_queue(queue **q)
{
	list *prev;
	list *head;

	head = (*q)->first;

	while (head)
	{
		prev = head->next;
		free(head->str);
		free(head);
		head = prev;
	}

	free(*q);
	*q = NULL;
}
