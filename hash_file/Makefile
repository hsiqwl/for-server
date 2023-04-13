CC=gcc
flags = -g -lreadline
all: clean debug
debug:
	$(CC) -c *.c $(flags)
	$(CC) *.o -o main $(flags)

clean:
	rm -rf *.o
