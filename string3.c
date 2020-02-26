#include "shell.h"

/**
 * _puts - prints a string with newline
 * @str: the string to print
 *
 * Return: number of chars written
 */
int _puts(char *str)
{
	size_t i = _strlen(str);

	write(1, str, i);
	return (i);
}
