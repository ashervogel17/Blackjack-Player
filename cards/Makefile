# Makefile for 'bag' module
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019
# CS 50, Fall 2022

OBJS = cardstest.o cards.o 
LIBS = ../libcs50/libcs50-given.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

cardstest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

cardstest.o: cards.h ../libcs50/counters.h
cards.o: cards.h

.PHONY: clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f cardstest
	rm -f core