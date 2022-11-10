#!/bin/bash
#
# File: train_player.sh
# 
#
# Asher Vogel
# CS 50, Fall 2022

# first run make

for i in {1..50}
do
    ./player Asher 129.170.64.104 8094 ../data/training training
    sleep 12
done

exit 0