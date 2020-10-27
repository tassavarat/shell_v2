#include "shell.h"

/**
 * no_quote - checks if operators are outside quotes
 * @lineptr: input string
 * @i: cursor position in @lineptr
 * @quote: bit field
 * Return: 1 if it is safe to parse operator, 0 if it is not
 */
char no_quote(char *lineptr, size_t i, char *quote)
{
	*quote = lineptr[i] == '\'' && (i == 0 || lineptr[i - 1] != '\\') ?
		*quote ^ 1 << 0 : *quote;
	*quote = lineptr[i] == '"' && (i == 0 || lineptr[i - 1] != '\\') ?
		*quote ^ 1 << 1 : *quote;

	return (*quote == 0);
}

/**
 * is_comment - checks if # sign is comment
 * @lineptr: input string
 * @i: cursor position in @lineptr
 * Return: 1 if it is comment, 0 if it is not
 */
int is_comment(char *lineptr, size_t i)
{
	if (lineptr[i] == '#' && (i == 0 || lineptr[i - 1] == ' '))
	{
		lineptr[i] = '\0';
		return (1);
	}
	return (0);
}

/**
 * check_operator - check whether run the command or not
 * @args: arguments struct
 * @operator: tells which operator it is, &&, ||, or ;
 * Return: 1 if the command if allowed to run, 0 otherwise
*/
int check_operator(arguments *args, char operator)
{
	return (operator == ';' || (operator == '&' && !args->exit_status)
		|| (operator == '|' && args->exit_status));
}


/**
 * parse_operators - parses logical operators
 * Description:
 * @args: arguments struct
 * @lineptr: input string
 */
void parse_operators(arguments *args, char *lineptr)
{
	char quote = 0, operator = ';';
	size_t i, line_pos = 0;
	int fd[2];

	for (i = 0; lineptr[i]; ++i)
		if (no_quote(lineptr, i, &quote))
		{
			if (is_comment(lineptr, i))
				break;
			if ((lineptr[i] == '&' || lineptr[i] == '|')
					&& i != 0 && lineptr[i - 1] == '\0')
			{
				operator = lineptr[i]; /* Handles second & or | */
				line_pos = i + 1;
			}
			else if (lineptr[i] == ';' ||
				 !_strncmp(lineptr + i, "&&", 2) ||
					!_strncmp(lineptr + i, "||", 2))
			{
				lineptr[i] = '\0';
				if (check_operator(args, operator))
					shell_run(args, lineptr + line_pos);
				line_pos = i + 1;
			}
			else if (lineptr[i] == '|')
			{
				lineptr[i] = '\0';
				if (args->exit_status && operator == 'p')
					continue;
				operator != 'p'
					? write_pipe(args, lineptr + line_pos, fd, &operator)
					: chain_pipe(args, lineptr + line_pos, fd, &operator, 1);
				line_pos = i + 1;

			}
		}
	if (operator == 'p')
		chain_pipe(args, lineptr + line_pos, fd, &operator, 0);
	else if (check_operator(args, operator))
		shell_run(args, lineptr + line_pos); /* Default behaviour */
}

/**
 * tokenise - tokenises lineptr
 * @lineptr: string to tokenise
 *
 * Return: tokenised string
 */
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
	write_history(args);
	while (args->env)
	{
		tmp = args->env;
		args->env = args->env->next;
		free(tmp->str);
		free(tmp);
	}
	_getline(-1);
	args->env = NULL;
	delalias(args->head);
	free_queue(&args->history);
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
