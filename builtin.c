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
		exitStatus = customAtoi(shellInfo->argv[1]);
		if (exitStatus == -1)
		{
			shellInfo->status = 2;
			print_error(shellInfo, "Wrong number: ");
			print_error(shellInfo, shellInfo->argv[1]);
			print_new_line();
			return (1);
		}
		shellInfo->errNum = exitStatus;
	}
	else
		shellInfo->errNum = -1;
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
		printErrorMessage(shellInfo, "TODO: Failure\n");
	if (!shellInfo->argc[1])
	{
		newDir = _getenv(shellInfo, "HOME=");
		if (!newDir)
			chdirResult = chdir((newDir = _getenv(shellInfo, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(shellInfo->argv[1], "-") == 0)
	{
		if (!_getenv(shellInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shellInfo, "OLDPWD="));
		_putchar('\n');
		chdirResult = chdir((newDir = _getenv(shellInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(shellInfo->argv[1]);

	if (chdirResult == -1)
	{
		printError(shellInfo, "cannot cd to: ");
		_eputs(shellInfo->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(shellInfo, "OLDPWD", _getenv(shellInfo, "PWD="));
		_setenv(shellInfo, "PWD", getcwd(buffer, 1024));
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
