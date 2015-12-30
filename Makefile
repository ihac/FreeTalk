CC=gcc
CFLAGS=-I.
DEPS=freetalk.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: wrapper.o server.o myerr.o
	$(CC) -o server wrapper.o myerr.o server.o $(CFLAGS)
