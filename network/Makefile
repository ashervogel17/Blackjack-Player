# Makefile for common.a that is required to compile the crawler executable. 
#
# Elias Rosenberg, CS 50, Fall 2022

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
OBJS = clientNetwork.o serverNetwork.o
LIB = network.a


# lib depends on object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)


# object files depend on header files
clientNetwork.o: clientNetwork.h
serverNetwork.o: serverNetwork.h

.PHONY: all clean


clean:
	rm -f $(LIB)
	rm -f *~ *.o
	rm -rf *.dSYM