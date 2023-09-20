#include "shell.h"

/**
 * strtow - Splits a string into words based on custom delimiters.
 * @input_str: input string.
 * @delim: delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

char **strtow(char *input_str, char *delim)
{
	int idx1, idx2, word_len, idx_word, num_wrds = 0;
	char **result;

	if (input_str == NULL || input_str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (idx1 = 0; input_str[idx1] != '\0'; idx1++)
	{
		if (!isCharDelim(input_str[idx1], delim) &&
			(isCharDelim(input_str[idx1 + 1], delim) || !input_str
			 [idx1 + 1]))
			num_wrds++;
	}
	if (num_wrds == 0)
		return (NULL);
	result = malloc((1 + num_wrds) * sizeof(char *));
	if (!result)
		return (NULL);
	for (idx1 = 0, idx2 = 0; idx2 < num_wrds; idx2++)
	{
		while (isCharDelim(input_str[idx1], delim))
			idx1++;
		word_len = 0;
		while (!isCharDelim(input_str[idx1 + word_len], delim) && input_str
				[idx1 + word_len])
			word_len++;
		result[idx2] = malloc((word_len + 1) * sizeof(char));
		if (!result[idx2])
		{
			for (word_len = 0; word_len < idx2; word_len++)
				free(result[word_len]);
			free(result);
			return (NULL);
		}
		for (idx_word = 0; idx_word < word_len; idx_word++)
			result[idx2][idx_word] = input_str[idx1++];
		result[idx2][idx_word] = 0;
	}
	result[idx2] = NULL;
	return (result);
}
