#include "shell.h"

/**
 * bufferInput - Buffers chained commands.
 * @info: Parameter structure.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 * Return: Bytes read.
 */

ssize_t bufferInput(shell_info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handleSigint);
		if (0)
			bytesRead = getline(buf, &len_p, stdin);
		else
			bytesRead = get_line(info, buf, &len_p);

		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			build_hist_list(info, *buf, info->histcount++);

			{
				*len = bytesRead;
				info->cmd_buf = buf;
			}
		}
	}
	return (bytesRead);
}

/**
 * getInputLine - Gets a line minus the newline.
 * @info: Parameter structure.
 * Return: Bytes read.
 */

ssize_t  getInputLine(shell_info_t *info)
{
	static char *cmdBuffer;
	static size_t currentIndex, nextIndex, bufferLength;
	ssize_t bytesRead = 0;
	char **currentCmdPtr = &(info->arg), *currentCmd;

	_putchar(-1);
	bytesRead = bufferInput(info, &cmdBuffer, &bufferLength);
	if (bytesRead == -1)
		return (-1);
	if (bufferLength)
	{
		nextIndex = currentIndex;
		currentCmd = cmdBuffer + currentIndex;

		checkChain(info, cmdBuffer, &nextIndex, currentIndex, bufferLength);
		while (nextIndex < bufferLength)
		{
			if (isChain(info, cmdBuffer, &nextIndex))
				break;
			nextIndex++;
		}

		currentIndex = nextIndex + 1;
		if (currentIndex >= bufferLength)
		{
			currentIndex = bufferLength = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*currentCmdPtr = currentCmd;
		return (_strlen(currentCmd));
	}
	*currentCmdPtr = cmdBuffer;
	return (bytesRead);
}

/**
 * readBuffer - Reads a buffer.
 * @info: Parameter structure.
 * @buf: Buffer.
 * @i: Size.
 * Return: bytesRead
 */

ssize_t readBuffer(shell_info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->readfd, buf, 1024);
	if (bytesRead >= 0)
		*i = bytesRead;
	return (bytesRead);
}

/**
 * get_line - Gets the next line of input from STDIN.
 * @info: Parameter structure.
 * @ptr: Address of a pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 * Return: bytesRead
 */

int get_line(shell_info_t *info, char **ptr, size_t *length)
{
	static char buf[1024];
	static size_t currentIndex, bufferLength;
	size_t k;
	ssize_t bytesRead = 0;
	char *currentLine = NULL, *newCurrentLine = NULL, *c;

	currentLine = *ptr;
	if (currentLine && length)
		bytesRead = *length;
	if (currentIndex == bufferLength)
		currentIndex = bufferLength = 0;

	bytesRead = readBuffer(info, buf, &bufferLength);
	if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
		return (-1);

	c = _strchr(buf + currentIndex, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : bufferLength;
	newCurrentLine = _realloc(currentLine, bytesRead, bytesRead ?
			bytesRead + k : k + 1);
	if (!newCurrentLine)
		return (currentLine ? free(currentLine), -1 : -1);

	if (bytesRead)
		_strncat(newCurrentLine, buf + currentIndex, k - currentIndex);
	else
		_strncpy(newCurrentLine, buf + currentIndex,
				k - currentIndex + 1);

	bytesRead += k - currentIndex;
	currentIndex = k;
	currentLine = newCurrentLine;

	if (length)
		*length = bytesRead;
	*ptr = currentLine;
	return (bytesRead);
}

/**
 * handleSigint - Blocks Ctrl-C.
 * @sigNum: The signal number.
 * Return: void
 */

void handleSigint(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(-1);
}
