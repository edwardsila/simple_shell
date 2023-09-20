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
	_eputs(errorStr);
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
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * convert_number_to_str - Converts a number to a string representation.
 * @num: Number to convert.
 * @base: Base for conversion.
 * @flag: Conversion flags.
 * Return: String representation of the number.
 */

char *convert_number_to_str(long int num, int base, int flag)
{
	static char *charset;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	charset = flag & CONVERT_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = charset[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - Replaces the first '#' character with '\0'.
 * @str: Pointer to the string to modify.
 * Return: Always 0.
 */

void rm_comments(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '#' && (!i || str[i - 1] == ' '))
		{
			str[i] = '\0';
			break;
		}
}
