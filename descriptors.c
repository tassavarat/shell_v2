#include "shell.h"

/**
 * choose_fd - specifies from which fd to get the input
 * @args: arhuments struct
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
			fprintf(stderr, "%s: %lu: Can't open file\n", *args->av, args->cmdnum - 1);
			args->exit_status = 127;
		}
	}

	return (fd);
}
