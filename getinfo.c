#include "shell.h"

/**
 * clearShellInfo - Initializes shell_info_t structure.
 * @shellInfo: Pointer to the shell_info_t structure to be cleared.
 */

void clearShellInfo(shell_info_t *shellInfo)
{
	shellInfo->arg = NULL;
	shellInfo->argv = NULL;
	shellInfo->path = NULL;
	shellInfo->argc = 0;
}

/**
 * setShellInfo - Initializes shell_info_t structure.
 * @shellInfo: Pointer to the shell_info_t structure to be initialized.
 * @av: Argument vector typically passed to the shell.
 */

void setShellInfo(shell_info_t *shellInfo, char **av)
{
	int i;

	i = 0;
	shellInfo->fname = av[0];
	if (shellInfo->arg)
	{
		shellInfo->argv = strtow(shellInfo->arg, " \t");
		if (!shellInfo->argv)
		{
			shellInfo->argv = malloc(sizeof(char *) * 2);
			if (shellInfo->argv)
			{
				shellInfo->argv[0] = _strdup(shellInfo->arg);
				shellInfo->argv[1] = NULL;
			}
		}
		for (i = 0; shellInfo->argv && shellInfo->argv[i]; i++)
			;
		shellInfo->argc = i;

		replaceAlias(shellInfo);
		replaceVars(shellInfo);
	}
}

/**
 * freeShellInfo - Frees shell_info_t structure fields.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @all: True if freeing all fields.
 */

void freeShellInfo(shell_info_t *shellInfo, int all)
{
	ffree(shellInfo->argv);
	shellInfo->argv = NULL;
	shellInfo->path = NULL;

	if (all)
	{
		if (!shellInfo->cmd_buf)
			free(shellInfo->arg);
		if (shellInfo->env)
			freeList(&(shellInfo->env));
		if (shellInfo->history)
			freeList(&(shellInfo->history));
		if (shellInfo->alias)
			freeList(&(shellInfo->alias));
		ffree(shellInfo->environ);
		shellInfo->environ = NULL;
		bfree((void **)shellInfo->cmd_buf);
		if (shellInfo->readfd > 2)
			close(shellInfo->readfd);
		_putchar(BUF_FLUSH);
	}
}
