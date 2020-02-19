#include "shell.h"

/**
 * error - display errors
 * @args: command from user
 */
void error(arguments *args)
{
	fprintf(stderr, "%s: ", *args->av + 2);
	if (errno == EXITERR)
		fprintf(stderr, "%lu: %s: Illegal number: %s\n", args->cmdnum,
				*args->tokarr, args->tokarr[1]);
	else if (errno == CDERR)
		fprintf(stderr, "%lu: %s: can't cd to %s\n", args->cmdnum,
				*args->tokarr, args->tokarr[1]);
}

void cleanup(arguments *args, char mode)
{
	list *tmp;

	if (mode == 'L')
	{
		free(args->tokarr);
		args->tokarr = NULL;
		return;
	}
	if (args->tokarr)
		free(*args->tokarr);
	free(args->tokarr);
	args->tokarr = NULL;
	while (args->env)
	{
		tmp = args->env;
		args->env = args->env->next;
		free(tmp->str);
		free(tmp);
	}
	args->env = NULL;
}

size_t wordcount(char *lineptr)
{
	size_t i, wc, word;

	wc = word = 0;
	for (i = 0; lineptr[i]; ++i)
	{
		if (!word && lineptr[i] != ' ')
		{
			word = 1;
			++wc;
		}
		else if (word && lineptr[i] == ' ')
		{
			word = 0;
		}
	}
	return (wc);
}

char **tokenise(char *lineptr)
{
	char *token;
	char **arr;
	size_t wc, i = 0;

	wc = wordcount(lineptr);
	arr = malloc(sizeof(*arr) * (wc + 1));
	if (!arr)
		return (NULL);
	token = strtok(lineptr, " \t\n");
	for (i = 0; token; ++i)
	{
		arr[i] = token;
		token = strtok(NULL, " \t\n");
	}
	arr[i] = NULL;
	if (!i)
	{
		free(arr);
		arr = NULL;
	}
	return (arr);
}

void pprompt(arguments *args)
{
	(void) args;

	if (isatty(STDIN_FILENO))
	{
		printf("hsh$ ");
		args->exitchr = '\n';
	}
}

void shell(arguments *args)
{
	char *lineptr = NULL;
	size_t n;
	ssize_t byterd = 0;

	while (1)
	{
		pprompt(args);
		byterd = getline(&lineptr, &n, stdin);
		if (byterd == EOF)
		{
			printf("%c", args->exitchr);
			free(lineptr);
			return;
		}
		args->tokarr = tokenise(lineptr);
		if (!args->tokarr)
			continue;
		/* 0 success, 1 fail, 2 no built-in found */
		if (builtins(args) == 2)
			printf("Call fork here\n");
		cleanup(args, 'L');
		++args->cmdnum;
	}
}

void initparam(arguments *args, const int ac, char **av)
{
	args->ac = ac;
	args->av = av;
	args->exitchr = '\0';
	args->tokarr = NULL;
	args->env = envlist();
	args->exit_status = 0;
	args->cmdnum = 1;
}

int main(int ac, char *av[])
{
	arguments args;

	initparam(&args, ac, av);
	shell(&args);
	cleanup(&args, '\0');
	return (EXIT_SUCCESS);
}
