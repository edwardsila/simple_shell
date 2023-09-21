#include "shell.h"

/**
 * is_executable - Determines if a file is an executable command.
 * @shellInfo: The shell_info_t struct.
 * @path: The path to the file.
 * Return: 1 if it's an executable, 0 otherwise.
 */

int is_executable(shell_info_t *shellInfo, char *path)
{
	struct stat st;

	(void)shellInfo;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * duplicate_chars - Duplicates characters from a path string.
 * @path_str: The PATH string.
 * @start: The starting index.
 * @stop: The stopping index.
 * Return: Pointer to a new buffer containing the duplicated characters.
 */

char *duplicate_chars(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
	{
		if (path_str[i] != ':')
			buf[j++] = path_str[i];
	}
	buf[j] = 0;
	return (buf);
}


/**
 * find_exe_path - Finds the full path of a command in the PATH string.
 * @shellInfo: The shell_info_t struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 * Return: The full path of the command if found, or NULL if not found.
 */
char *find_exe_path(shell_info_t *shellInfo, char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && startWith(command, "./"))
	{
		if (is_executable(shellInfo, command))
			return (_strdup(command));
	}

	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = duplicate_chars(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}

			if (is_executable(shellInfo, path))
				return (_strdup(path));
			if (!path_str[i])
				break;

			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
