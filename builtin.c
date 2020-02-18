#include "shell.h"

/**
 * _unsetenv - Unsets the specified environment variable
 * @args: Arugements structure
 * Return: 1 on success
 */
int _unsetenv(arguments *args)
{
	list *tmp, *prev;
	char *p;
	size_t /*i = 0,*/ len;

	if (!args->tokarr[1])
	{
		/* error(args, 1); */
		perror("perror called in _unsetenv");
		return (1);
	}
	tmp = prev = args->env;
	len = _strlen(args->tokarr[1]);
	while (tmp)
	{
		p = _strchr(tmp->str, '=');
		/* args->index = i; */
		if (len == (size_t ) (p - tmp->str) &&
				!(_strncmp(tmp->str, args->tokarr[1], len)))
		{
			/* delete_node_at_index(&(args->head), i); */
			prev->next = tmp->next;
			free(tmp);
			break;
		}
		prev = tmp;
		tmp = tmp->next;
		/* ++i; */
	}
	return (0);
}

/**
 * _setenv - Sets specified enviroment variable
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int _setenv(arguments *args)
{
	char *variable = NULL, *value = NULL;
	char tmp[PATH_MAX] = {0};

	if (args->tokarr[1] && args->tokarr[2])
	{
		variable = args->tokarr[1];
		value = args->tokarr[2];
		_unsetenv(args);
		_strcat(tmp, variable);
		_strcat(tmp, "=");
		_strcat(tmp, value);
		/* add_node_end(&(args->head), tmp); */
		insert_node_at_index(&(args->head), args->index, tmp);
		return (1);
	}
	error(args, 1);
	return (1);
}

int parsecd(arguments *args)
{
	int val;
	char *home = _getenv("HOME=", args), *oldpw = _getenv("OLDPWD=", args);
	char *tmp = NULL;

	if (args->tokarr[1] == NULL && home)
	{
		val = chdir(home);
	}
	else if (*args->tokarr[1] == '-' && oldpw)
	{
		val = chdir(oldpw);
		printf("%s\n", getcwd(tmp, 0));
		free(tmp);
	}
	else
		val = chdir(args->tokarr[1]);
	return (val);
}

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int changedir(arguments *args)
{
	char *nwd = NULL, *cwd = NULL;

	cwd = getcwd(cwd, 0);
	if (parsecd(args) == -1)
	{
		errno = 0;
		perror("perror called in changedir");
		/* error(args, 3); */
	}
	args->tokarr[1] = "OLDPWD", args->tokarr[2] = cwd;
	_setenv(args);
	args->tokarr[1] = "PWD", args->tokarr[2] = nwd = getcwd(nwd, 0);
	_setenv(args);
	free(nwd);
	free(cwd);
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
	list *cur = args->env;

	while (cur) {
		printf("%s\n", cur->str);
		cur = cur->next;
	}
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
	cleanup(args, '\0');
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
