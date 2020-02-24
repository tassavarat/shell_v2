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
 * is_digit - checks if char @n is digit
 * @n: character
 * Return: 1 if @n is digit, 0 if not
 */
int is_digit(char n)
{
	return (n >= '0' && n <= '9' ? 1 : 0);
}

/**
 * check_redirection - handles redirections
 * @args: arguments
 * @lineptr: input string
 * @fds: file descriptors
 */
void check_redirection(arguments *args, char *lineptr, int *fds)
{
	char quote = 0;
	size_t i;
	int flags = O_RDWR | O_CREAT;
	char *file;

	(void) args;
	for (i = 0; lineptr[i]; ++i)
	{
		if (no_quote(lineptr, i, &quote))
		{
			/* TODO: Handle ls; ls >> error */
			if (lineptr[i] == '>')
			{
				if (i != 0 && is_digit(lineptr[i - 1]))
				{
					fds[2] = lineptr[i - 1] - '0';
					lineptr[i - 1] = '\0';
				}
				lineptr[i++] = '\0';
				if (lineptr[i] == '>')
					++i, flags |= O_APPEND;
				file = strtok(lineptr + i, " \n");
				fds[0] = open(file, flags, 0664);
				fds[1] = dup(fds[2]);
				break;
			}
		}
	}
}

/**
 * shell_run - calls relevant functions to parse
 * @args: arguments structure
 * @lineptr: input string
 */
void shell_run(arguments *args, char *lineptr)
{
	int fds[3] = {-2, -2, STDOUT_FILENO};

	check_redirection(args, lineptr, fds);
	if (fds[0] != -2 && fds[1] != -2 && (fds[0] == -1 || fds[1] == -1
					 || dup2(fds[0], fds[2]) == -1))
	{
		if (fds[0] != -1)
			close(fds[0]);
		error(args);
		free(lineptr);
		return;
	}

	args->tokarr = tokenise(lineptr);
	if (!args->tokarr)
		return;
	if (builtins(args) == 2)
		create_process(args);
	cleanup(args, 'L');
	if (fds[0] != -2)
	{
		if (dup2(fds[1], fds[2]) == -1)
			error(args);
		close(fds[0]);
	}
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
 * parse_operators - parses logical operators
 * Description:
 * @args: arguments struct
 * @lineptr: input string
 */
void parse_operators(arguments *args, char *lineptr)
{
	char quote = 0, operator = ';';
	size_t i, line_pos = 0;

	for (i = 0; lineptr[i]; ++i)
	{
		if (no_quote(lineptr, i, &quote))
		{
			if (is_comment(lineptr, i))
				break;
			if ((lineptr[i] == '&' || lineptr[i] == '|')
			    && i != 0 && lineptr[i - 1] == '\0')
			{
				operator = lineptr[i]; /*Handles second & or | */
				line_pos = i + 1;
			}
			else if (lineptr[i] == ';' ||
				 !_strncmp(lineptr + i, "&&", 2) ||
				 !_strncmp(lineptr + i, "||", 2))
			{
				lineptr[i] = '\0';
				if (operator == ';' || (operator == '&' && !args->exit_status)
				    || (operator == '|' && args->exit_status))
					shell_run(args, lineptr + line_pos);
				line_pos = i + 1;
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
		if (byterd == EOF || syntaxerr(lineptr))
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
	args->cmdnum = 1;
	args->errstr = "";
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
