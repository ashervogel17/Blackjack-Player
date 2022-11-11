# Makefile for CS50 Tiny Search Engine
#
# Asher Vogel, Nate Roe, Rory Doyle, Eli Rosenberg
# CS 50, Fall 2022

L = libcs50
.PHONY: all clean

############## default: make all libs and programs ##########
# If libcs50 contains set.c, we build a fresh libcs50.a;
# otherwise we use the pre-built library provided by instructor.
all: 
	(cd $L && if [ -r set.c ]; then make $L.a; else cp $L-given.a $L.a; fi)
	make -C network
	make -C cards
	make -C dealer
	make -C player

############### TAGS for emacs users ##########
TAGS:  Makefile */Makefile */*.c */*.h */*.md */*.sh
	etags $^

############## clean  ##########
clean:
	rm -f *~
	rm -f TAGS
	make -C cards clean
	make -C dealer clean
	make -C network clean
	make -C player clean