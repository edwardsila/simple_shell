#include "shell.h"

/**
 * _strlen - returns length of a string.
 * @s: string.
 * Return: length of string
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s++)
		len++;
	return (len);
}

/**
 * _strcmp - compares two strings.
 * @str1: string1.
 * @str2: string2
 * Return: - for (st1 < str2), + if (str1 > str2), 0 if (str1 == str2).
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * startWith - checks if needle starts with stack
 * @stack: string
 * @c: the substring to find
 * Return: address of next char of stack or NULL
 */

char *startWith(const char *stack, const char *c)
{
	while (*c)
		if (*c++ != *stack++)
			return (NULL);
	return ((char *)stack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: c.
 */

char *_strcat(char *dest, char *src)
{
	char *c = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (c);
}

