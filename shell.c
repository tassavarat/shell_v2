#include "shell.h"

/**
 * error - display errors
 * @args: command from user
 */
void error(arguments *args)
{
	fprintf(stderr, "%s: %lu: ", *args->av, args->cmdnum);
	if (errno == EXITERR)
	{
		fprintf(stderr, "%s: Illegal number: %s\n", *args->tokarr,
				args->tokarr[1]);
		args->exit_status = 2;
	}
	else if (errno == CDERR)
	{
		fprintf(stderr, "%s: can't cd to %s\n", *args->tokarr,
				args->tokarr[1]);
		args->exit_status = 2;
	}
	else if (errno == EACCES)
	{
		perror("cannot create file");
		args->exit_status = 126;
	}
	else if (errno == ENOENT)
	{
		fprintf(stderr, "%s: not found\n", *args->tokarr);
		args->exit_status = 127;
	}
	else if (errno == ENVERR)
	{
		fprintf(stderr, "%s: invalid argument(s)\n", *args->tokarr);
		args->exit_status = 2;
	}
	else
		perror(NULL);
}

/**
 * pprompt - prints prompt
 * @args: arguments structure
 * @prompt: specifies what prompt to print
 */
void pprompt(arguments *args, char *prompt)
{
	if (isatty(STDIN_FILENO) && !args->fd)
	{
		fprintf(stderr, "%s ", prompt);
		args->exitstr = "\n";
	}
}

/**
 * initparam - initialises arguments structure
 * @args: arguments structure to initialise
 * @ac: number of arguments
 * @av: arguments passed
 *
 * Return: 0 on success, 1 on failure
 */
int initparam(arguments *args, const int ac, char **av)
{
	args->ac = ac;
	args->av = av;
	args->exitstr = "";
	args->tokarr = NULL;
	args->env = envlist();
	args->fd = choose_fd(args);
	if (!args->env || args->fd == -1)
	{
		args->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	args->exit_status = EXIT_SUCCESS;
	args->cmdnum = 1;
	args->errstr = "";
	args->pipefd[0] = 0;
	args->pipefd[1] = 0;
	args->pstat = -1;
	return (EXIT_SUCCESS);
}

/**
 * main - entry point
 * @ac: number of arguments
 * @av: arguments passed
 *
 * Return: exit status
 */
int main(int ac, char *av[])
{
	arguments args;

	if (!initparam(&args, ac, av))
	{
		shell(&args);
		cleanup(&args, '\0');
	}
	return (args.exit_status);
}
