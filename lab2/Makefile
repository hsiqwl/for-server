CC=gcc
all: clean debug

list:
	$(CC) -c main.c
	$(CC) -o main_list main.o -Llibrary -llist -lreadline

vector:
	$(CC) -c main.c
	$(CC) -o main_arr main.o -Llibrary -larr -lreadline

clean:
	rm *.o
	
