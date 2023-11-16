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
 *struct _pass_info - contains pseudo-arguements to pass into a function,
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
typedef struct _pass_info
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

<<<<<<< HEAD
int hsh(info_type *, char **);
int find_builtin22(info_type *);
void find_commmd(info_type *);
void fork_commmand(info_type *);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);


=======
	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_type;
>>>>>>> 963ededd235ebe94b5f4c12bd1b6cfbd89932bca
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin_t
{
	char *type;
	int (*func)(info_type *);
} builtin_table;

int hsh(info_type *, char **);
int find_built(info_type *);
void find_commd(info_type *);
void fork_commd(info_type *);

int _strlen(char *);
int _str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *_str_cat(char *, char *);







int is_commd(info_type *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_type *, char *, char *);


int loophsh(char **);


void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);





char *_str_copy(char *, char *);
char *_strdupli(const char *);
void _puts(char *);
int _puts_char(char);


char *_strn_copy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


char **str_tow(char *, char *);
char **str_tow2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);


int buf_free(void **);


int interactive(info_type *);
int is_delim(char, char *);
int _is_alphab(int);
int _sti(char *);


int _err_sti(char *);
void print_error(info_type *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_cmnt(char *);


int _myexit(info_type *);
int _mydir(info_type *);
int _myhelp(info_type *);


int _myhist(info_type *);
int _myalias(info_type *);


ssize_t input_buf(info_type *info, char **buf, size_t *len);
ssize_t get_input(info_type *);
int _getline(info_type *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);


char *_get_env(info_type *, const char *);
int _myenv(info_type *);
int _mysetenv(info_type *);
int _myunsetenv(info_type *);
int populate_env_list(info_type *);


char **get_env(info_type *);
int _unsetenv(info_type *, char *);
int _setenv(info_type *, char *, char *);


char *get_history_file(info_type *info);
int write_history(info_type *info);
int read_history(info_type *info);
int build_history_list(info_type *info, char *buf, int linecount);
int renumber_history(info_type *info);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);


size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain_del(info_type *, char *, size_t *);
void check_chain(info_type *, char *, size_t *, size_t, size_t);
int replace_alias(info_type *);
int replace_vars(info_type *);
int replace_string(char **, char *);

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
#endif
