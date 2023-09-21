#include "shell.h"

/**
 * isChain - Checks if current character in the buffer is a chain delimiter.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */

int isChain(shell_info_t *shellInfo, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		shellInfo->cmd_buf_type = CMD_OR;
	}
	else if (buf[i]  == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		shellInfo->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		shellInfo->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * checkChain - Checks whether we should continue chaining.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length.
 * Return: Void.
 */

void checkChain(shell_info_t *shellInfo, char *buf, size_t *p, size_t i,
		size_t len)
{
	size_t m = *p;

	if (shellInfo->cmd_buf_type == CMD_AND)
	{
		if (shellInfo->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	if (shellInfo->cmd_buf_type == CMD_OR)
	{
		if (!shellInfo->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	*p = m;
}


/**
 * replaceAlias - Replaces aliases in the tokenized string.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: 1 if replaced, 0 otherwise.
 */

int replaceAlias(shell_info_t *shellInfo)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_pfx(shellInfo->alias, shellInfo->argv[0],
				'=');
		if (!node)
			return (0);
		free(shellInfo->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shellInfo->argv[0] = p;
	}
	return (1);
}

/**
 * replaceVars - Replaces variables in the tokenized string.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: 1 if replaced, 0 otherwise.
 */

int replaceVars(shell_info_t *shellInfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; shellInfo->argv[i]; i++)
	{
		if (shellInfo->argv[i][0] != '$' || !shellInfo->argv[i][1])
			continue;

		if (!_strcmp(shellInfo->argv[i], "$?"))
		{
			replace_string(&(shellInfo->argv[i]), _strdup
				(convert_number_to_str(shellInfo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shellInfo->argv[i], "$$"))
		{
			replace_string(&(shellInfo->argv[i]), _strdup
					(convert_number_to_str(getpid(), 10, 0)));
			continue;
		}
		node = find_node_with_pfx(shellInfo->env,&
				shellInfo->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shellInfo->argv[i]), _strdup(_strchr
						(node->str, '=') + 1));
			continue;
		}
		replace_string(&shellInfo->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 * Return: 1 if replaced, 0 otherwise.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
