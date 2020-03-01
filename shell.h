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
#include "_getline.h"

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
 * @pipefd: pipe descriptors
 * @pstat: flag to know which end of @pipefd to close
 * @fd: file descriptor where input will be taken
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
	int pipefd[2];
	int pstat;
	int fd;
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
int initparam(arguments *args, const int ac, char **av);
void pprompt(arguments *args, char *prompt);
void error(arguments *args);

/* string */
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strlen(char *str);
char *_strdup(const char *str);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
char *_memset(char *s, char b, unsigned int n);
char *_strncpy(char *dest, char *src, int n);
int is_digit(char n);
int _puts(char *str);
char *convert(unsigned int num, int base);
char *strsrch(char *s, char c, size_t len);
char *_memcpy(char *dest, char *src, unsigned int n);

/* environment */
char *_getenv(char *name, arguments *args);
list *envlist(void);
char **ltoa(list *head);

/* linked_list */
list *add_node_end(list **head, const char *str);
size_t list_len(const list *h);

/* builtin */
int builtins(arguments *args);
int clear_scr(arguments *args);
int callexit(arguments *args);
int penv(arguments *args);
int changedir(arguments *args);
int parsecd(arguments *args);
int _setenv(arguments *args);
int set_environment(list **env, char *name, char *value);
int _unsetenv(arguments *args);
size_t envmatch(char *s, list *tmp, arguments *args);
void help2(arguments *args);
int help(arguments *args);

/* fork */
void create_process(arguments *args);
void forkproc(arguments *args, char *exec);
char *get_path(arguments *args);
char *split_path(char *str);

/* parse */
size_t wordcount(char *lineptr);
void cleanup(arguments *args, char mode);
int syntaxerr(char *lineptr);
void checkerr(int *stat, char *errs, size_t *i, int incr);
char **tokenise(char *lineptr);
void parse_operators(arguments *args, char *lineptr);
int is_comment(char *lineptr, size_t i);
char no_quote(char *lineptr, size_t i, char *quote);

/* execution */
void shell_run(arguments *args, char *lineptr);
void shell(arguments *args);

/* redirection */
int check_redirection(arguments *args, char *lineptr, int *fds);
int stdout_redirection(arguments *args, char *lineptr, size_t i, int *fds);
int stdin_redirection(arguments *args, char *lineptr, size_t i, int *fds);
int check_redirect_errs(arguments *args, int *fds, int flags, char *file,
		int is_valid, int which_redirect);
void clean_redirection(arguments *args, int *fds);
char *heredoc(arguments *args, char *lineptr, size_t i);

/* pipe */
void write_pipe(arguments *args, char *lineptr, int *fd, char *operator);
void chain_pipe(arguments *args, char *lineptr, int *fd, char *operator,
		int pstat);

void var_expansion(arguments *args);

/* Descriptors */
int choose_fd(arguments *args);

void free_list(list *head);
#endif /* SHELL_H */
