# Make file for shell v2 project at Holberton school

# List of variables
CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -std=gnu89 -g
# name of the executable
NAME=hsh
# Find all c files in current directory and substitute
# extension with object files (.o)
OBJ=$(patsubst %.c,%.o, $(wildcard *.c))

LINTER=betty

# Compile object files
%.o: %.c
	$(CC) -c $< $(CFLAGS)

all: $(NAME)

# Compile executable from object files
$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean, run, check, memcheck

clean:
	rm -f *.o $(NAME)

# Compile and run  command, @ means do not print info
run: all
	@./$(NAME)

check:
	$(LINTER) *.c *.h

memcheck: all
	valgrind ./$(NAME)
