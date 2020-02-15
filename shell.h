#ifndef SHELL_H
#define SHELL_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
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

typedef struct arguments
{
	int ac;
	char **av;
	char exitchr;
	char **tokarr;
} arguments;

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

/* string */
int _strcmp(char *s1, char *s2);

#endif /* SHELL_H */
