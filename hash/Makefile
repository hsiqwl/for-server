CC=gcc
flags = -g
all: clean debug
debug:
	$(CC) -c *.c $(flags)
	$(CC) *.o -o main $(flags)

clean:
	rm -rf *.o
