#include "shell.h"

/**
 * shell_run - calls relevant functions to parse
 * @args: arguments structure
 * @lineptr: input string
 */
void shell_run(arguments *args, char *lineptr)
{
	int rstat, fds[3] = {0};

	rstat = check_redirection(args, lineptr, fds);
	if (rstat == -1)
		return;
	args->tokarr = tokenise(lineptr);
	if (!args->tokarr)
		return;
	var_expansion(args);
	if (builtins(args))
	{
		checkalias(args);
		create_process(args);
	}
	else
		checkalias(args);
	cleanup(args, 'L');
	if (rstat == 1)
		clean_redirection(args, fds);
}

/**
 * shell - gets input and calls relevant functions to parse
 * @args: arguments structure
 */
void shell(arguments *args)
{
	char *lineptr = NULL;

	while (1)
	{
		pprompt(args, "$");
		lineptr = _getline(args->fd);
		if (!lineptr)
		{
			_puts(args->exitstr);
			free(lineptr);
			return;
		}
		parse_operators(args, lineptr);
		free(lineptr);
		++args->cmdnum;
	}
}
