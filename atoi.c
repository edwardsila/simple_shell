#include "shell.h"

/**
 * isShellInteractive - Determine if the shell is in interactive mode.
 * @shellInfo: A structure containing shell information.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */

int isShellInteractive(info_t *shellInfo)
{
	return (isTerminal(STDIN_FILENO) && shellInfo->readDescriptor <= 2);
}

/**
 * isCharDelim - Check if a character is a delimiter.
 * @character: The character to check.
 * @delimStr: The string of delimiters to compare against.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */

int isCharDelim(char character, char *delimStr)
{
	while (*delimStr)
	{
		if (*delimStr++ == character)
			return (1); /* Character is a delimeter */
	}
	return (0); /* character not a delim */
}

/**
 * isalpha - checks for alphabetic char
 * @c: character
 * Return: 1 if c is an alphabet, 0 otherwise
 */

int isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * strToInt - Convert a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 if no numbers in string, the converted number otherwise.
 */

int strToInt(char *str)
{
	int i;

	sign = 1;
	flag = 0;
	result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}
	if (sign == -1)
		return (-result);
	else
		return (result);
}
