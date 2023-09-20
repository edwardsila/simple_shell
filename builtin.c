#include "shell.h"

/**
 * exitShell - Exit the shell with an optional exit status.
 * @shellInfo: Structure containing potential arguments.
 *
 * Return: Exits the shell with a given exit status (0 if no exit argument).
 */

int exitShell(shell_info_t *shellInfo)
{
	int exitStatus;

	if (shellInfo->argc > 1)
	{
		exitStatus = _erratoi(shellInfo->argv[1]);
		if (exitStatus == -1)
		{
			shellInfo->status = 2;
			print_error(shellInfo, "Wrong number: ");
			_eputs(shellInfo->argv[1]);
			_eputchar('\n');
			return (1);
		}
		shellInfo->err_num = _erratoi(shellInfo->argv[1]);
		return (-2);
	}
	else
		shellInfo->err_num = -1;
	return (-2);
}

/**
 * changeDir - Change the current working directory of the process.
 * @shellInfo: Structure containing potential arguments.
 * Return: Always 0.
 */

int changeDir(shell_info_t *shellInfo)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: Failure\n");
	if (!shellInfo->argv[1])
	{
		newDir = getEnvVariable(shellInfo, "HOME=");
		if (!newDir)
			chdirResult = chdir((newDir = getEnvVariable(shellInfo, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
		if (!getEnvVariable(shellInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(getEnvVariable(shellInfo, "OLDPWD="));
		_putchar('\n');
		chdirResult = chdir((newDir = getEnvVariable(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(shellInfo->argv[1]);

	if (chdirResult == -1)
	{
		print_error(shellInfo, "cannot cd to: ");
		_eputs(shellInfo->argv[1]);
		_eputchar('\n');
	}
	else
	{
		setEnv(shellInfo, "OLDPWD", getEnvVariable(shellInfo, "PWD="));
		setEnv(shellInfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * showHelp - Display help information.
 * @shellInfo: Structure containing arguments.
 * Return: Always 0.
 */

int showHelp(shell_info_t *shellInfo)
{
	char **argArray;

	argArray = shellInfo->argv;
	_puts("show help functions \n");
	if (0)
	{
		_puts(*argArray);
	}
	return (0);
}
