#include "shell.h"
#define WR_BUF_SZ 1024

/**
 * _eputs - prints a string
 * @str: pointer to the string
 * Return: Nothing
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - inputs character c
 * @c: character to output
 * Return: 1 on succes, o otherwise
 */

int _eputchar(char c)
{
	static int i;
	static char buffer[WR_BUF_SZ];

	if (c == -1 || i >= WR_BUF_SZ)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != -1)
		buffer[i++] = c;
	return (1);
}

/**
 * _putFileDp - writes c to filedescriptor
 * @c: character
 * @filedescriptor: filedescriptor.
 * Return: 1 on success && -1 otherwise
 */

int _putFileDp(char c, int filedescriptor)
{
	static int i;
	static char buffer[WR_BUF_SZ];

	if (c == -1 || i >= WR_BUF_SZ)
	{
		write(filedescriptor, buffer, i);
		i = 0;
	}
	if (c != -1)
		buffer[i++] = c;
	return (1);
}

/**
 * _putsFileDp - prints a string.
 * @str: string
 * @filedescriptor: fd
 * Return: i
 */

int _putsFileDp(char *str, int filedescriptor)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i += _putFileDp(*str++, filedescriptor);
	}
	return (i);
}
