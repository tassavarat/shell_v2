#include "shell.h"

int check_pipe(arguments *args, char *lineptr)
{
	size_t i;

	for (i = 0; lineptr[i]; ++i)
	{
		if (lineptr[i] == '|')
		{
			++args->cmdcnt;
		}
	}
	printf("cmdcnt %lu\n", args->cmdcnt);
	return (0);
}
