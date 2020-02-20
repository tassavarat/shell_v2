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
void cleanup(arguments *args, char mode);
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

/* environment */
char *_getenv(char *name, arguments *args);
list *envlist(void);

/* linked_list */
list *add_node_end(list **head, const char *str);

/* builtins */
int builtins(arguments *args);
int _setenv(arguments *args);
int _unsetenv(arguments *args);
void set_environment(list **env, char *name, char *value);
int parsecd(arguments *args);

/* fork */
char *get_path(arguments *args);
void create_process(arguments *args);

/* parse */
size_t wordcount(char *lineptr);

#endif /* SHELL_H */
