#!/bin/bash
#
# File: train_server.sh
# 
#
# Asher Vogel
# CS 50, Fall 2022


#first run the following:
# make
# mygcc -o server serverTest.c serverNetwork.c ../cards/cards.c

for i in {1..20}
do
    ./server
    sleep 30
done

exit 0