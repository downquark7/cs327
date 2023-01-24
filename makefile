CC=gcc
CFLAGS=-g

all: listKnights

listKnights: listKnights.o
	$(CC) listKnights.o -o listKnights

listKnights.o: listKnights.c
	$(CC) $(CFLAGS) listKnights.c

clean:
	rm -rf *o listKnights
