CC=gcc
CFLAGS=-Wall -Wextra -Werror -Iinclude -std=c99
SRCS=src
INCS=include

all: assembler

assembler: $(SRCS)/main.c $(SRCS)/assembler.c $(SRCS)/dynamic_array.c $(SRCS)/hashtable.c $(SRCS)/helper.c
	$(CC) $(CFLAGS) -lc $^ -o build/$@