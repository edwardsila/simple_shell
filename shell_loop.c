#include "shell.h"

/**
 * hsh - main shell loop
 * @shellInfo: Pointer to the shell_info_t structure.
 * @av: The argument vector from main().
 * Return: 0 on success, 1 on error, or error code.
 */

int hsh(shell_info_t *shellInfo, char **av)
{
	ssize_t s = 0;
	int builtin = 0;

	while (s != -1 && builtin != -2)
	{
		clear_info(ShellInfo);
		if (interactive(shellInfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = get_input(shellInfo);
		if (s != -1)
		{
			set_info(shellInfo, av);
			builtin = find_builtin(shellInfo);
			if (builtin == -1)
				find_cmd(shellInfo);
		}
		else if (interactive(shellInfo))
			_putchar('\n');
		free_info(shellInfo, 0);
	}
	write_history(shellInfo);
	free_info(shellInfo, 0);
	if (!interactive(shellInfo) && shellInfo->status)
		exit(shellInfo->status);
	if (builtin == -2)
	{
		if (shellInfo->err_num == -1)
			exit(shellInfo->status);
		exit(shellInfo->err_num);
	}
	return (builtin);
}

/**
 * find_builtin - finds a builtin command
 * @shellInfo: Pointer to the shell_info_t structure.
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit()
 */

int find_builtin(shell_info_t *shellInfo)
{
	int i;
	int  builtIn = -1;
	ShellBuiltin builtinta[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias}
		{NULL, NULL}
	};

	for (i = 0; builtinta[i].command; i++)
	{
		if (_strcmp(shellInfo->argv[0], builtinta[i].command) == 0)
		{
			shellInfo->line_count++;
			builtIn = builtinta[i].handler(shellInfo);
			break;
		}
	}
	return (builtIn);
}
