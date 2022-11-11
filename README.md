# CS50 Final Project
## Rory Doyle, Asher Vogel, Nate Roe, Eli Rosenberg

This is the blackjack project group 14 for CS50 Fall 2022. 

## Requirements 
The requirements for this project were outlined on the course webpage and in class. 

## Design
The design for this project was broken into four modules to make it easier to complete as a group. These modules were:
- Network - server code
- Dealer - driver for playing the game
- Player - algorithm to play and train
- Cards - data structures used in game

## Implementation
See implementation specifications for details concerning each module listed above. 

## Testing
All methods written were unit tested. In addition, testing consisted of integrating the already unit tested methods and testing their interactions. 



The assignment is in a [public repo](https://github.com/cs50-2022-fall/project).
Do not clone that repo; view it on GitHub.  One person from your team should accept the assignment from GitHub classroom.
Watch if there for any commits that may represent updates to the assignment or specs.

See the course web site for [detailed description of the project](https://www.cs.dartmouth.edu/~tjp/cs50/project/index.html)

Add here any assumptions you made while writing the solution, or any ways in which you know your implementation fails to work.

## Usage

Run `make` from the home directory.
In one terminal window, navigate to the dealer directory `./dealer-given 1 *num_games* 8094`.
In another terminal window, navigate to the player directory and run `./player Asher 129.170.64.104 8094 ../data/training`.

## Known Problems

We found no memory leaks, but received a few errors that don't seem to impact the program's functionality. The output of this valgrind testing can be found in a file called `testing.out` within the `player` directory. The errors are related to the functions `read`, `send`, and `close` that work with the socket and and networking component of the project.

Also, depending on the speed setting of the server, sometimes we are unable to run valgrind, but we were able to get around this problem by running our player against our own server where we can control the speed.