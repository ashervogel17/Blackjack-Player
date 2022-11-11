# CS50 blackjack Final Project
## Design Specification -- player module 

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and focus on the implementation-independent design decisions.  Here we focus on:

- User interface
- Inputs and outputs
- Functional decomposition into modules
- Pseudo code (plain English-like language) for logic/algorithmic flow
- Major data structures
- Testing plan

## User interface

As described in the [Requirements Spec](REQUIREMENTS.md), the player's only interface with the user is on the command-line; it must always have three arguments.

```bash
$ ./player name IPAdress port decisionmakerFilename
```

For example, to train the player by updating the decisonmaker hashtable of game outcomes for given game "states", use this command line:

``` bash
./player Asher 129.170.64.104 8094 ../data/training training
```

## Inputs and outputs

*Input:* the decionmakerFilename is an input from which the player can load training data related to choosing the best gameplay choice for each game

*Output:* The dealer program will tell the player module whether they WIN, LOOSE, BUST, or PUSH and the player will output the result


## Functional decomposition into modules -- player

We anticipate the following modules or functions for the player.c module:

 1. *parseArgs*, which parses arguments 
 2. *play*, which establishes a server connection, sends gameplay messages to facilitate gameplay, and updates the values of the decisionmaker hashtable of gameplay decision choices

 ## Functional decomposition into modules -- decisionmaker

We anticipate the following modules or functions for the decisionmaker.c module. Note the decisionmaker table is a wrapper of the hashtable data structure from cs50 and contains the following information

 *      the keys represent the current state of the blackjack game
 *      the items are structs that store:
 *          number of hands won when staying
 *          number of hands won when hitting
 *          number of hands played when staying
 *          number of hands played when hitting



 1. *decisionmaker_new*, creates decisionmaker table
 2. *decisionmaker_insert*, inserts the decisionmaker table outcomes into the given decisionmaker 
 3. *decisionmaker_find*, returns the decision outcomes associated with the given state.
 4. *decisionmaker_decide*, function used for tournament gameplay; decides the optimal move given a current state 
 5. *decisionmaker_update*, updates the average reward for a given action in a given gameplay state
 6. *decisionmaker_save*, save the decisionmaker to the disc via the decisionmakerFilename
 7. *decision_outcomes_new*, creates new decision outcomes and initializes values to corresponding parameters in decisionmaker


## Pseudo code for logic/algorithmic flow

* The player will: 

1. parse the command line arguments 
2. establish a connection to the server 
3. receive gameplay messages from the dealer and communicate over the server 
4. update the decisionmaker gameplay logic hashtable 
5. output the gameplay 

## Major data structures

- *decisionmaker* see above data structure
- *decisionmaker_outcomes* outcomes of decisionmaker structure