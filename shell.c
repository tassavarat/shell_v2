#include "shell.h"

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

/**
 * pprompt - prints prompt
 * @args: arguments structure
 */
void pprompt(arguments *args)
{
	(void) args;

	if (isatty(STDIN_FILENO))
	{
		fprintf(stderr, "$ ");
		args->exitstr = "\n";
	}
}

/**
 * initparam - initialises arguments structure
 * @args: arguments structure to initialise
 * @ac: number of arguments
 * @av: arguments passed
 */
int initparam(arguments *args, const int ac, char **av)
{
	args->ac = ac;
	args->av = av;
	args->exitstr = "";
	args->tokarr = NULL;
	args->env = envlist();
	if (!args->env)
	{
		args->exit_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	args->exit_status = EXIT_SUCCESS;
	args->cmdnum = 1;
	args->errstr = "";
	return (EXIT_SUCCESS);
}
