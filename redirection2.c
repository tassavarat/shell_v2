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
	ssize_t read_size;
	size_t s = 0;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		error(args);
		return (NULL);
	}
	while (1)
	{
		pprompt(args, ">");
		read_size = getline(&buf, &s, stdin);
		if ((read_size == -1 || read_size == 0) ||
		    (!_strncmp(buf, term_char, _strlen(term_char)) &&
		     _strlen(term_char) == _strlen(buf) - 1))
			break;
		write(fd, buf, read_size);
	}
	free(buf);
	close(fd);
	return (file);
}

/**
 * var_expansion - Looks for variables in the current
 * environmental  * variables
 * @args: An array of tokenized commands
 */
void var_expansion(arguments *args)
{
	int i = 0, j = 0, flag = 0, len = 0;
	static char *n = "Hello";

	while ((args->tokarr)[i])
	{

		if (*((args->tokarr))[i] == '$')
		{
			flag = 1;
			break;
		}
		i++;
	}
	if (flag)
	{
		((args->tokarr))[i]++;
		len = _strlen(((args->tokarr))[i]);
		while (environ[j])
		{
			if (!_strncmp(((args->tokarr))[i], environ[j], len))
			{
				((args->tokarr))[i] = environ[j] + len + 1;
				break;
			}
			j++;
		}
	}
	else if (flag && !_strcmp(args->tokarr[i], "?"))
	{
		args->tokarr[i] = n;
	}
}
