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

#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND	2
#define CMD_CHAIN 3

/* convert_number */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/*   getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: number
 * @str: string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

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

/* getline */
ssize_t bufferInput(shell_info_t *info, char **buf, size_t *len);
ssize_t  getInputLine(shell_info_t *info);
ssize_t readBuffer(shell_info_t *info, char *buf, size_t *i);
int get_line(shell_info_t *info, char **ptr, size_t *length);
void handleSigint(__attribute__((unused))int sigNum);

/* getenv */
char **getEnviron(shell_info_t *shellInfo);
int unsetEnv(shell_info_t *shellInfo, char *var);
int setEnv(shell_info_t *shellInfo, char *var, char *value);

/* getinfo */
void clearShellInfo(shell_info_t *shellInfo);
void setShellInfo(shell_info_t *shellInfo, char **av);
void freeShellInfo(shell_info_t *shellInfo, int all);

/* history */
char *get_hist_file(shell_info_t *shellInfo);
int write_hist_file(shell_info_t *shellInfo);
int read_hist_file(shell_info_t *shellInfo);
int build_hist_list(shell_info_t *shellInfo, char *buf, int linecount);
int renumber_history(shell_info_t *shellInfo);

/* lists */
list_t *add_history_node(shell_info_t *shellInfo, const char *str, int num);
list_t *add_history_node_end(list_t **head, const char *str, int num);
size_t print_history_str(const list_t *h);
int delete_hist_node_at_index(list_t **head, unsigned int index);
void free_hist_list(list_t **head_p);

/* parser */
int is_executable(shell_info_t *shellInfo, char *path);
char *duplicate_chars(char *path_str, int start, int stop);
char *find_exe_path(shell_info_t *shellInfo, char *path_str, char *command);

/* realloc */
char *_memset(char *s, char c, unsigned int n);
void free_string_array(char **str_arr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* memory */
int freeAndNull(void **ptr);

/* shell_loop */
int hsh(shell_info_t *shellInfo, char **av);
int find_builtin(shell_info_t *shellInfo);
void findCmd(shell_info_t *shellInfo);
void forkCmd(shell_info_t *shellInfo);

/* string */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* string_1 */
int _strlen(char *s);
int _strcmp(char *str1, char *str2);
char *startWith(const char *stack, const char *c);
char *_strcat(char *dest, char *src);

/* tokenizer */
char **strtow(char *input_str, char *delim);

/* vars */
int isChain(shell_info_t *shellInfo, char *buf, size_t *p);
void checkChain(shell_info_t *shellInfo, char *buf, size_t *p,
	size_t i, size_t len);
int replaceAlias(shell_info_t *shellInfo);
int replace_string(char **old, char *new);
int replaceVars(shell_info_t *shellInfo);

/* list_1 */
size_t list_length(const list_t *h);
char **list_to_string_arr(list_t *head);
size_t print_list(const list_t *h);
list_t *find_node_with_pfx(list_t *node, char *pfx, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* errors1 */
int _erratoi(char *s);
void print_error(shell_info_t *shellInfo, char *errorStr);
int print_d(int, int);
char *convert_number_to_str(long int, int, int);
void rm_comments(char *);

#endif
