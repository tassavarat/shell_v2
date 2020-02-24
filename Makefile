# Make file for shell v2 project at Holberton school
# List of variables
SHELL = /bin/bash
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
# name of the executable
NAME = hsh
# Find all c files in current directory and substitute
# extension with object files (.o)
OBJ = $(patsubst %.c,%.o, $(wildcard *.c))
LINTER = betty

# Compile object files only when they are modified,
# It's implicitly compiled
# %.o: %.c
# 	$(CC) -c $< $(CFLAGS)

# Main directive
all: $(NAME)

# Compile executable from object files
$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean, run, check, memcheck, memfull, test

clean:
	rm -f *.o $(NAME)

# Compile and run  command, @ means do not print info
run: all
	@./$(NAME)

check:
	@$(LINTER) *.[ch]

memcheck: all
	@valgrind ./$(NAME)

memfull: all
	@valgrind --leak-check=full --track-origins=yes ./$(NAME)

test: all
	cp $(NAME) shell_v2_checker/ && cd shell_v2_checker && ./start.bash
