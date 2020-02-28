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
	{
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
			else if (lineptr[i] == '|')
			{
				operator = 'p';
				args->pstat = 1;
				lineptr[i] = '\0';
				if (pipe(args->pipefd) == -1)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
				fd[1] = dup(STDOUT_FILENO);
				dup2(args->pipefd[1], STDOUT_FILENO);
				shell_run(args, lineptr + line_pos);
				dup2(fd[1], STDOUT_FILENO);
				line_pos = i + 1;
			}
			else if (operator == 'p')
			{
				args->pstat = 0;
				fd[0] = dup(STDIN_FILENO);
				dup2(args->pipefd[0], STDIN_FILENO);
				shell_run(args, lineptr + line_pos);
				dup2(fd[0], STDIN_FILENO);
				/* close(fd[0]); */
				/* close(fd[1]); */
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
