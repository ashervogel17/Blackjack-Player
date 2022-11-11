# Makefile for 'dealer' module
#
# Rory Doyle, the man
# CS 50, Fall 2022

OBJS = dealer.o ../cards/cards.o ../network/serverNetwork.o
L1 = ../libcs50
L2 = ../network
LIBS = $(L1)/libcs50-given.a $(L2)/network.a




CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$(L1) -I$(L2)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

dealer: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

dealer.o: ../cards/cards.h ../network/serverNetwork.h
./cards/cards.o: ../cards/cards.h
../network/serverNetwork.o: ../network/serverNetwork.h

.PHONY: clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f dealer
	rm -f core