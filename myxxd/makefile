#Name: Andrew Gendreau
#Purpose: makefile for myxxd program
# ============================================

SOURCES = myxxd.c
OBJECTS = myxxd.o hexdump.o fileReader.o binary.o
CC = gcc
CFLAGS = -g -Wall

all: myxxd

myxxd: $(OBJECTS)
	$(CC) $(CFLAGS) -o myxxd $(OBJECTS)

myxxd.o: myxxd.c
	$(CC) $(CFLAGS) -c myxxd.c

hexdump.o: hexdump.h hexdump.c
	$(CC) $(CFLAGS) -c hexdump.c

fileReader.o: fileReader.h fileReader.c
	$(CC) $(CFLAGS) -c fileReader.c

binary.o: binary.c
	$(CC) $(CFLAGS) -c binary.c

clean:
	rm -f *o myxxd OBJECTS

