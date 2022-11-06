# Makefile for dealer for blackjack project
# 
# Rory Doyle
# 
# CS50, Fall 2022

PROG = dealer
OBJ = dealer.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) 
CC = gcc
MAKE = make

$(PROG): $(OBJ)
		$(CC) $(CFLAGS) 

.PHONY: clean


clean: 
		rm -rf *.dSYM
		rm -f *~ *.o
		rm -f $(PROG)