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

/**
 * convert - Function that converts our int to hex, octal, or binary
 * @num: Number passed into the function
 * @base: Base to convert to
 *
 * Return: Converted number of a certain base
 */
char *convert(unsigned int num, int base)
{
	char rep[] = "0123456789ABCDEF";
	static char buffer[11];
	char *ptr;

	ptr = &buffer[10];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);
	return (ptr);
}
