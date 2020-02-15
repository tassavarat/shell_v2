#include "shell.h"

/**
 * custom_cd - Changes directory
 * @args: Arguments structure
 *
 * Return: 1 on success
 */
int changedir(arguments *args)
{
	char *cwd = NULL, *temp = NULL;
	char *oldwd = NULL;
	int val = 0;
	char *home = _getenv("HOME=", args);

	oldwd = getcwd(oldwd, 0);
	if (args->arr[1] == NULL)
	{
		val = chdir(home ? home : oldwd);
	}
	else if (*args->arr[1] == '-')
	{
		val = chdir(_getenv("OLDPWD=", args) ? _getenv("OLDPWD=", args) : oldwd);
		_puts(getcwd(temp, 0)), _puts("\n"), free(temp);
	}
	else
		val = chdir(args->arr[1]);
	if (val == -1)
	{
		errno = NOTDIR;
		error(args, 3);
	}
	if (1)
	{
		args->arr[1] = "OLDPWD", args->arr[2] = oldwd;
		_setenv(args);
		args->arr[1] = "PWD", args->arr[2] = cwd = getcwd(cwd, 0);
		_setenv(args);
		free(cwd);
	}
	free(oldwd);
	return (1);
}

int builtins(arguments *args)
{
	size_t i;
	built_ins func_arr[] = {
		{"cd", changedir},
		{"env", penv},
		{"exit", callexit},
		(NULL, NULL)
	};

	for (i = 0; func_arr[i].bi; ++i)
		if (!_strcmp(*args->tokarr, func_arr[i].bi))
			return (func_arr[i].f(args));
	return (0);
}

