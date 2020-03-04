#include "shell.h"

/**
 * read_history - reads input command history from file
 * @args: arguments structure
 */
void read_history(arguments *args)
{
	char *home = _getenv("HOME=", args);
	char buf[PATH_MAX] = {0};
	char *str;
	int fd;

	if (!home)
		return;
	sprintf(buf, "%s/%s", home, HISTORY_FILE);
	fd = open(buf, O_RDONLY);
	if (fd == -1)
		return;
	while ((str = _getline(fd)))
	{
		en_queue(args->history, str);
		free(str);
	}
	close(fd);
}

/**
 * write_history - writes input command history to file
 * @args: arguments structure
 */
void write_history(arguments *args)
{
	char *home = _getenv("HOME=", args);
	list *cur = args->history->first;
	char buf[PATH_MAX] = {0};
	int fd;

	if (!home)
		return;
	sprintf(buf, "%s/%s", home, HISTORY_FILE);
	fd = open(buf, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd == -1)
	{
		error(args);
		return;
	}
	for (; cur; cur = cur->next)
	{
		write(fd, cur->str, _strlen(cur->str));
		write(fd, "\n", 1);
	}
	close(fd);
}

/**
 * history - prints out shell input history preceded by command number
 * @args: arguments structure
 *
 * Return: 0
 */
int history(arguments *args)
{
	list *cur = args->history->first;
	size_t i;

	for (i = args->history->pos; cur; ++i, cur = cur->next)
	{
		fprintf(stdout, "%lu: %s\n", i, cur->str);
	}
	return (0);
}
