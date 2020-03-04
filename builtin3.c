#include "shell.h"

void help3(int help_num)
{
	if (help_num == 0)
	{
		_puts("help: clear\n"
				"    Clear the terminal screen\n\n"
				"    Clears your screen if this is possible, including its scrollback buffer\n"
				"    (if the extended “E3” capability is defined).  clear looks in the environment\n"
				"    for the terminal type given by the environment variable TERM, and then in the\n"
				"    terminfo database to determine how to clear the screen.\n");
	}
	else if (help_num == 1)
	{
		_puts("help: [alias-name[=string]...]\n"
				"    Define or display aliases\n\n"
				"    The alias utility shall create or redefine alias definitions or write the values\n"
				"    of existing alias definitions to standard output. An  alias  definition  provides\n"
				"    a string value that shall replace a command name when it is encountered\n");
	}
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
	else if (!_strcmp(args->tokarr[1], "clear"))
		help3(0);
	else if (!_strcmp(args->tokarr[1], "alias"))
		help3(1);
	else
		error(args);
}

/**
 * help - Display information about builtin commands
 * @args: Arguments structure
 *
 * Return: 0
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
				"env\nexit [n]\ncd [dir]\nunsetenv [name]\n"
				"setenv [name]\nhelp [pattern...]\nclear\n"
				"alias [name[=value] ... ]\n");
	}
	return (0);
}
