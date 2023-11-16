#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_type;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_type *);
} builtin_table;


/* find_cmd.c */
int shell_loop(info_type *, char **);
int find_builtin_cmd(info_type *);
void find_command(info_type *);
void fork_command(info_type *);

/* get_path.c */
int is_command(info_type *, char *);
char *dupli_chars(char *, int, int);
char *find_path(info_type *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* error_print.c */
void _eput_str(char *);
int _eputchar(char);
int _put_fd(char c, int fd);
int _puts_fd(char *str, int fd);

/* str_len.c */
int _strlength(char *);
int _str_comp(char *, char *);
char *starts_with(const char *, const char *);
char *_str_cat(char *, char *);

/* strcopy.c */
char *_str_copy(char *, char *);
char *_str_dup(const char *);
void _puts(char *);
int _putchar(char);

/* strncopy.c */
char *_strn_copy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_str_chr(char *, char);

/* split_str.c */
char **str_split(char *, char *);
char **str_split2(char *, char);

/* memory_set.c */
char *_memory_set(char *, char, unsigned int);
void str_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* free_ptr.c */
int ptr_free(void **);

/* interactive.c */
int interactive(info_type *);
int is_delim(char, char *);
int _is_alpha(int);
int _sti(char *);

/* convert_str.c */
int _errors_sti(char *);
void print_error(info_type *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* my_dir.c */
int _myexit(info_type *);
int _mydir(info_type *);
int _myhelp(info_type *);

/* set_alias.c */
int _myhistory(info_type *);
int _myalias(info_type *);

/*get_line.c */
ssize_t get_input(info_type *);
int _getline(info_type *, char **, size_t *);
void sigintHandler(int);

/* get_info.c */
void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);

/* my_environ.c */
char *_get_env(info_type *, const char *);
int _myenvir(info_type *);
int _mysetenv(info_type *);
int _my_unsetenv(info_type *);
int p_env_list(info_type *);

/* get_env.c */
char **get_env(info_type *);
int _unsetenv(info_type *, char *);
int _setenviro(info_type *, char *, char *);

/* get_history.c */
char *get_history_f(info_type *info);
int write_history(info_type *info);
int read_hist(info_type *info);
int build_history_l(info_type *info, char *buf, int linecount);
int renumber_history(info_type *info);

/* get_nod.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t prt_list_str(const list_t *);
int delete_node(list_t **, unsigned int);
void free_list(list_t **);

/* list_len.c */
size_t list_len(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node(list_t *, list_t *);

/* chain.c */
int is_chain_del(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);
int replace_alias(info_type *);
int replace_vars_str(info_type *);
int replace_str(char **, char *);

#endif
