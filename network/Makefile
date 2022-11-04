
# add -DAPPEST for functional tracking report
# add -DMEMTEST for memory tracking report
# (and run `make clean; make` whenever you change this)
FLAGS = #-DAPPTEST # -DMEMTEST

PROG = server
PROG2 = client
OBJ = server.o
OBJ2 = object.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc
MAKE = make

VALGRIND = valgrind -s --leak-check=full --show-leak-kinds=all

all: $(PROG) $(PROG2)


$(PROG): $(OBJ) 
	$(CC) $(CFLAGS) -o $@


# server source dependencies
server.o:



$(PROG2): $(OBJ2) 
	$(CC) $(CFLAGS) -o $@


# client source dependencies
client.o:

.PHONY: all test valgrind clean

test: bash -v testing.sh >& testing.out

clean: 
	rm -rf *~ *.0
	rm -f $(PROG)
	rm -f $(PROG2)
	