#include "shell.h"

/**
 * heredoc - heredoc functionality
 * @args: arguments
 * @lineptr: input sting
 * @i: pos at @lineptr
 * Return: temp file
 */
char *heredoc(arguments *args, char *lineptr, size_t i)
{
	char *buf = NULL;
	static char *file = "/tmp/tmp_file.txt";
	char *term_char = strtok(lineptr + i + 1, " \t\n");
	int fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		error(args);
		return (NULL);
	}
	while (1)
	{
		pprompt(args, ">");
		buf = _getline(0);
		if ((!buf) ||
		    (!_strncmp(buf, term_char, _strlen(term_char)) &&
		     _strlen(term_char) == _strlen(buf)))
			break;
		write(fd, buf, _strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (file);
}

/* char *heredoc(arguments *args, char *lineptr, size_t i) */
/* { */
/*	char *buf = NULL; */
/*	static char *file = "/tmp/tmp_file.txt"; */
/*	char *term_char = strtok(lineptr + i + 1, " \t\n"); */
/*	int fd; */
/*	ssize_t read_size; */
/*	size_t s = 0; */

/*	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666); */
/*	if (fd == -1) */
/*	{ */
/*		error(args); */
/*		return (NULL); */
/*	} */
/*	while (1) */
/*	{ */
/*		pprompt(args, ">"); */
/*		read_size = getline(&buf, &s, stdin); */
/*		if ((read_size == -1 || read_size == 0) || */
/*		    (!_strncmp(buf, term_char, _strlen(term_char)) && */
/*		     _strlen(term_char) == _strlen(buf) - 1)) */
/*			break; */
/*		write(fd, buf, read_size); */
/*	} */
/*	free(buf); */
/*	close(fd); */
/*	return (file); */
/* } */
