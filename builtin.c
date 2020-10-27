#include "shell.h"

/**
 * help3 - displays information about builtin commands
 * @help_num: determines which help information to print
 */
void help3(int help_num)
{
	if (help_num == 0)
	{
		_puts("help: clear\n"
				"    Clear the terminal screen\n\n"
				"    Clears your screen if this is possible, including its scrollback buffer\n"
				"    (if the extended “E3” capability is defined).  clear looks in the environment\n"
				"    for the terminal type given by the environment variable TERM, and then in the\n"
				"    terminfo database to determine how to clear the screen.\n");
	}
	else if (help_num == 1)
	{
		_puts("help: [alias-name[=string]...]\n"
				"    Define or display aliases\n\n"
				"    The alias utility shall create or redefine alias definitions or write the values\n"
				"    of existing alias definitions to standard output. An  alias  definition  provides\n"
				"    a string value that shall replace a command name when it is encountered\n");
	}
}

/**
 * help2 - display information about builtin commands
 * @args: arguments structure
 */
void help2(arguments *args)
{
	if (!_strcmp(args->tokarr[1], "env"))
		_puts("env\n"
				"    Prints the full environment\n");
	else if (!_strcmp(args->tokarr[1], "exit"))
		_puts("exit: exit [n]\n"
				"    Exit the shell.\n\n"
				"    Exits the shell with a status of N. If N is omitted, the exit status\n"
				"    is that of the last command executed.\n");
	else if (!_strcmp(args->tokarr[1], "cd"))
		_puts("cd: cd [dir]\n"
				"    Change the shell working directory.\n\n"
				"    Change the current directory to DIR. The default DIR is the value of the\n"
				"    HOME shell variable.\n");
	else if (!_strcmp(args->tokarr[1], "unsetenv"))
		_puts("unsetenv: unsetenv [name]\n"
				"    Remove an environmental variable.\n\n"
				"    Deletes the variable name from the enviroment. If the name does not\n"
				"    exist in the enviromnent, then the builtin succeeds, and the\n"
				"    environment is unchanged\n");
	else if (!_strcmp(args->tokarr[1], "setenv"))
		_puts("setenv: setenv [name] [value] [overwrite]\n"
				"    Change or add an environmental variable.\n\n"
				"    Adds the variable name to the environment with the value value, if name\n"
				"    does not already exist. If name does exist in the environment, then it's\n"
				"    value is changed to value if overwrite is nonzero; if overwrite is zero,\n"
				"    then the value of name is not changed.\n");
	else if (!_strcmp(args->tokarr[1], "help"))
		_puts("help: help [pattern...]\n"
				"    Displays brief summaries of builtin commands.\n\n"
				"    If PATTERN is specified, give detailed help on all commands matching PATTERN,\n"
				"    otherwise the list if help topics is printed.\n");
	else if (!_strcmp(args->tokarr[1], "clear"))
		help3(0);
	else if (!_strcmp(args->tokarr[1], "alias"))
		help3(1);
	else
		error(args);
}

/**
 * help - display information about builtin commands
 * @args: arguments structure
 *
 * Return: 0
 */
int help(arguments *args)
{
	if (args->tokarr[1])
	{
		help2(args);
	}
	else
	{
		_puts("Type 'help name' to find out more about the function 'name'.\n\n"
				"env\nexit [n]\ncd [dir]\nunsetenv [name]\n"
				"setenv [name]\nhelp [pattern...]\nclear\n"
				"alias [name[=value] ... ]\n");
	}
	return (0);
}

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
 * Return: 0 on success, 1 on error
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
		/* printf("%s\n", tmp); FIXME: printf*/
		_puts(tmp);
		_puts("\n");
		free(tmp);
	}
	else
		val = chdir(args->tokarr[1]);
	return (val);
}

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
		{"alias", alias},
		{"history", history},
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
