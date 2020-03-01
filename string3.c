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

/**
 * strsrch - locates a character in a string
 * @s: string
 * @c: character
 * @len: the length of @s
 *
 * Return: returns a pointer
 */

char *strsrch(char *s, char c, size_t len)
{
	size_t i = 0;

	for (i = 0; i < len; i++)
	{
		if (s[i] == c)
			return (s + i);
	}
	return (NULL);
}

/**
 * _memcpy - Copies memory area
 * @dest: Area being copied to
 * @src: Area being copied
 * @n: Amount of bytes to be copied
 *
 * Return: Pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
		*(dest + i) = *(src + i);
	return (dest);
}
