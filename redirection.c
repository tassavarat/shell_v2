#include "shell.h"

/**
 * clean_redirection - reverts back redirection
 * @args: arguments struct
 * @fds: file descriptors, fds[3]
 */
void clean_redirection(arguments *args, int *fds)
{
	/* if (dup2(fds[1], fds[2]) == -1) */
	/*	error(args); FIXME: n> error message */
	(void) args;
	dup2(fds[1], fds[2]);
	close(fds[0]);
	unlink("/tmp/tmp_file.txt");
}

/**
 * check_redirect_errs - handles redirections errors
 * @args: arguments
 * @fds: file descriptors
 * @flags: Modes for file opening
 * @file: file to open
 * @is_valid: tells if to throw an error if there is n> redirection
 * @which_redirect: tells which redirection, for error messages
 * Return: -1 if error, 1 if successful
 */
int check_redirect_errs(arguments *args, int *fds, int flags, char *file,
			int is_valid, int which_redirect)
{
	if (!file)
	{
		fprintf(stderr, "%s: %lu: ", *args->av, args->cmdnum);
		fprintf(stderr, "Syntax error: newline unexpected\n");
		args->exit_status = 2;
		return (-1);
	}
	fds[0] = open(file, flags, 0666);
	fds[1] = dup(fds[2]);
	if (fds[0] == -1 || (fds[1] == -1 && !is_valid))
	{
		fprintf(stderr, "%s: %lu: ", *args->av, args->cmdnum);
		if (errno == EACCES || errno == ENOENT)
			fprintf(stderr, "%s %s %s: ", "cannot",
				which_redirect ? "create" : "open", file);
		if (errno == ENOENT && !which_redirect)
			fprintf(stderr, "No such file\n");
		else
			perror(NULL);
		args->exit_status = 2;
		return (-1);
	}
	if (dup2(fds[0], fds[2]) == -1 && !is_valid)
	{
		error(args);
		return (-1);
	}
	return (1);
}

/**
 * stdin_redirection - handles stdin redirections
 * @args: arguments
 * @lineptr: input string
 * @i: position of @lineptr
 * @fds: file descriptors
 * Return: -1 if error, 1 if successful
 */
int stdin_redirection(arguments *args, char *lineptr, size_t i, int *fds)
{
	int flags = O_RDONLY;
	char *file;

	lineptr[i++] = '\0';
	if (lineptr[i] == '<')
		file = heredoc(args, lineptr, i);
	else
		file = strtok(lineptr + i, " \t\n");

	return (check_redirect_errs(args, fds, flags, file, 0, 0));
}

/**
 * stdout_redirection - handles stdout redirections
 * @args: arguments
 * @lineptr: input string
 * @i: position of @lineptr
 * @fds: file descriptors
 * Return: -1 if error, 1 if successful
 */
int stdout_redirection(arguments *args, char *lineptr, size_t i, int *fds)
{
	char *file;
	int flags = O_WRONLY | O_CREAT | O_TRUNC, is_valid = 0;

	if (i != 0 && is_digit(lineptr[i - 1]))
	{
		fds[2] = lineptr[i - 1] - '0';
		lineptr[i - 1] = '\0';
		is_valid = 1;
	}
	lineptr[i++] = '\0';
	if (lineptr[i] == '>')
		++i, flags = (flags & ~O_TRUNC) | O_APPEND;
	file = strtok(lineptr + i, " \t\n");

	return (check_redirect_errs(args, fds, flags, file, is_valid, 1));
}

/**
 * check_redirection - handles redirections
 * @args: arguments
 * @lineptr: input string
 * @fds: file descriptors
 * Return: 0 if there is no redirection, 1 if there is redirection
 * and -1 if there is an error
 */
int check_redirection(arguments *args, char *lineptr, int *fds)
{
	char quote = 0;
	size_t i;

	for (i = 0; lineptr[i]; ++i)
	{
		if (no_quote(lineptr, i, &quote))
		{
			if (lineptr[i] == '>')
			{
				fds[2] = STDOUT_FILENO;
				return (stdout_redirection(args, lineptr, i, fds));
			}
			if (lineptr[i] == '<')
			{
				fds[2] = STDIN_FILENO;
				return (stdin_redirection(args, lineptr, i, fds));
			}
		}
	}
	return (0);
}
