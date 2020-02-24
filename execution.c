#include "shell.h"

/**
 * shell_run - calls relevant functions to parse
 * @args: arguments structure
 * @lineptr: input string
 */
void shell_run(arguments *args, char *lineptr)
{
	int fds[3] = {-2, -2, STDOUT_FILENO};

	check_redirection(args, lineptr, fds);
	if (fds[0] != -2 && fds[1] != -2 && (fds[0] == -1 || fds[1] == -1
					 || dup2(fds[0], fds[2]) == -1))
	{
		if (fds[0] != -1)
			close(fds[0]);
		error(args);
		return;
	}

	args->tokarr = tokenise(lineptr);
	if (!args->tokarr)
		return;
	if (builtins(args) == 2)
		create_process(args);
	cleanup(args, 'L');
	if (fds[0] != -2)
	{
		if (dup2(fds[1], fds[2]) == -1)
			error(args);
		close(fds[0]);
	}
}

/**
 * shell - gets input and calls relevant functions to parse
 * @args: arguments structure
 */
void shell(arguments *args)
{
	char *lineptr = NULL;
	size_t n;
	ssize_t byterd = 0;

	while (1)
	{
		pprompt(args);
		byterd = getline(&lineptr, &n, stdin);
		if (byterd == EOF || syntaxerr(lineptr))
		{
			printf("%s", args->exitstr);
			free(lineptr);
			return;
		}
		parse_operators(args, lineptr);
		++args->cmdnum;
	}
}
