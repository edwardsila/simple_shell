#include "shell.h"
/**
 * _strcpy - copies a str from source to destination.
 * @dest: destination of the string.
 * @src: source of the string.
 * Return: newly copied string.
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string.
 * @str: string to duplicate.
 * Return: duplicated string.
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *c;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	c = malloc(sizeof(char) * (len + 1));
	if (!c)
		return (NULL);
	for (len++; len--;)
		c[len] = *--str;
	return (c);
}

/**
 * _puts - prints a string.
 * @str: string.
 * Return: void
 */

void _puts(char *str)
{
	int i;

	i = 0;
	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}


/**
 * _putchar - writes character c to stdout.
 * @c: character.
 * Return: On success 1. and -1 on error.
 */

int _putchar(char c)
{
	static int i;
	static char buffer[1024];

	if (c == BUF_FLUSH || i >= 1024)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}
