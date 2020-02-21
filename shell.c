#include "shell.h"

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
 * pprompt - prints prompt
 * @args: arguments structure
 */
void pprompt(arguments *args)
{
	(void) args;

	if (isatty(STDIN_FILENO))
	{
		printf("hsh$ ");
		args->exitstr = "\n";
	}
}


void shell_run(arguments *args, char *lineptr)
{
	args->tokarr = tokenise(lineptr);
	if (!args->tokarr)
		return;
	if (builtins(args) == 2)
		create_process(args);
	cleanup(args, 'L');
}

void parse_operators(arguments *args, char *lineptr)
{
	char dquote, squote, operator;
	size_t i, line_pos = 0;

	squote = dquote = 0;
	operator = ';';
	for (i = 0; lineptr[i]; ++i)
	{
		/* Handling escape character  echo "\"Timmy\""  */
		squote = lineptr[i] == '\'' && (i == 0 || lineptr[i - 1] != '\\') ? ~squote : squote;
		dquote = lineptr[i] == '"' && (i == 0 || lineptr[i - 1] != '\\') ? ~dquote : dquote;
		if (!squote && !dquote)
		{
			if (lineptr[i] == '#' && (i == 0 || lineptr[i - 1] == ' '))
			{
				lineptr[i] = '\0'; /* This handles the comments*/
				shell_run(args, lineptr + line_pos);
				return;
			}
			if (lineptr[i] == ';')
			{
				lineptr[i] = '\0';
				if (operator == ';' || (operator == '&' && !args->exit_status)
				    || (operator == '|' && args->exit_status))
					shell_run(args, lineptr + line_pos);
				    line_pos = ++i;
			}
			else if (lineptr[i] == '&')
			{
				if (lineptr[i + 1] == '&') /* if you hit the first &*/
				{
					lineptr[i] = '\0';
					if (operator == ';' || (operator == '&' && !args->exit_status)
					    || (operator == '|' && args->exit_status))
						shell_run(args, lineptr + line_pos);
					line_pos = i + 1;
				}
				else if (i != 0 && lineptr[i - 1] == '\0') /*if you hit second &*/
				{
					operator = '&';
					line_pos = i + 1;
				}
			}
			else if (lineptr[i] == '|')
			{
				if (lineptr[i + 1] == '|') /* if you hit the first &*/
				{
					lineptr[i] = '\0';
					if (operator == ';' || (operator == '&' && !args->exit_status)
					    || (operator == '|' && args->exit_status))
						shell_run(args, lineptr + line_pos);
					line_pos = i + 1;
				}
				else if (i != 0 && lineptr[i - 1] == '\0') /*if you hit second &*/
				{
					operator = '|';
					line_pos = i + 1;
				}
			}
		}
	}
	if (operator == ';' || (operator == '&' && !args->exit_status)
	    || (operator == '|' && args->exit_status))
		shell_run(args, lineptr + line_pos); /* Default behaviour */
}

/**
 * shell - gets input and calls relevant functions to parse
 * @args: arguments structure
 */
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
			printf("%s", args->exitstr);
			free(lineptr);
			return;
		}
		++args->cmdnum;
		parse_operators(args, lineptr);
	}
}

/**
 * initparam - initialises arguments structure
 * @args: arguments structure to initialise
 * @ac: number of arguments
 * @av: arguments passed
 */
void initparam(arguments *args, const int ac, char **av)
{
	args->ac = ac;
	args->av = av;
	args->exitstr = "";
	args->tokarr = NULL;
	args->env = envlist();
	args->exit_status = 0;
	args->cmdnum = 0;
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

	initparam(&args, ac, av);
	shell(&args);
	cleanup(&args, '\0');
	return (args.exit_status);
}
