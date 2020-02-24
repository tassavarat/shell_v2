#include "shell.h"

/**
 * checkerr - Check for syntax errors, helper function
 * @stat: status flag
 * @errs: error string
 * @i: postion of pointer in input string
 * @incr: increment @i based on this value
 */
void checkerr(int *stat, char *errs, size_t *i, int incr)
{
	printf("syntax error %s\n", errs);
	*stat = 1;
	if (incr)
		++*i;
}

/* int checkchar(char *s, size_t *i) */
/* { */
/*	static char notspace = 0; */
/*	int stat = 0; */

/*	if (s[0] == '|' &&  s[1] == '|') */
/*	{ */
/*		if (!notspace) */
/*		{ */
/*			s[2] = '\0'; */
/*			checkerr(&stat, s, i, 1); */
/*			/\* */
/*			printf("syntax error %s\n", s); */
/*			stat = 1; */
/*			*\/ */
/*		} */
/*		notspace = 0; */
/*		/\* */
/*		++i; */
/*		*\/ */
/*	} */
/*	else if (s[0] == '&') */
/*	{ */
/*		if (!notspace || s[1] != '&') */
/*		{ */
/*			s[1] = '\0'; */
/*			checkerr(&stat, s, i, 1); */
/*			/\* */
/*			printf("syntax error %s\n", s); */
/*			stat = 1; */
/*			*\/ */
/*		} */
/*		notspace = 0; */
/*		/\* */
/*		++i; */
/*		*\/ */
/*	} */
/*	else if (s[0] == ';' || s[0] == '|') */
/*	{ */
/*		if (!notspace) */
/*		{ */
/*			checkerr(&stat, s, i, 0); */
/*			s[1] = '\0'; */
/*			/\* */
/*			printf("syntax error %s\n", s); */
/*			stat = 1; */
/*			*\/ */
/*		} */
/*		notspace = 0; */
/*	} */
/*	else if (s[0] != ' ' && s[0] != '\t' ) */
/*	{ */
/*		notspace = 1; */
/*	} */
/*	return (stat); */
/* } */

/**
 * syntaxerr - main syntax check function
 * @lineptr: input sting
 * Return: 1 if there is an syntax error, 0 otherwise
 */
int syntaxerr(char *lineptr)
{
	char dquote, squote;
	size_t i;

	squote = dquote = 0;
	for (i = 0; lineptr[i]; ++i)
	{
		squote = lineptr[i] == '\'' && (i == 0 ||
				lineptr[i - 1] != '\\') ? ~squote : squote;
		dquote = lineptr[i] == '"' && (i == 0 ||
				lineptr[i - 1] != '\\') ? ~dquote : dquote;
		/* if (!squote && !dquote && */
		/*		checkchar(lineptr + i, &i)) */
		/*	return (1); */
	}
	return (0);
}

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
		perror(NULL);
		args->exit_status = 126;
	}
	else if (errno == ENOENT)
	{
		fprintf(stderr, "%s: not found\n", *args->tokarr);
		args->exit_status = 127;
	}
	else
		perror(NULL);
}

/**
 * cleanup - performs relevant cleanup for arguments structure
 * @args: arguments structure
 * @mode: if there is tokenised array to free
 */
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

/**
 * wordcount - counts number of words
 * @lineptr: string to parse
 *
 * Return: number of words
 */
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
