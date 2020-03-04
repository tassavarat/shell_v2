#include "shell.h"

/**
 * signal_handler - Handles Ctrl + C signal
 * @signum: number of the signal
 */
void signal_handler(int signum)
{
	(void) signum;
	_puts("\n");
	write(STDERR_FILENO, "$ ", 2);
	fflush(stdout);
}
