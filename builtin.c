#include "shell.h"

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int changedir(arguments *args)
{
	(void) args;
	/* char *cwd = NULL, *temp = NULL; */
	/* char *oldwd = NULL; */
	/* int val = 0; */
	/* char *home = _getenv("HOME=", args); */

	/* oldwd = getcwd(oldwd, 0); */
	/* if (args->tokarr[1] == NULL) */
	/* { */
	/* 	val = chdir(home ? home : oldwd); */
	/* } */
	/* else if (*args->tokarr[1] == '-') */
	/* { */
	/* 	val = chdir(_getenv("OLDPWD=", args) ? _getenv("OLDPWD=", args) : oldwd); */
	/* 	_puts(getcwd(temp, 0)), _puts("\n"), free(temp); */
	/* } */
	/* else */
	/* 	val = chdir(args->tokarr[1]); */
	/* if (val == -1) */
	/* { */
	/* 	errno = 0; */
	/* 	error(args, 3); */
	/* } */
	/* if (1) */
	/* { */
	/* 	args->tokarr[1] = "OLDPWD", args->tokarr[2] = oldwd; */
	/* 	_setenv(args); */
	/* 	args->tokarr[1] = "PWD", args->tokarr[2] = cwd = getcwd(cwd, 0); */
	/* 	_setenv(args); */
	/* 	free(cwd); */
	/* } */
	/* free(oldwd); */
	return (1);
}

/**
 * callexit - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int penv(arguments *args)
{
	(void) args;
	return (0);
}

/**
 * callexit - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int callexit(arguments *args)
{
	int number = 0;

	if (args->tokarr[1])
	{
		number = _atoi(args->tokarr[1]);
		if (number == -1)
		{
			/* errno = ILLNUM; */
			/* error(args, 21); */
			/* args->exit_status = 2; */
			printf("Error\n");
			return (1);
		}
	}
	else
	{
		number = args->exit_status;
	}
	/* Make this a function? */
	free(*args->tokarr);
	free(args->tokarr);
	exit(number);
}

/**
 * clear_scr - Clears screen
 * @args: Arguments structure
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

int builtins(arguments *args)
{
	size_t i;
	built_ins func_arr[] = {
		{"cd", changedir},
		{"env", penv},
		{"exit", callexit},
		{"clear", clear_scr},
		{NULL, NULL}
	};

	for (i = 0; func_arr[i].bi; ++i)
		if (!_strcmp(*args->tokarr, func_arr[i].bi))
			return (func_arr[i].f(args));
	return (0);
}
