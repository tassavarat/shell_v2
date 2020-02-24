#ifndef SHELL_H
#define SHELL_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define EXITERR 100
#define CDERR 101
#define ENVERR 102

/**
 * struct list - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 */
typedef struct list
{
	char *str;
	struct list *next;
} list;

/**
 * struct arguments - contains arguments used by functions
 * @ac: number of arguments
 * @av: array of argument strings
 * @exitstr: string to print on shell exit
 * @tokarr: tokenised array
 * @env: head pointer to linked list
 * @exit_status: exit value
 * @cmdnum: current command number
 * @errstr: Error string
 */
typedef struct arguments
{
	int ac;
	char **av;
	char *exitstr;
	char **tokarr;
	list *env;
	int exit_status;
	size_t cmdnum;
	char *errstr;
} arguments;

extern char **environ;

/**
 * struct built_ins - Struct for built-ins
 * @bi: Name of built-ins
 * @f: Function pointer
 */
typedef struct built_ins
{
	char *bi;
	int (*f)(arguments *args);
} built_ins;

/* shell */
void pprompt(arguments *args);
int initparam(arguments *args, const int ac, char **av);


void error(arguments *args);

/* string */
int _atoi(char *s);
char *_strdup(const char *str);
size_t _strlen(char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
int _strcmp(char *s1, char *s2);

char *_strchr(char *s, char c);

/* string_2 */
int is_digit(char n);
char *_strncpy(char *dest, char *src, int n);
char *_memset(char *s, char b, unsigned int n);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);

/* environment */
char *_getenv(char *name, arguments *args);
list *envlist(void);

/* linked_list */
list *add_node_end(list **head, const char *str);

/* builtin */
int changedir(arguments *args);
int penv(arguments *args);
int callexit(arguments *args);
int clear_scr(arguments *args);
int builtins(arguments *args);

/* builtin_2*/
size_t envmatch(char *s, list *tmp, arguments *args);
int _unsetenv(arguments *args);
int set_environment(list **env, char *name, char *value);
int _setenv(arguments *args);
int parsecd(arguments *args);

/* fork */
char *split_path(char *str);
char *get_path(arguments *args);
void forkproc(arguments *args, char *exec);
void create_process(arguments *args);

/* parse */
void checkerr(int *stat, char *errs, size_t *i, int incr);
int syntaxerr(char *lineptr);
void error(arguments *args);
void cleanup(arguments *args, char mode);
size_t wordcount(char *lineptr);

/* parse_2 */
char no_quote(char *lineptr, size_t i, char *quote);
void check_redirection(arguments *args, char *lineptr, int *fds);
int is_comment(char *lineptr, size_t i);
void parse_operators(arguments *args, char *lineptr);
char **tokenise(char *lineptr);

/* execution */
void shell_run(arguments *args, char *lineptr);
void shell(arguments *args);

#endif /* SHELL_H */
