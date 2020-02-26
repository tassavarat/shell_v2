#include "shell.h"

/**
 * help - Display information about builtin commands
 * @args: Arguments structure
 *
 * Return: 1
 */
int help(arguments *args)
{
	if (args->tokarr[1])
	{
		help2(args);
	}
	else
	{
		_puts("Type 'help name' to find out more about the function 'name'.\n\n"
		      "env\nexit [n]\ncd [dir]\nunsetenv [name]\nsetenv [name]\nhelp [pattern...]\n");
	}
	return (1);
}

/**
 * help2 - Display information about builtin commands
 * @args: Arguments structure
 */
void help2(arguments *args)
{
	if (!_strcmp(args->tokarr[1], "env"))
		_puts("env\n"
		      "    Prints the full environment\n");
	else if (!_strcmp(args->tokarr[1], "exit"))
		_puts("exit: exit [n]\n"
		      "    Exit the shell.\n\n"
		      "    Exits the shell with a status of N. If N is omitted, the exit status\n"
		      "    is that of the last command executed.\n");
	else if (!_strcmp(args->tokarr[1], "cd"))
		_puts("cd: cd [dir]\n"
		      "    Change the shell working directory.\n\n"
		      "    Change the current directory to DIR. The default DIR is the value of the\n"
		      "    HOME shell variable.\n");
	else if (!_strcmp(args->tokarr[1], "unsetenv"))
		_puts("unsetenv: unsetenv [name]\n"
		      "    Remove an environmental variable.\n\n"
		      "    Deletes the variable name from the enviroment. If the name does not\n"
		      "    exist in the enviromnent, then the builtin succeeds, and the\n"
		      "    environment is unchanged\n");
	else if (!_strcmp(args->tokarr[1], "setenv"))
		_puts("setenv: setenv [name] [value] [overwrite]\n"
		      "    Change or add an environmental variable.\n\n"
		      "    Adds the variable name to the environment with the value value, if name\n"
		      "    does not already exist. If name does exist in the environment, then it's\n"
		      "    value is changed to value if overwrite is nonzero; if overwrite is zero,\n"
		      "    then the value of name is not changed.\n");
	else if (!_strcmp(args->tokarr[1], "help"))
		_puts("help: help [pattern...]\n"
		      "    Displays brief summaries of builtin commands.\n\n"
		      "    If PATTERN is specified, give detailed help on all commands matching PATTERN,\n"
		      "    otherwise the list if help topics is printed.\n");
	else
		error(args);
}
