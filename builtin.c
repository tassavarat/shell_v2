#include "shell.h"

/**
 * changedir - Changes directory
 * @args: Arguments structure
 *
 * Return: 0 on success, otherwise 1
 */
int changedir(arguments *args)
{
	char *nwd = NULL, *cwd = NULL;

	cwd = getcwd(cwd, 0);
	if (parsecd(args) == -1)
	{
		errno = CDERR;
		error(args);
		free(cwd);
		return (1);
	}
	nwd = getcwd(nwd, 0);
	set_environment(&(args->env), "OLDPWD", cwd);
	set_environment(&(args->env), "PWD", nwd);
	free(nwd);
	free(cwd);
	return (0);
}

/**
 * penv - prints environment variables
 * @args: arguments structure
 *
 * Return: 0 on success
 */
int penv(arguments *args)
{
	list *cur = args->env;

	while (cur)
	{
		/* printf("%s\n", cur->str); FIXME: printf*/
		_puts(cur->str);
		_puts("\n");
		cur = cur->next;
	}
	return (0);
}

/**
 * callexit - changes directory
 * @args: arguments structure
 *
 * Return: 1 on failure, otherwise exit
 */
int callexit(arguments *args)
{
	int number = 0;

	if (args->tokarr[1])
	{
		number = _atoi(args->tokarr[1]);
		if (number == -1)
		{
			errno = EXITERR;
			error(args);
			return (1);
		}
	}
	else
	{
		number = args->exit_status;
	}
	cleanup(args, '\0');
	exit(number);
}

/**
 * clear_scr - clears screen
 * @args: arguments structure
 *
 * Return: 0 on success, may not work on some systems
 */
int clear_scr(arguments *args)
{
	char *clr = "\033[2J";
	char *move = "\033[1;1H";

	(void) args;
	/* printf("%s%s", move, clr); FIXME: printf*/
	_puts(move);
	_puts(clr);
	return (0);
}

/**
 * builtins - calls appropriate built-ins
 * @args: arguments structure
 *
 * Return: 0 on success, 1 no built-in found
 */
int builtins(arguments *args)
{
	size_t i, stat;
	built_ins func_arr[] = {
		{"cd", changedir},
		{"env", penv},
		{"exit", callexit},
		{"clear", clear_scr},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"help", help},
		{NULL, NULL}
	};

	for (i = 0; func_arr[i].bi; ++i)
		if (!_strcmp(*args->tokarr, func_arr[i].bi))
		{
			stat = func_arr[i].f(args);
			if (!stat)
				args->exit_status = 0;
			if (args->pstat == 1)
				close(args->pipefd[1]);
			else if (args->pstat == 0)
				close(args->pipefd[0]);
			return (0);
		}
	return (1);
}
