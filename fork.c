#include "shell.h"

/**
 * split_path - describe me
 * @str: string
 * Return: dir
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
		     && *(path + new_pos) != ':'; ++new_pos)
		;
	dir = malloc(sizeof(char) * (new_pos - cur_pos + 1));
	if (!dir)
		return (NULL);
	_strncpy(dir, path + cur_pos, new_pos - cur_pos);
	dir[new_pos - cur_pos] = '\0';
	cur_pos = *(path + new_pos) ? ++new_pos : new_pos;
	return (dir);
}

/**
 * get_path - gets the path
 * @args: arguments structure
 * Return: full path on command, otherwise NULL
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
 * forkproc - fork a process
 * @args: arguments structure
 * @exec: executable
 */
void forkproc(arguments *args, char *exec)
{
	pid_t pid = 0;
	int wstatus;
	char **envlist = NULL;

	pid = fork();
	if (pid < 0)
	{
		error(args);
	}
	else if (pid == 0)
	{
		envlist = ltoa(args->env);
		if (args->pipefd[0] != 0)
		{
			close(args->pipefd[0]);
			close(args->pipefd[1]);
		}
		if (execve(exec, args->tokarr, envlist))
		{
			free(envlist);
			error(args);
			exit(errno);
		}
	}
	else
	{
		if (args->pstat == 1)
			close(args->pipefd[1]);
		else if (args->pstat == 0)
			close(args->pipefd[0]);
		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus))
			args->exit_status = WEXITSTATUS(wstatus);
	}
}


/**
 * create_process - creates a process
 * @args: arguments structure
 */
void create_process(arguments *args)
{
	char *exec = NULL;

	exec = ((*args->tokarr)[0] == '.' &&
		((*args->tokarr)[1] == '.' || (*args->tokarr)[1] == '/')) ||
		**args->tokarr == '/'
		? args->tokarr[0] : get_path(args);
	if (!exec || access(exec, F_OK))
	{
		if (args->pstat == 1)
			close(args->pipefd[1]);
		else if (args->pstat == 0)
			close(args->pipefd[0]);
		errno = ENOENT;
		error(args);
	}
	else if (access(exec, X_OK | R_OK))
	{
		if (args->pstat == 1)
			close(args->pipefd[1]);
		else if (args->pstat == 0)
			close(args->pipefd[0]);
		error(args);
	}
	else
	{
		forkproc(args, exec);
	}
}
