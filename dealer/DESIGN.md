## CS50 Blackjack Project Dealer
## Design Specification

This is the design specification for the dealer program for the CS50 blackjack project. It includes: 

- User interface
- Inputs and outputs
- Functional decomposition into modules
- Pseudocode for logical flow
- Major data structures
- Testing plan

## User interface
The user interface does not include any command line arguments. 

Usage: 
```bash
$ ./dealer
```

## Inputs and outputs
There are no inputs and outputs for dealer. 

## Functional decomposition into modules
The dealer program is broken into two main modules: 

1. *main* - driver to initialize and start game
2. *play* - method to send, receive, and parse messages

## Pseudocode for logical flow 
The dealer will run as follows:

1. Main: 
```c
set up server
wait for connection
create data structures
while game is ongoing: 
    call method to play game
```

2. Play: 
```c
send messsage to begin
wait for response 
based on response: 
    send according messages 
calculate game result 
send game result
```

## Major data structures
- *server* - stores and sets up server 
- *card* - card struct from card.h
- *hand* - hand struct from card.h
- *deck* - deck struct from card.h

## Testing plan 
Testing for dealer will be highly integrated with testing for the client side of the server. Before connections can be made, testing can include: 

1. testing cards methods integration in a typical game flow
2. hard coding messages to "send" or "receive" to test logic
3. hard code values of games to see if logic of game result is functional

Once the client side is complete, testing can begin for normal operation. 
