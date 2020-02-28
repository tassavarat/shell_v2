#include "shell.h"

/**
 * write_pipe - write to the pipe
 * @args: arguments struct
 * @lineptr: input string
 * @fd: duplicated STDIN and STDOUT
 * @operator: operator flag
 */
void write_pipe(arguments *args, char *lineptr, int *fd, char *operator)
{
	args->pstat = 1;
	*operator = 'p';
	if (pipe(args->pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	fd[1] = dup(STDOUT_FILENO);
	dup2(args->pipefd[1], STDOUT_FILENO);
	shell_run(args, lineptr);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

/**
 * chain_pipe - write to the pipe
 * @args: arguments struct
 * @lineptr: input string
 * @fd: duplicated STDIN and STDOUT
 * @operator: operator flag
 * @pstat: tells which end of pipe to clean
 */
void chain_pipe(arguments *args, char *lineptr,
		int *fd, char *operator, int pstat)
{
	fd[0] = dup(STDIN_FILENO);
	dup2(args->pipefd[0], STDIN_FILENO);

	if (pstat)
	{
		close(args->pipefd[0]);
		write_pipe(args, lineptr, fd, operator);
	}
	else
	{
		args->pstat = 0;
		shell_run(args, lineptr);
	}

	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}
