# Makefile for CS50 cards final project module
#
# Nathaniel Roe 
# CS 50, Fall 2022

# uncomment the following to turn on verbose memory logging
#TESTING= -DMEMTEST

#MISC. TEST CASES FOR FXNS
#TESTING=-DAPPTEST
L = ../../libcs50
LIBS = $L/libcs50.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L
CC = gcc
PROG = dealer
MAKE = make
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
OBJS = dealer.o ../cards/cards.o

.PHONY: all clean 

#makes indexerand indextest
all: dealer

$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# object files depend on header files

dealer.o: dealer.c
../cards/cards.o: ../cards/cards.c

clean: 
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
