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
		clearShellInfo(shellInfo);
		if (isShellInteractive(shellInfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		s = getInputLine(shellInfo);
		if (s != -1)
		{
			setShellInfo(shellInfo, av);
			builtin = find_builtin(shellInfo);
			if (builtin == -1)
				findCmd(shellInfo);
		}
		else if (isShellInteractive(shellInfo))
			_putchar('\n');
		freeShellInfo(shellInfo, 0);
	}
	write_hist_file(shellInfo);
	freeShellInfo(shellInfo, 0);
	if (!isShellInteractive(shellInfo) && shellInfo->status)
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
g*	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit()
 */

int find_builtin(shell_info_t *shellInfo)
{
	int i;
	int  builtIn = -1;
	ShellBuiltin builtinta[] = {
		{"exit", exitShell},
		{"env", dispEnvironment},
		{"help", showHelp},
		{"history", displayShellHist},
		{"setenv", setEnvVariable},
		{"unsetenv", unsetEnvVariable},
		{"cd", changeDir},
		{"alias", manageAlias},
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

/**
 * findCmd - finds a command in PATH
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: void
 */

void findCmd(shell_info_t *shellInfo)
{
	char *path = NULL;
	int i, j;

	shellInfo->path = shellInfo->argv[0];
	if (shellInfo->linecount_flag == 1)
	{
		shellInfo->line_count++;
		shellInfo->linecount_flag = 0;
	}
	for (i = 0, j = 0; shellInfo->arg[i]; i++)
	{
		if (!isCharDelim(shellInfo->arg[i], "\t\n"))
			j++;
	}
	if (!j)
		return;

	path = find_exe_path(shellInfo, getEnvVariable(shellInfo, "PATH="),
			shellInfo->argv[0]);
	if (path)
	{
		shellInfo->path = path;
		forkCmd(shellInfo);
	}
	else
	{
		if ((isShellInteractive(shellInfo) || getEnvVariable(shellInfo, "PATH=")
			|| shellInfo->argv[0][0] == '/') && is_executable(shellInfo,
				shellInfo->argv[0]))
			forkCmd(shellInfo);
		else if (*(shellInfo->arg) != '\n')
		{
			shellInfo->status = 127;
			print_error(shellInfo, "not found\n");
		}
	}
}

/**
 * forkCmd - forks an exec thread to run cmd
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: void
 */

void forkCmd(shell_info_t *shellInfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error! ");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shellInfo->path, shellInfo->argv, shellInfo->environ
			  ) == -1)
		{
			freeShellInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(shellInfo->status));
		if (WIFEXITED(shellInfo->status))
		{
			shellInfo->status = WEXITSTATUS(shellInfo->status);
			if (shellInfo->status == 126)
				print_error(shellInfo, "Permission denied\n");
		}
	}
}
