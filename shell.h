#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

/**
 * struct shell_info - contains pseudo-arguments to pass into a function,
 * allowing a uniform prototype for a function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 * @cmdBuffer: a buffer for storing chained commands
 * @cmdBufferLength: length of the cmdBuffer
 */
typedef struct shell_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;

	char *cmdBuffer;
	size_t cmdBufferLength;
} shell_info_t;


/**
 * struct ShellBuiltin - Structure for shell built-in commands.
 * @command: The built-in command name.
 * @handler: The function pointer to the command handler.
 * Description: This structure associates a built-in command name with
 * its corresponding handler function.
 */

typedef struct ShellBuiltin
{
	char *command;
	int (*handler)(shell_info_t *);
} ShellBuiltin;


/* atoi */
int isShellInteractive(shell_info_t *shellInfo);
int isCharDelim(char character, char *delimStr);
int isalpha(int c);
int strToInt(char *str);

/* builtin */
int exitShell(shell_info_t *shellInfo);
int changeDir(shell_info_t *shellInfo);
int showHelp(shell_info_t *shellInfo);

/* builtin1 */
int displayShellHist(shell_info_t *shellInfo);
int rmShellAlias(shell_info_t *shellInfo, char *aliasStr);
int setAlias(shell_info_t *shellInfo, char *aliasStr);
int printAlias(list_t *node);
int manageAlias(shell_info_t *shellInfo);

/* exits */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* environ */
int dispEnvironment(shell_info_t *shellInfo);
char *getEnvVariable(shell_info_t *shellInfo, const char *name);
int setEnvVariable(shell_info_t *shellInfo);
int unsetEnvVariable(shell_info_t *shellInfo);
int populateEnvList(shell_info_t *shellInfo);

/* errors */
void _eputs(char *str);
int _eputchar(char c);
int _putFileDp(char c, int filedescriptor);
int _putsFileDp(char *str, int filedescriptor);


#endif
