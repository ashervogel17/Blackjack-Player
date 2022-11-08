# Makefile for 'player' module
#
# Asher Vogel
# CS 50, Fall 2022

OBJS = decisionmaker.o player.o cards.o
L = ../libcs50
LIBS = $L/libcs50-given.a

# comment out the following to turn off logging
APPTEST=-DAPPTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) $(APPTEST) -I$L
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

player: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

decisionmaker.o: decisionmaker.h

.PHONY: clean #test

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f player
	rm -f decisionmaker_test
	rm -f decisionmaker_test_data
	rm -f core

# test: player decisionmaker.o
# 	bash -v testing.sh