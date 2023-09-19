#include "shell.h"

/**
 * _memset - Fills memory with a constant byte.
 * @s: The pointer to the memory area.
 * @c: The byte to fill *s with.
 * @n: The amount of bytes to be filled.
 * Return: A pointer to the memory area s.
 */

char *_memset(char *s, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = c;
	return (s);
}

/**
 * free_string_array - Frees an array of strings and the array itself.
 * @str_arr: The array of strings.
 */

void free_string_array(char **str_arr)
{
	char **arr = str_arr;

	if (!str_arr)
		return;

	while (*str_arr)
		freee(*str_arr++);

	free(arr);
}

/**
 * _realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the reallocated block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *c;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		c[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (p);
}
