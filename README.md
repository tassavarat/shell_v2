# An implementation of sh in C programming language

[![Run on Repl.it](https://repl.it/badge/github/tassavarat/shell_v2)](https://repl.it/github/tassavarat/shell_v2)
## Overview

**Simple Shell** - is a Holberton school group project. The task is to write a simple UNIX command interpreter.

Table of contents
=================

<!--ts-->
   * [Overview](#overview)
   * [Table of contents](#table-of-contents)
   * [General Requirements](#requirements)
   * [Authorized functions and macros](#list-of-allowed-functions-and-system-calls)
   * [Compilation](#compilation)
   * [Tasks](#tasks)
   * [Installation](#installation)
   * [Examples](#examples)
   * [Authors](#authors)
<!--te-->


*************************************************************************

## Requirements
### General

  - Allowed editors: vi, vim, emacs
  - All your files will be compiled on Ubuntu 14.04 LTS
  - Your programs and functions will be compiled with gcc 4.8.4 using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
  - All your files should end with a new line
  - A `README.md` file, at the root of the folder of the project is mandatory
Your code should use the `Betty` style. It will be checked using [`betty-style.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [`betty-doc.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
  - No more than 5 functions per file
  - All your header files should be include guarded
  - Use system calls only when you need to ([`why?`](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))
## More Info
### Output
- Unless specified otherwise, your program __must have the exact same output__ as `sh` (`/bin/sh`) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
******************************************************************************

## List of allowed functions and system calls

- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## Compilation
Your shell will be compiled this way:

    gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
## Testing
Your shell should work like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
*******************************************************************************

### Tasks
<details>
<summary>
Click here to expand
</summary>
<ul>

<li>- 0. I'm not going anywhere. You can print that wherever you want to. I'm here and I'm a Spur for life <i>mandatory</i>
</ul>
</details>

## Installation

In order to use this Simple Shell function you need to clone this repository to your local machine
```
$ git clone https://github.com/narnat/simple_shell.git
```
After cloning go to the simple_shell folder
```
$ cd simple_shell
```
You can compile it with your your C source code
```
$ gcc *.c hsh
```
*****************************************************************************************************


## Examples
```
$ ./hsh
(╯°□°)╯︵ ┻━┻ ls
a.out         built-ins.c    hsh       README.md                 simple_shell.h        strings_functions.c
built-ins2.c  environment.c  main.c    sf-0119_shell_test_suite  strings_functions2.c  test
built-ins3.c  holberton      man_page  shell.c                   strings_functions3.c  which
(╯°□°)╯︵ ┻━┻ 
(╯°□°)╯︵ ┻━┻ exit
$  
```

## Authors
[Tim Assavarat](https://github.com/tassavarat)

[Farrukh Akhrarov](https://github.com/narnat)
