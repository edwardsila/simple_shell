#include "shell.h"

/**
 * _erratoi - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: 0 if no numbers in string, converted number otherwise, -1 on error.
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an error message.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @errorStr: String containing the specified error type.
 * Return: void.
 */

void print_error(shell_info_t *shellInfo, char *errorStr)
{
	_eputs(shellInfo->fname);
	_eputs(":");
	print_d(shellInfo->line_count, STDERR_FILENO);
	_eputs(":");
	_eputs(shellInfo->argv[0]);
	_eputs(":");
	_eputs(estr);
}

/**
 * print_d - Prints an integer to a file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 * Return: Number of characters printed.
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current % = i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}
