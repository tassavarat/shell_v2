#include "shell.h"

/**
 * changedir - Changes directory
 * @args: Arguments structure
 *
 * Return: 0 on success
 */
int changedir(arguments *args)
{
	char *nwd = NULL, *cwd = NULL;

	cwd = getcwd(cwd, 0);
	if (parsecd(args) == -1)
	{
		errno = CDERR;
		error(args);
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
		printf("%s\n", cur->str);
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
	printf("%s%s", move, clr);
	return (0);
}

/**
 * builtins - calls appropriate built-ins
 * @args: arguments structure
 *
 * Return: 0 on success, 1 built-in error, 2 no built-in found
 */
int builtins(arguments *args)
{
	size_t i;
	built_ins func_arr[] = {
		{"cd", changedir},
		{"env", penv},
		{"exit", callexit},
		{"clear", clear_scr},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; func_arr[i].bi; ++i)
		if (!_strcmp(*args->tokarr, func_arr[i].bi))
			return (func_arr[i].f(args));
	return (2);
}
