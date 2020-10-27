# An implementation of sh in C programming language

[![Run on Repl.it](https://repl.it/badge/github/tassavarat/shell_v2)](https://repl.it/github/tassavarat/shell_v2)
## Overview

**Shell** - is a collaborative project. The goal is to write a simple UNIX command interpreter and hopefully learn about system calls and the inner workings of UNIX along the way.

Table of contents
=================

<!--ts-->
   * [Compilation](#compilation)
   * [Tasks](#tasks)
   * [Installation](#installation)
   * [Examples](#examples)
   * [Authors](#authors)
<!--te-->

*******************************************************************************

## Installation and Compilation

In order to use the Shell, the project must be on your local machine. Open your favourite terminal and navigate to a directory where you wish the project to reside. Once that's done, we will clone the project.
```
$ git clone https://github.com/tassavarat/shell_v2.git
```
After cloning, let's navigate into the directory.
```
$ cd shell_v2
```
Use make to compile it.
```
$ make
```
Now run the executable to start the Shell
```
./sh
```
*****************************************************************************************************

We tried our best to implement quite a few features. The following section is a list of the capabilities of our Shell.

## Examples
List directory contents:
```
$ ./sh
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
