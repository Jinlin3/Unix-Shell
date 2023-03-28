CC = gcc
CFLAGS = -g -Wall

mysh: mysh.o
	$(CC) -o mysh mysh.o