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
	char buf[BUFSIZ] = {0};
	int fd;
	static char *file = "/tmp/tmp_file.txt";
	char *term_char = strtok(lineptr + i + 1, " \t\n");
	size_t read_size;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		error(args);
		return (NULL);
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		read_size = read(STDIN_FILENO, &buf, BUFSIZ);
		if (!_strncmp(buf, term_char, _strlen(term_char)))
			break;
		write(fd, buf, read_size);
		_memset(buf, 0, BUFSIZ);
	}
	close(fd);
	return (file);
}
