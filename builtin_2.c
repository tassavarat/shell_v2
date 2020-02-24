#include "shell.h"

/**
 * envmatch - checks for matching enviroment variable name
 * @s: first string to compare
 * @tmp: second string to compare
 * @args: arguments structure
 *
 * Return: 1 on match otherwise 0
 */
size_t envmatch(char *s, list *tmp, arguments *args)
{
	char *p;
	size_t len;

	if (!s)
		s = args->tokarr[1];
	len = _strlen(s);
	p = _strchr(tmp->str, '=');
	return ((len == (size_t) (p - tmp->str) &&
			!(_strncmp(tmp->str, s, len))));
}

/**
 * _unsetenv - Unsets the specified environment variable
 * @args: Arugements structure
 * Return: 1 on success
 */
int _unsetenv(arguments *args)
{
	list *tmp, *prev = NULL;

	if (!args->tokarr[1])
	{
		errno = ENVERR;
		error(args);
		return (1);
	}
	tmp = args->env;
	while (tmp)
	{
		if (envmatch(NULL, tmp, args))
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
 * set_environment - sets specified enviroment variable
 * @env: environment list
 * @name: name of the environment
 * @value: value of the @name
 *
 * Return: 0 on success, otherwise 1
 */
int set_environment(list **env, char *name, char *value)
{
	list *tmp, *prev = NULL;
	char buf[PATH_MAX] = {0};

	tmp = *env;
	while (tmp)
	{
		if (envmatch(name, tmp, NULL))
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
		if (!tmp)
			return (1);
		tmp->next = NULL;
	}
	if (prev)
		prev->next = tmp;
	else if (!*env)
		*env = tmp;
	tmp->str = _strdup(buf);
	if (!tmp->str)
		return (1);
	return (0);
}


/**
 * _setenv - sets specified enviroment variable
 * @args: arguments structure
 *
 * Return: 0 on success, otherwise 1
 */
int _setenv(arguments *args)
{
	int stat = 0;

	if (args->tokarr[1] && args->tokarr[2])
	{
		stat = set_environment(&(args->env), args->tokarr[1], args->tokarr[2]);
	}
	else
	{
		stat = 1;
		errno = ENVERR;
		error(args);
	}
	return (stat);
}

/**
 * parsecd - parses through cd command
 * @args: arguments structure
 *
 * Return: 0 on success, otherwise 1
 */
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
