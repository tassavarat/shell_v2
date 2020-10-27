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

/**
 * _atoi - converts string to an integer
 * @s: takes string
 *
 * Return: if number negative or not number return -1
 */
int _atoi(char *s)
{
	size_t i;
	size_t n = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i]; ++i)
	{
		if (s[i] >= '0' && s[i] <= '9')
			n = n * 10 + (s[i] - '0');
		else
			return (-1);
	}
	if (n > INT_MAX)
		return (-1);
	return (n);
}

/**
 * _strdup - duplicates a string
 * @str: string
 *
 * Return: a pointer to the string
 */
char *_strdup(const char *str)
{
	char *s;
	int i = 0;

	if (str == NULL)
		return (NULL);
	while (str[i])
		i++;
	s = malloc(sizeof(char) * i + 1);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = '\0';
	return (s);
}

/**
 * _strlen - Calculates length of a string
 * @str: String being evaluated
 *
 * Return: length of string
 */
size_t _strlen(char *str)
{
	size_t i = 0;

	while (*(str + i))
		++i;
	return (i);
}

/**
 * _strncmp - Compares two strings at most n bytes
 * @s1: First string being evaluated
 * @s2: Second string being evaluated
 * @n: Amount of bytes to be evaluated
 *
 * Return: Difference between string characters being evaluated
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
			++i;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: positive or negative value whether p1 or p2 are greater
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return (s1[i] - s2[i]);
}
