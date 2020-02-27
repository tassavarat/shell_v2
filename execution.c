#include "shell.h"

/**
 * shell_run - calls relevant functions to parse
 * @args: arguments structure
 * @lineptr: input string
 */
void shell_run(arguments *args, char *lineptr)
{
	int fds[3] = {0};
	int res;

	res = check_redirection(args, lineptr, fds);
	if (res == -1)
		return;
	args->tokarr = tokenise(lineptr);
	if (!args->tokarr)
		return;
	if (builtins(args))
		create_process(args);
	cleanup(args, 'L');
	if (res == 1)
		clean_redirection(args, fds);
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
		pprompt(args, "$");
		byterd = getline(&lineptr, &n, stdin);
		/* if (byterd == EOF || syntaxerr(lineptr)) FIXME*/
		if (byterd == EOF)
		{
			/* printf("%s", args->exitstr); FIXME: printf */
			_puts(args->exitstr);
			free(lineptr);
			return;
		}
		parse_operators(args, lineptr);
		++args->cmdnum;
	}
}
