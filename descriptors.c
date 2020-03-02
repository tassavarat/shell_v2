#include "shell.h"

/**
 * choose_fd - specifies from which fd to get the input
 * @args: arguments struct
 * Return: fd of the file or STDIN_FILENO
*/
int choose_fd(arguments *args)
{
	int fd = STDIN_FILENO;

	if (args->ac == 2)
	{
		fd = open(args->av[1], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "%s: %lu: Can't open %s\n", *args->av,
				args->cmdnum - 1, args->av[1]);
			args->exit_status = 127;
		}
	}

	return (fd);
}

/**
 * read_config - reads .hshrc config file
 * @args: arguments struct
*/
void read_config(arguments *args)
{
	char *home = _getenv("HOME=", args);
	char *conf = ".hshrc";
	char buf[PATH_MAX] = {0};
	int fd, backup_fd;

	if (!home)
		return;

	backup_fd = args->fd;
	sprintf(buf, "%s/%s", home, conf);
	fd = open(buf, O_RDONLY);
	args->fd = fd;
	if (fd != -1)
	{
		shell(args);
	}
	args->fd = backup_fd;
	args->cmdnum = 1;
}
