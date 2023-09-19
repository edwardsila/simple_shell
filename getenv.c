#include "shell.h"
/**
 * getEnviron - Retrieves and returns the environment variables as a string
 * @shellInfo: A pointer to a structure (shell_info_t)
 * @Return: A pointer to a string array containing the environment variables.
 */

char **getEnviron(shell_info_t *shellInfo)
{
	if (!shellInfo || shellInfo->env_changed)
	{
		shellInfo = listToStrings(shellInfo->env);
		shellInfo->env_chnaged = 0;
	}
	return (shellInfo->environ);
}

/**
 * unsetEnv - Remove an environment variable.
 * @shellInfo: Structure containing arguments.
 * @var: The string env var property.
 * Return: 1 on delete, 0 otherwise.
 */

int unsetEnv(shell_info_t *shellInfo, char *var)
{
	list_t *node = shellInfo->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			shellInfo->env_changed = delete_node_at_index
				(&(shellInfo->env), i);
			node = shellInfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shellInfo->env_changed);
}

/**
 * setEnv - Initialize a new environment variable,
 *             or modify an existing one.
 * @shellInfo: Structure containing potential arguments.
 * @var: The string env var property.
 * @value: The string env var value.
 * Return: Always 0.
 */

int setEnv(shell_info_t *shellInfo, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, '=');
	_strcat(buf, value);
	node = shellInfo->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shellInfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(shellInfo->env), buf, 0);
	free(buf);
	shellInfo->env_changed = 1;
	return (0);
}
