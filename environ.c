#include "shell.h"
/**
 * dispEnvironment - Displays the current environment variables.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always returns 0.
 */

int dispEnvironment(shell_info_t *shellInfo)
{
	print_history_str(shellInfo->env);
	return (0);
}

/**
 * getEnvVariable - Gets the value of an environment variable.
 * @shellInfo: Structure containing potential arguments.
 * @name: The name of the environment variable.
 * Return: The value of the environment variable, or NULL if not found.
 */

char *getEnvVariable(shell_info_t *shellInfo, const char *name)
{
	list_t *node = shellInfo->env;
	char *p;

	while (node)
	{
		p = startWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvVariable - Initialize a new environment variable or modify
 * an existing one.
 * @shellInfo: Structure containing potential arguments.
 * Return: Returns 0 on success, 1 on error.
 */

int setEnvVariable(shell_info_t *shellInfo)
{
	if (shellInfo->argc != 3)
	{
		_eputs("check number of arguments\n");
		return (1);
	}
	if (setEnv(shellInfo, shellInfo->argv[1], shellInfo->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvVariable - Remove an environment variable.
 * @shellInfo: Structure containing arguments.
 * Return: Returns 0 on success, 1 on error.
 */

int unsetEnvVariable(shell_info_t *shellInfo)
{
	int i;

	if (shellInfo->argc == 1)
	{
		_eputs("Few Arguments.\n");
		return (1);
	}
	for (i = 1; i <= shellInfo->argc; i++)
		unsetEnv(shellInfo, shellInfo->argv[i]);

	return (0);
}

/**
 * populateEnvList - Populates the environment linked list.
 * @shellInfo: Structure containing arguments.
 * Return: Always returns 0.
 */

int populateEnvList(shell_info_t *shellInfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_history_node_end(&node, environ[i], 0);
	shellInfo->env = node;
	return (0);
}
