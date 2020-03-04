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
#define HISTORY_SIZE 1024
#define HISTORY_FILE ".hsh_history"

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
 * struct queue - Queue
 * @size: size of queue
 * @pos: position of history
 * @first: first node
 * @last: last node
 */
typedef struct queue
{
	size_t size;
	size_t pos;
	list *first;
	list *last;
} queue;

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
 * @head: pointer to aliases head node
 * @history: pointer to head of queue linked list
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
	struct aliases *head;
	queue *history;
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

/**
 * struct aliases - link lists of aliases and their values
 * @name: name of alias
 * @value: alias value
 * @next: pointer to next node
 */
typedef struct aliases
{
	char *name;
	char *value;
	struct aliases *next;
} aliases;

/* shell */
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
void var_expansion(arguments *args);

/* linked_list */
list *add_node_end(list **head, const char *str);
size_t list_len(const list *h);
void free_list(list *head);

/* builtin */
int builtins(arguments *args);
int callexit(arguments *args);
int parsecd(arguments *args);
int _setenv(arguments *args);
int set_environment(list **env, char *name, char *value);
int _unsetenv(arguments *args);
void help2(arguments *args);
int help(arguments *args);

/* fork */
void create_process(arguments *args);

/* parse */
size_t wordcount(char *lineptr);
void cleanup(arguments *args, char mode);
char **tokenise(char *lineptr);
void parse_operators(arguments *args, char *lineptr);
char no_quote(char *lineptr, size_t i, char *quote);

/* execution */
void shell_run(arguments *args, char *lineptr);
void shell(arguments *args);

/* redirection */
int check_redirection(arguments *args, char *lineptr, int *fds);
void clean_redirection(arguments *args, int *fds);
char *heredoc(arguments *args, char *lineptr, size_t i);

/* pipe */
void write_pipe(arguments *args, char *lineptr, int *fd, char *op);
void chain_pipe(arguments *args, char *lineptr, int *fd, char *op, int pstat);

/* Descriptors */
int choose_fd(arguments *args);
void read_config(arguments *args);

/* alias */
int alias(arguments *args);
void delalias(aliases *head);
void checkalias(arguments *args);
aliases *overwriteval(aliases *head, char *name);
char *doublealias(aliases *head, char *value);

/* signal */
void signal_handler(int signum);

/* queue */
queue *create_queue();
void en_queue(queue *queue, char *cmd);
void free_queue(queue **q);

/* history */
int history(arguments *args);
void write_history(arguments *args);
void read_history(arguments *args);

#endif /* SHELL_H */
