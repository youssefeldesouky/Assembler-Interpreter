CC=gcc
CFLAGS=-Wall -Iinclude -std=c99
SRCS=src
INCS=include

all: assembler

assembler: $(SRCS)/main.c $(SRCS)/assembler.c $(SRCS)/dynamic_array.c $(SRCS)/hashtable.c $(SRCS)/helper.c $(INCS)/helper.h $(INCS)/assembler.h $(INCS)/dynamic_array.h $(INCS)/hashtable.h
	$(CC) $(CFLAGS) -lc $^ -o build/$@