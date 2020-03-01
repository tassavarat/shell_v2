#include "_getline.h"
#include "shell.h"

static int failure;

/**
 * get_fd - get id of the car
 * @head: linked list of cars
 * @fd: the id to look for
 * Return: the node with given @id or NULL
 */
descriptor_t *get_fd(descriptor_t **head, int fd)
{
	descriptor_t *prev = NULL, *node, *cur;

	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		prev = cur;
		cur = cur->next;
	}

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);

	node->fd = fd;
	node->next = NULL;
	_memset(node->buf, 0, READ_SIZE);
	node->pos = 0;
	if (!*head)
		*head = node;
	else
		prev->next = node;
	return (node);
}

/**
 * _realloc - realloc() implementation
 * @ptr: pointer to the memory
 * @old_size: old size of the block of memory
 * @new_size: new size of the block of memory
 *
 * Return: void
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s, *a;
	unsigned int i, limit;

	if (old_size == new_size)
		return (ptr);
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	s = malloc(sizeof(char) * new_size);
	if (!s)
	{
		failure = 1;
		return (NULL);
	}
	if (ptr == NULL)
		return (s);
	a = ptr;
	limit = new_size > old_size ? old_size : new_size;
	for (i = 0; i < limit; i++)
	{
		s[i] = a[i];
	}
	free(ptr);
	return (s);
}


/**
 * read_descriptor - read function
 * @line: the line
 * @pos: pos in the @line
 * @size: size of line
 * @need: space needed for flushing
 * @desc: file descriptor
 * Return:  @line
 */
char *flush_buffer(char *line, size_t *pos, size_t *size,
		   size_t need, descriptor_t *desc)
{
	size_t free_space;

	free_space = *size - *pos;
	if (need > free_space)
	{
		line = _realloc(line, *size, *size + READ_SIZE + 1);
		if (!line)
			return (NULL);
		*size += READ_SIZE;
		_memset(line + *pos + need, 0, READ_SIZE - need + 1);
	}
	_memcpy(line + *pos, desc->buf + desc->pos, need);
	*pos += need;
	return (line);
}

/**
 * read_descriptor - read function
 * @desc: file descriptor
 * Return: A line read from @fd
 */
char *read_descriptor(descriptor_t *desc)
{
	size_t line_size = 0, line_pos = 0, needed_space;
	char *line = NULL, *temp;
	ssize_t read_val = 0, old_val;

	while (1)
	{
		temp = strsrch(desc->buf + desc->pos, '\n', READ_SIZE - desc->pos);
		if (!temp)
		{
			if (read_val > 0)
			{
				needed_space = READ_SIZE - desc->pos; /*Max READ_SIZE*/
				line = flush_buffer(line, &line_pos, &line_size, needed_space, desc);
				if (!line && failure)
					return (NULL);
			}
			old_val = read_val, read_val = read(desc->fd, desc->buf, READ_SIZE);
			if (read_val < READ_SIZE)
				_memset(desc->buf + (read_val), 0, (READ_SIZE - read_val));
			if (read_val < 1)
			{
				if (read_val == 0 && line && old_val > 0)
					return (line);
				free(line);
				return (NULL);
			}
			desc->pos = 0;
		}
		else
		{
			*temp = '\0';
			needed_space = temp - (desc->buf + desc->pos) + 1;
			line = flush_buffer(line, &line_pos, &line_size, needed_space, desc);
			if (!line && failure)
				return (NULL);
			desc->pos += needed_space;
			return (line);
		}
	}
	return (NULL);
}

/**
 * _getline - getline function
 * @fd: file descriptor
 * Return: A line read from @fd
 */
char *_getline(const int fd)
{
	static descriptor_t *list;
	descriptor_t *cur = NULL, *tmp;

	if (fd == -1)
	{
		cur = list;
		while (cur != NULL)
		{
			tmp = cur;
			cur = cur->next;
			free(tmp);
		}
		return (NULL);
	}
	if (fd < 0)
		return (NULL);
	cur = get_fd(&list, fd);
	if (!cur)
		return (NULL);
	return (read_descriptor(cur));
}
