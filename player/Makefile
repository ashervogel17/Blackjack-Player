# Makefile for 'player' module
#
# Asher Vogel
# CS 50, Fall 2022

OBJS = decisionmaker.o player.o ../cards/cards.o
L1 = ../libcs50
L2 = ../network
LIBS = $(L1)/libcs50-given.a $(L2)/network.a

# comment out the following to turn off logging
APPTEST=-DAPPTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) $(APPTEST) -I$(L1) -I$(L2) #-DDEBUG
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

player: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

decisionmaker.o: decisionmaker.h
../cards/cards.o: ../cards/cards.h

.PHONY: clean #test

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f player
	rm -f decisionmaker_test
	rm -f decisionmaker_test_data
	rm -f core