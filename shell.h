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

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct list
{
	char *str;
	struct list *next;
} list;

typedef struct arguments
{
	int ac;
	char **av;
	char exitchr;
	char **tokarr;
	list *env;
	int exit_status;
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

/* string */
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strlen(char *str);
char *_strdup(const char *str);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);

/* environment */
char *_getenv(char *name, arguments *args);
list *envlist(void);

/* linked_list */
list *add_node_end(list **head, const char *str);

/* builtins */
int builtins(arguments *args);

#endif /* SHELL_H */
