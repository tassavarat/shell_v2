#include "shell.h"

/**
 * _strncpy - copies string
 * @dest: takes string
 * @src: takes string
 * @n: takes number of bytes
 *
 * Return: pointer to dest
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[i] = src[i];
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

/**
 * _memset - Fills memory with constant byte
 * @s: Array being filled
 * @b: Constant byte
 * @n: Amount of array elements to be filled with b
 *
 * Return: Filled buffer
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; ++i)
		s[i] = b;
	return (s);
}

/**
 * _strchr - Locates a character in a string
 * @s: String being evaluated
 * @c: Character being checked for
 *
 * Return: Pointer to first occurrence of character
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i++])
		if (s[i] == c)
			return (s + i);
	return (0);
}

/**
 * _strcat - Concatenates two strings
 * @dest: String being passed
 * @src: String being passed
 *
 * Return: Pointer to resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i = _strlen(dest);
	int j = 0;

	while (src[j])
		dest[i++] = src[j++];
	dest[i] = src[j];
	return (dest);
}
