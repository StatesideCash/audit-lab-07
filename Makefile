CC=afl-clang
CFLAGS= -std=c99 -pedantic -Wall -Werror -g

clean:
	rm -f main

main:
	$(CC) $(CFLAGS) -o main main.c

all: clean main
