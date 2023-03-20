CC=gcc
CFLAGS = -g
all: clean build
build:
	$(CC) -c funcs.c -o funcs.o
	$(CC) -c main.c -o main.o
	$(CC) main.o funcs.o -o main

debug:
	$(CC) -c funcs.c -o funcs.o $(CFLAGS)
	$(CC) -c main.c -o main.o	$(CFLAGS)
	$(CC) main.o funcs.o -o main

clean:
	rm -rf *.o
