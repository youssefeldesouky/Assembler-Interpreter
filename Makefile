CC=gcc
CFLAGS=-Wall -Wextra -Wno-unused-result -I./include -std=c99 -O2
SRCS=src
INCS=include

all: assembler

assembler: $(SRCS)/main.c $(SRCS)/assembler.c $(SRCS)/dynamic_array.c $(SRCS)/hashtable.c $(SRCS)/helper.c
	$(CC) $(CFLAGS) $^ -o build/$@