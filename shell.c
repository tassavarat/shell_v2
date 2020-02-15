#include "shell.h"

size_t wordcount(char *lineptr)
{
	size_t i, wc, word;

	wc = word = 0;
	for(i = 0; lineptr[i]; ++i)
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
		free(args->tokarr);
	}
}

void initparam(arguments *args, const int ac, char **av)
{
	args->ac = ac;
	args->av = av;
	args->exitchr = '\0';
	args->tokarr = NULL;
}

int main(int ac, char *av[])
{
	arguments args;
	initparam(&args, ac, av);
	shell(&args);
	return (EXIT_SUCCESS);
}
