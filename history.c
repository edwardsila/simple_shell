#include "shell.h"

/**
 * get_hist_file - Gets the history file.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: Allocated string containing the history file.
 */

char *get_hist_file(shell_info_t *shellInfo)
{
	char *buf, *dir;

	dir = _getenv(shellInfo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist_file - Creates a file, or appends to an existing file.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: 1 on success, else -1.
 */

int write_hist_file(shell_info_t *shellInfo)
{
	ssize_t fd;
	char *filename = get_history_file(shellInfo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shellInfo->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist_file - Reads history from a file.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: histcount on success, 0 otherwise.
 */

int read_hist_file(shell_info_t *shellInfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(shellInfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(shellInfo, buf + last, linecount++);
			last = i + 1;
		}
	}
	if (last != i)
		build_hist_list(shellInfo, buf + last, linecount++);
	free(buf);
	shellInfo->histcount = linecount;
	while (shellInfo->histcount-- >= HIST_MAX)
		delete_node_at_index(&(shellInfo->history), 0);
	renumber_history(shellInfo);
	return (shellInfo->histcount);
}

/**
 * build_hist_list - Adds an entry to a history linked list.
 * @shellInfo: Pointer to the shell_info_t structure.
 * @buf: Buffer.
 * @linecount: The history linecount, histcount.
 * Return: Always 0.
 */

int build_hist_list(shell_info_t *shellInfo, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shellInfo->history)
		node = shellInfo->history;
	add_node_end(&node, buf, linecount);

	if (!shellInfo->history)
		shellInfo->history = node;

	return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes.
 * @shellInfo: Pointer to the shell_info_t structure.
 * Return: The new histcount.
 */

int renumber_history(shell_info_t *shellInfo)
{
	list_t *node = shellInfo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (shellInfo->histcount = i);
}
