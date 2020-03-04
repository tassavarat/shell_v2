#include "shell.h"

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
	{
		/* error(args); */
		return;
	}
	while ((str = _getline(fd)))
	{
		en_queue(args->history, str);
		free(str);
	}
	close(fd);
}


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
