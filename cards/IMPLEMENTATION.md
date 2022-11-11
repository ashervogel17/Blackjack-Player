# CS50 Final Project Cards Module
## Implementation Specification

Implementation may include many topics; not all are relevant to the cards module of the blackjack player.
Here we focus on the core subset:

-  Data structures
-  Control flow: pseudo code for overall flow, and for each of the functions
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan

## Data structures 

We use three data structures: a 'card' that contains the card information, a 
'hand' which contains the set of cards held by the game player, and a 'deck' which contains the cards currently available for use by the game players.

Each card has value (2-11) of a card, 'suit' (Clubs, Diamonds, Hearts, Spades), and 'rank' which captures the item described by the card (ex: five of diamonds has 'rank' of five).

Each hand contains the player's set of cards (array of pointers to cards), the computed value of the hand, and an integer tracking the number of cards in the hand. 

Each deck contains an array of pointers to cards, a boolean indicateding whether or not the deck is shuffled, and an integer tracking the number of cards in the deck.

## Control flow

The cards module is implemented in one file `cards.c`, with 24 non-helper functions across the card, hand, and deck functionality. To analyze each of the functions, we will sort by card, hand, and deck-oriented functions

### card fxn 1: cardNew()
* for a given char *rank, and char *suit passed to the function, the cardNew() function will return a pointer to a new "card" structure if the passed rank and suit are valid. Otherwise, the function will return NULL. We note that the caller is responsible for later freeing allocated space for the card via the cardDelete() function.

### card fxn 2: cardParse()
* For a given string passed to the function of the form "Rank of Suit" where 'Rank' represents the rank of a card defined above and 'Suit' represents the suit of the card. The function parses the string to extract the rank and suit and from these read strings creates and returns a pointer to a card. The caller is responsible for freeing the cardString. 

### card fxn 3: cardGetValue()
* This is a simple 'getter' function which extracts the value componenet from a card data structure.

### card fxn 4: cardGetSuit()
* This is a simple 'getter' function which extracts the suit componenet from a card data structure.

### card fxn 5: cardGetRank()
* This is a simple 'getter' function which extracts the rank componenet from a card data structure.

### card fxn 5: cardDelete()
* This is a simple delete function for a card which frees the allocated memory associated with a passed-in card.

### card fxn 5: cardGetName()
* This is a simple function which returns a string-formatted version of a card structure based on the rank and suit information for a given card. For example, if a card has a rank of 7 and a suit of clubs, the function will output "Seven of Clubs"

### card fxn 5: cardPrint()
* This function prints the contents of a card, the rank, suit, and value of the card. 

### hand fxn 1: handNew()
* This function is responsible for creating an empty hand structure, and it returns NULL if the function cannot allocate memory. We note that the caller of handNew() is responsible for later freeing the allocated memory with handDelete().

### hand fxn 2: handGetCards()
* This simple getter function extracts the array of cards_t * pointers contained in a given hand. 

### hand fxn 3: handGetValueOfHand()
* This simple getter function extracts the computed "value" of the hand based on the computed value of the cards contained in the hand.  

### hand fxn 4: handGetNumberOfCards()
* This simple getter function extracts the number of cards in the hand.

### hand fxn 5: handSortedString()
* This program intakes a valid hand structure and passes out a string with one word for each card's rank sorted in ascending order, ex: "Two Nine Queen." The passed hand is unaffected by this function and the caller is responsible for later freeing the returned string. 

### hand fxn 6: handaddCard()
* This function adds a card from the deck to the player's hand structure by passing in a valid hand and card. Within the function, the handCalculateValue function is called which computes the optimal value of the hand based on whether or not the ace value is set to = 1 or set to = 11. 

### hand fxn 7: handCalculateValue()
* For a given hand pointer, the function computes the sum total value of the cards in the hand based on the (2-11) value ranking system for cards and decides if based on the presence or absence of aces within the hand, whether the optimal score for the hand is achieved by setting aces = 11 or setting aces = 1.

### hand fxn 8: handDelete()
* This function deletes the hand and is called in concert with deckDelete().

### hand fxn 9: handPrint()
* This function prints the cards in a hand to stdout. 

### hand fxn 9: handPrint()
* This function prints the cards in a hand to stdout. 

### deck fxn 1: deckNew()
* This function allocates memory for a newDeck and populates the deck array of pointers to cards structures by calling the cardNew() function. The function returns a deck object and initializes the bool value of the deck as shuffled to "false." The deckNew() function also initializes the number of cards in the deck to 52. 

### deck fxn 2: deckGetNumberOfCards()
* This simple 'getter' function extracts from the deck the number of cards currently contained in the deck. Note that when a card is dealt from the deck, the number of cards in the deck is decremented to reflect the action.

### deck fxn 3: deckIsShuffled()
* This simple 'getter' function determines whether the deck is shuffled  by returning a bool.  

### deck fxn 4: deckGetCards()
* This simple 'getter' function extracts the array of cards contained in the deck structure. 

### deck fxn 5: deckShuffle()
* This function will reorganize the deck and shuffle the cards within the deck. That is this function will take and reorder the cards contained within the deck. 

### deck fxn 5: deckDealRandomCard()
* This function will 1: check that the deck is shuffled. If the deck is not shuffled, shuffle it and remove one card from the "top" of the deck. For example if the deck has 52 cards, the deal function will pop off the 51st card and return or "deal" out a pointer to the "popped" card.  

### deck fxn 6: deckDelete()
* This function will free all the memory associated with the deck


## Function prototypes

```c
/*card methods*/

/* Create a new card structure
 *
 * Caller provides:
 *      a rank (Ace, Two, Three, ..., Ten, Jack, Queen, King)
 *      a suit (Diamonds, Hearts, Clubs, Spades)
 * We return:
 *   a pointer to a new "card" structure if the rank and suit are valid
 *   NULL if any parameters are NULL or if the rank or suit are invalid
 * We guarantee:
 *   The card is assigned at creation (ex: 2 of clubs)
 * Caller is responsible for:
 *   later freeing allocated space for the card via cardDelete()
 */
card_t* cardNew(char* rank, char* suit);

/**
 * Caller provides:
 *      valid cardString (e.g. Seven of Diamonds, King of Spades, etc.)
 * We return:
 *      a card struct corresponding to the given cardString
 *      NULL if the cardString is invalid or NULL
 * Notes:
 *      the caller is responsible for freeing cardString
 *      the caller is responsible for freeing the card struct's memory later with cardDelete()
 */
card_t* cardParse(char *cardString);

/* simple getter for card value */
int cardGetValue (card_t* card);

/* simple getter for card suit */
char* cardGetSuit (card_t* card); 

/* simple getter for card rank */
char* cardGetRank (card_t* card);

/**
 * Caller provides:
 *      card struct
 * We do:
 *      free the memory used by this struct
 *      free the pointer to the struct
 * */
void cardDelete (card_t* card); 

/**
 * Caller provides:
 *      card struct
 * We return:
 *      the name of the card (e.g. Seven of Diamonds, Four of Hearts, Queen of Spades)
 * Notes:
 *      the card struct is unaltered
 *      the caller is responsible for freeing the string we return
 * */
char* cardGetName(card_t* card);

/**
 * Caller provides:
 *      card struct
 * We print:
 *      the name of the card
 * Notes:
 *      the card struct is unaltered
 *      this function frees all memory is allocates
 * */
void cardPrint(card_t* card);



/*hand methods*/

/**
 * Create an empty hand struct (returns NULL if function cannot allocate memory)
 * Caller is responsible for calling handDelete()
 * */
hand_t* handNew();

/* simple gett for hand cards */
card_t** handGetCards (hand_t* hand); 

/* simple getter for hand value */
int handGetValueOfHand(hand_t* hand);

/* simple getter for hand number of cards */
int handGetNumberOfCards (hand_t* hand);

/**
 * Caller provides:
 *      valid hand struct
 * We return:
 *      a string with one word for each card's rank sorted in ascending order (e.g. "Two Nine Queen")
 * Notes:
 *      hands is unaltered by this function
 *      the caller is responsible for freeing the returned string
 * */
char* handSortedString(hand_t* hand);

/**
 * The caller provides:
 *      valid hand
 *      valid card
 * We do:
 *      add the card to the hand array
 * Notes:
 *      the card is unaffected
 * */
bool handAddCard (hand_t* hand, card_t* card);

/**
 * The caller provides:
 *      valid hand
 * We do:
 *      set the hand's value within the struct to the value of the hand (accounts for soft aces)
 * */
void handCalculateValue(hand_t* hand); 

/**
 * Frees all memory associated with the hand
 * */
void handDelete (hand_t* hand);  

/**
 * Prints the cards in a hand to stdout
 * Hand is unaffected
 * */
void handPrint(hand_t* hand);



/*deck methods*/

/**
 * Build and return a deck struct
 * Intialize cards to an array with 52 cards (like a real deck)
 * Intialize shuffled to false
 * Initialize number of cards to 52
 * */
deck_t* deckNew();

/* simple getter for deck number of cards */
int deckGetNumberOfCards (deck_t* deck);

/* simple getter for deck shuffled */
bool deckIsShuffled (deck_t* deck);

/* simple getter for deck cards */
card_t** deckGetCards (deck_t* deck); 

/**
 * Caller provides:
 *      a deck struct
 * We do:
 *      shuffle the cards in the deck (put the same cards in a different order)
 * */
void deckShuffle(deck_t* deck);

/**
 * Caller provides:
 *      a deck struct
 * We do:
 *      check that the deck is shuffled - if not, shuffle it
 *      remove one card from the deck and return it
 *      decrement number of cards
 * */
card_t* deckDealRandomCard(deck_t* deck);

/**
 * Free all memory associated with the given deck
 * */
void deckDelete(deck_t* deck); 

```


## Error handling and recovery

All code uses defensive-programming tactics to catch and exit (using variants of the `mem_assert` functions), e.g., if a function receives bad parameters.


## Testing plan

Here is an implementation-specific testing plan.

### Unit testing

For each of the data structures card, hand, and deck along with their respective functions, there are unit tests run. All of the unit testing employs the unittest.h header file from libcs50 and tests for basic functionality as well as memory leaks in the cases of ---new() functions and ---delete() functions

Below is the output of our unit testing

```
Cannot create card with NULL rank
Cannot create card with NULL suit
Cannot create card with suit S
Cannot create card with suit T
PASS test cardNew and cardDelete

Cannot create card with NULL card string
Cannot create card from string Water Buffalo
Cannot create card with rank Thirteen
Cannot create card with suit Buildings
PASS test cardParse

Built hand: 
Ace of Diamonds
Seven of Spades
Jack of Clubs
Ace of Clubs
PASS test handAddCard and handCalculateValue

Card 1: Ace of Diamonds
Card 2: Two of Diamonds
Card 3: Three of Diamonds
Card 4: Four of Diamonds
Card 5: Five of Diamonds
Card 6: Six of Diamonds
Card 7: Seven of Diamonds
Card 8: Eight of Diamonds
Card 9: Nine of Diamonds
Card 10: Ten of Diamonds
Card 11: Jack of Diamonds
Card 12: Queen of Diamonds
Card 13: King of Diamonds
Card 14: Ace of Clubs
Card 15: Two of Clubs
Card 16: Three of Clubs
Card 17: Four of Clubs
Card 18: Five of Clubs
Card 19: Six of Clubs
Card 20: Seven of Clubs
Card 21: Eight of Clubs
Card 22: Nine of Clubs
Card 23: Ten of Clubs
Card 24: Jack of Clubs
Card 25: Queen of Clubs
Card 26: King of Clubs
Card 27: Ace of Spades
Card 28: Two of Spades
Card 29: Three of Spades
Card 30: Four of Spades
Card 31: Five of Spades
Card 32: Six of Spades
Card 33: Seven of Spades
Card 34: Eight of Spades
Card 35: Nine of Spades
Card 36: Ten of Spades
Card 37: Jack of Spades
Card 38: Queen of Spades
Card 39: King of Spades
Card 40: Ace of Hearts
Card 41: Two of Hearts
Card 42: Three of Hearts
Card 43: Four of Hearts
Card 44: Five of Hearts
Card 45: Six of Hearts
Card 46: Seven of Hearts
Card 47: Eight of Hearts
Card 48: Nine of Hearts
Card 49: Ten of Hearts
Card 50: Jack of Hearts
Card 51: Queen of Hearts
Card 52: King of Hearts

TEST DECK SHUFFLE
Card 1: Ace of Diamonds
Card 2: Two of Hearts
Card 3: Three of Diamonds
Card 4: Four of Diamonds
Card 5: Five of Diamonds
Card 6: Six of Diamonds
Card 7: Seven of Diamonds
Card 8: Eight of Clubs
Card 9: Five of Hearts
Card 10: Ten of Diamonds
Card 11: Jack of Diamonds
Card 12: Two of Diamonds
Card 13: Jack of Spades
Card 14: Six of Spades
Card 15: Nine of Diamonds
Card 16: King of Spades
Card 17: Nine of Spades
Card 18: Five of Clubs
Card 19: Six of Clubs
Card 20: Four of Spades
Card 21: Seven of Hearts
Card 22: Nine of Clubs
Card 23: Queen of Diamonds
Card 24: Queen of Hearts
Card 25: Jack of Clubs
Card 26: King of Diamonds
Card 27: Four of Clubs
Card 28: Two of Clubs
Card 29: Three of Spades
Card 30: Three of Clubs
Card 31: King of Hearts
Card 32: Seven of Clubs
Card 33: Seven of Spades
Card 34: Eight of Spades
Card 35: Two of Spades
Card 36: Eight of Hearts
Card 37: Ten of Clubs
Card 38: Queen of Spades
Card 39: Five of Spades
Card 40: Ten of Spades
Card 41: Ace of Spades
Card 42: Three of Hearts
Card 43: Four of Hearts
Card 44: Ace of Hearts
Card 45: Queen of Clubs
Card 46: Ace of Clubs
Card 47: Eight of Diamonds
Card 48: Nine of Hearts
Card 49: Ten of Hearts
Card 50: King of Clubs
Card 51: Six of Hearts
Card 52: Jack of Hearts

TEST DECK DEAL CARD
Size of deck: 52
Jack of Hearts
Size of deck: 51
Hand: Jack of Hearts

PASS test deck functions

PASS all test cases
```