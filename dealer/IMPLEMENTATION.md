## CS50 Blackjack Project Dealer
## Implementation Specification 

This is the implementation specification of my dealer. 
Here we focus on: 

- Data structures
- Control flow: pseudocode for overall flow, and for each of the functions
- Detailed function prototypes and their parameters 
- Error handling and recovery 
- Testing plan 

## Data structures 
We use: 
- card - struct from cards.h
- deck - struct from cards.h
- hand - struct from cards.h
- server_data - struct from network modules

## Control flow 
The dealer is implemented in dealer.c with 2 functions

### 1. main 
main - driver for server and game flow 

### 2. parseServerMessage
parseServerMethod - recieve a message, send messages, and play game accordingly 

Expected: 
- string of message received 
- socket 
- pointers ot a deck and two hands
- boolean to aid in game flow 

Returns: void 

## Function prototypes
```c
void parseServerMessage(char* buffer, int new_socket, deck_t* deck, hand_t* dealerHand, hand_t* playerHand, bool* gameOnGoing);
```

## Structs used 

### 1. server_data 
- struct used to store server data and set up server

### 2. card_t
- struct used to store card data

### 3. hand_t
- struct used to store data for a player's hand

### 4. deck_t
- struct used to store cards in a deck 

## Testing plan
Testing for dealer involved written out methods to test the integration of data structures in a normal game flow. For instance, creating two hands, a shuffled deck, and dealing cards to players. It then consisted of testing the logical comparisons to determine result of the game. Server send methods were then written, and without a client to connect, hard-coded strings were tested to see if proper messages were sent. Then, testing was completed with client-side of the server which was the majority of the testing conducted on dealer. 