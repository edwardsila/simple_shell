#include "shell.h"

/**
 * displayShellHist - Displays the command history with line numbers.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always returns 0.
 */

int displayShellHist(shell_info_t *shellInfo)
{
	print_list(shellInfo->history);
	return (0);
}

/**
 * rmShellAlias - Unsets an alias for a command.
 * @shellInfo: Parameter structure.
 * @aliasStr: The string representing the alias.
 * Return: Returns 0 on success, 1 on error.
 */

int rmShellAlias(shell_info_t *shellInfo, char *aliasStr)
{
	char *aliasAssignment, tempChar;
	int result;

	aliasAssignment = _strchr(aliasStr, '=');
	if (!aliasAssignment)
		return (1);
	tempChar = *aliasAssignment;
	*aliasAssignment = '\0';
	result = delete_hist_node_at_index(&(shellInfo->alias),
			get_node_index(shellInfo->alias,
				find_node_with_pfx(shellInfo->alias, aliasStr, -1)));
	*aliasAssignment = tempChar;
	return (result);
}

/**
 * setAlias - Sets an alias for a command.
 * @shellInfo: Parameter structure.
 * @aliasStr: The string representing the alias.
 * Return: Returns 0 on success, 1 on error.
 */

int setAlias(shell_info_t *shellInfo, char *aliasStr)
{
	char *aliasAssignment;

	aliasAssignment = _strchr(aliasStr, '=');
	if (!aliasAssignment)
		return (1);
	if (!*++aliasAssignment)
		return (rmShellAlias(shellInfo, aliasStr));
	rmShellAlias(shellInfo, aliasStr);

	return (add_history_node_end(&(shellInfo->alias), aliasStr, 0) == NULL);
}

/**
 * printAlias - Prints an alias string.
 * @node: The alias node.
 * Return: Returns 0 on success, 1 on error.
 */

int printAlias(list_t *node)
{
	char *aliasAssignment = NULL, *aliasName = NULL;

	if (node)
	{
		aliasAssignment = _strchr(node->str, '=');
		for (aliasName = node->str; aliasName <= aliasAssignment; aliasName++)
			_putchar(*aliasName);
		_putchar('\'');
		_puts(aliasAssignment + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - Manages shell aliases.
 * @shellInfo: Structure containing arguments.
 * Return: Returns 0.
 */

int manageAlias(shell_info_t *shellInfo)
{
	int i = 0;
	char *aliasAssignment = NULL;
	list_t *node = NULL;

	if (shellInfo->argc == 1)
	{
		node = shellInfo->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shellInfo->argv[i]; i++)
	{
		aliasAssignment = _strchr(shellInfo->argv[i], '=');
		if (aliasAssignment)
			setAlias(shellInfo, shellInfo->argv[i]);
		else
			printAlias(find_node_with_pfx(shellInfo->alias, shellInfo->argv[i], '='));
	}
	return (0);
}
