#include "shell.h"

/**
 * _unsetenv - Unsets the specified environment variable
 * @args: Arugements structure
 * Return: 1 on success
 */
int _unsetenv(arguments *args)
{
	list *tmp, *prev = NULL;
	char *p;
	size_t len;

	if (!args->tokarr[1])
	{
		perror("perror called in _unsetenv");
		return (1);
	}
	tmp = args->env;
	len = _strlen(args->tokarr[1]);
	while (tmp)
	{
		p = _strchr(tmp->str, '=');
		if (len == (size_t ) (p - tmp->str) &&
		    !(_strncmp(tmp->str, args->tokarr[1], len)))
		{
			if (prev)
				prev->next = tmp->next;
			else
				args->env = tmp->next;
			free(tmp->str);
			free(tmp);
			break;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

/**
 * set_environment - Sets specified enviroment variable
 * @env: Environment list
 * @name: Name of the environment
 * @value: Value of the @name
 * Return: Nothing
 */
void set_environment(list **env, char *name, char *value)
{
	list *tmp, *prev = NULL;
	char *p = NULL;
	char buf[PATH_MAX] = {0};
	size_t len;

	tmp = *env;
	len = _strlen(name);
	while (tmp)
	{
		p = _strchr(tmp->str, '=');
		if (len == (size_t ) (p - tmp->str) &&
		    !(_strncmp(tmp->str, name, len)))
			break;
		prev = tmp;
		tmp = tmp->next;
	}
	sprintf(buf, "%s=%s", name, value);
	if (tmp)
	{
		free(tmp->str);
	}
	else
	{
		tmp = malloc(sizeof(*tmp)); /*Check  malloc?*/
		tmp->next = NULL;
	}
	if (prev)
		prev->next = tmp;
	else if (!*env)
		*env = tmp;
	tmp->str = _strdup(buf);
}


/**
 * _setenv - Sets specified enviroment variable
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int _setenv(arguments *args)
{
	if (args->tokarr[1] && args->tokarr[2])
	{
		set_environment(&(args->env), args->tokarr[1], args->tokarr[2]);
		return (0);
	}
	perror("perror called in _setenv");
	return (1);
}

int parsecd(arguments *args)
{
	int val = 0;
	char *home = _getenv("HOME=", args), *oldpw = _getenv("OLDPWD=", args);
	char *tmp = NULL;

	if (args->tokarr[1] == NULL)
	{
		if (home)
			val = chdir(home);
	}
	else if (*args->tokarr[1] == '-')
	{
		if (oldpw)
			val = chdir(oldpw);
		tmp = getcwd(tmp, 0);
		printf("%s\n", tmp);
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
		/* errno = 0; */
		/* perror("perror called in changedir"); */
		error(args);
	}
	nwd = getcwd(nwd, 0);
	set_environment(&(args->env), "OLDPWD", cwd);
	set_environment(&(args->env), "PWD", nwd);
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
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; func_arr[i].bi; ++i)
		if (!_strcmp(*args->tokarr, func_arr[i].bi))
			return (func_arr[i].f(args));
	return (2);
}
