#include "shell.h"

/**
 * _strncpy - copies string
 * @dest: takes string
 * @src: takes string
 * @n: takes number of bytes
 *
 * Return: pointer to dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

/**
 * _memset - Fills memory with constant byte
 * @s: Array being filled
 * @b: Constant byte
 * @n: Amount of array elements to be filled with b
 *
 * Return: Filled buffer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
		s[i] = b;
	return (s);
}

/**
 * get_path - Process
 * @args: Arugements structure
 * Return: Nothing
 */
char *split_path(char *str)
{
	static char *path;
	char *dir;
	static size_t cur_pos;
	size_t new_pos;

	if (str)
	{
		cur_pos = 0;
		path = str;
	}
	if (!path || !*(path + cur_pos))
		return (NULL);
	for (new_pos = cur_pos; *(path + new_pos)
		     && *(path + new_pos) != ':'; ++new_pos);
	dir = malloc(sizeof(char) * (new_pos - cur_pos + 1));
	_strncpy(dir, path + cur_pos, new_pos - cur_pos);
	dir[new_pos - cur_pos] = '\0';
	cur_pos = *(path + new_pos) ? ++new_pos : new_pos;
	return (dir);
}

/**
 * get_path - Process
 * @args: Arugements structure
 * Return: Nothing
 */
char *get_path(arguments *args)
{
	char *path = _getenv("PATH=", args), *token, *delimiter;
	static char buf[PATH_MAX];

	if (!path)
		return (NULL);
	for (token = split_path(path); token; token = split_path(NULL))
	{
		delimiter = *token ? "/" : "./";
		sprintf(buf, "%s%s%s", token, delimiter, args->tokarr[0]);
		free(token);
		if (!access(buf, F_OK))
			return (buf);
	}
	return (NULL);
}


/**
 * _fork - Fork a process
 * @args: Arugements structure
 * @exec: Executable
 * Return: Nothing
 */
void _fork(arguments *args, char *exec)
{
	pid_t pid = 0;
	int wstatus;

	pid = fork();
	if (pid < 0)
	{

		error(args);
	}
	else if (pid == 0)
	{
		if (execve(exec, args->tokarr, NULL))
		{
			error(args);
			exit(errno);
		}
	}
	else
	{

		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus))
			args->exit_status = WEXITSTATUS(wstatus);
	}
}


/**
 * create_process - Process
 * @args: Arugements structure
 * Return: Nothing
 */
void create_process(arguments *args)
{
	char *exec = NULL;

	/* if (!_strncmp(args->tokarr[0], "./", 2) || **args->tokarr == '/') */
	/* { */
	/* 	exec = args->tokarr[0]; */
	/* } */
	/* else */
	/* { */
	/* 	exec = get_path(args); */
	/* } */
	exec = !_strncmp(args->tokarr[0], "./", 2) || **args->tokarr == '/'
		? args->tokarr[0] : get_path(args);
	if (!exec || access(exec, F_OK))
	{
		errno = ENOENT;
		error(args);
	}
	else if (access(exec, X_OK | R_OK))
	{
		error(args);
	}
	else
	{
		_fork(args, exec);
	}
}
