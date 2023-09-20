#include "shell.h"
/**
 * add_history_node - Adds a history node to the start of the list.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @str: The string field of the node.
 * @num: Node index used by history.
 * Return: Pointer to the new head of the list.
 */

list_t *add_history_node(shell_info_t *shellInfo, const char *str, int num)
{
	list_t *newHead;

	if (!shellInfo)
		return (NULL);

	newHead = malloc(sizeof(list_t));
	if (!newHead)
		return (NULL);

	_memset((void *)newHead, 0, sizeof(list_t));
	newHead->num = num;

	if (str)
	{
		newHead->str = _strdup(str);
		if (!newHead->str)
		{
			free(newHead);
			return (NULL);
		}
	}
	newHead->next = shellInfo->history;
	shellInfo->history = newHead;
	return (newHead);
}

/**
 * add_history_node_end - Adds a history node to the end of the list.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @str: The string field of the node.
 * @num: Node index used by history.
 * Return: Pointer to the new node.
 */

list_t *add_history_node_end(shell_info_t *shellInfo, const char *str, int num)
{
	list_t *newNode, *node;

	if (!shellInfo)
		return (NULL);

	node = shellInfo->history;
	newNode = malloc(sizeof(list_t));

	if (!newNode)
		return (NULL);
	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		shellInfo->history = newNode;
	return (newNode);
}

/**
 * print_history_str - Prints only the str element of a history list.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: The number of nodes printed.
 */

size_t print_history_str(shell_info_t *shellInfo)
{
	list_t *node = shellInfo->history;
	size_t i = 0;

	while (node)
	{
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");
		node = node->next;
		i++;
	}
	return (i);
}


/**
 * delete_hist_node_at_index - Deletes a history node at a given index.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @index: Index of the node to delete.
 * Return: 1 on success, 0 on failure.
 */

int delete_hist_node_at_index(shell_info_t *shellInfo, unsigned int index)
{
	list_t *node = shellInfo->history;
	list_t *prevNode = NULL;
	unsigned int i = 0;

	if (!shellInfo || !shellInfo->history)
		return (0);

	if (!index)
	{
		shellInfo->history = shellInfo->history->next;
		free(node->str);
		free(node);
		return (1);
	}

	while (node)
	{
		if (i == index)
		{
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_hist_list - Frees all nodes of a history list.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: void.
 */

void free_hist_list(shell_info_t *shellInfo)
{
	list_t *node, *nextNode, *head;

	if (!shellInfo || !shellInfo->history)
		return;

	head = shellInfo->history;
	node = head;

	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}
	shellInfo->history = NULL;
}
