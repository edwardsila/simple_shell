#include "shell.h"

/**
 * list_length - Determine the length of a linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */

size_t list_length(const list_t *h)
{
	size_t size = 0;

	while (h)
	{
		h = h->next;
		size++;
	}
	return  (size);
}

/**
 * list_to_string_arr - Convert a linked list to an array of strings.
 * @head: Pointer to the first node.
 * Return: Array of strings.
 */

char **list_to_string_arr(list_t *head)
{
	list_t *node = head;
	size_t size = list_length(head), i;
	char **strings;
	char *str;

	if (!head || !size)
		return (NULL);
	strings = malloc(sizeof(char *) * (size + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * print_list - Print all elements of a linked list.
 * @h: Pointer to the first node.
 * Return: Size of the list.
 */

size_t print_list(const list_t *h)
{
	size_t size = 0;

	while (h)
	{
		_puts(convert_number_to_str(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		size++;
	}
	return (size);
}
/**
 * find_node_with_pfx - Find a node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @pfx: String to match.
 * @c: The next character.
 * Return: Matching node or NULL.
 */

list_t *find_node_with_pfx(list_t *node, char *pfx, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startWith(node->str, pfx);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Get the index of a node in the linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 * Return: Index of the node or -1 if not found.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
