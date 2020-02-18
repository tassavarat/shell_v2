#include "shell.h"

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
