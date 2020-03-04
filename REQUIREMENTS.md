# Requirements
## General

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


- `access`
- `chdir`
- `close`
- `execve`
- `fork`
- `stat (__xstat)`
- `lstat (__lxstat)`
- `fstat (__fxstat)`
- `kill`
- `open`
- `read`
- `signal`
- `wait`
- `waitpid`
- `wait3`
- `wait4`
- `write`
- `_exit`
- `dup`
- `dup2`
- `pipe`
- `unlink`
- `time`
- `gethostname`
- `geteuid`
- `sigaction`
- `sigemptyset`
- `select`
- `getpid`
- `__errno_location (errno macros)`
- `closedir`
- `exit`
- `free`
- `getcwd`
- `getline`
- `malloc`
- `opendir`
- `perror`
- `readdir`
- `strtok`
- `localtime`
- `getpwuid`
- `isatty`
- `printf`
- `fflush`
- `fprintf`
- `vfprintf`
- `sprintf`

## Compilation

-     You have to provide a `Makefile` in order to compile your program
-     Your `Makefile` must define the `all` rule: The `all` rule should compile and link the source code to generate the executable `hsh`
-     Make sure your program compiles on `Ubuntu 14.04 LTS`, with `gcc 4.8.4`
-     You must compile using the flags `-Wall -Werror -Wextra` and `-pedantic`
-     Your executable must be named: `hsh`

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
