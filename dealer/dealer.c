/* 
* dealer.c - dealer module for blackjack project
* 
* Rory Doyle, Asher Vogel, Eli Rosenberg, Nate Roe
* CS50, Fall 2022*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "/thayerfs/home/f0055pp/cs50/labs/tse-rorydoyle/libcs50/counters.h"
#include "cards.h"

/********CONSTANT VARIBALES - taken from cards.c from Nate*/
const int CARDS_IN_DECK = 52;
const int MAX_CARDS_IN_A_HAND = 22; // draw all aces at ace value = 1 and hit again to bust with 22 card hand

//  CARD VALUE INFO
const int MAX_CARD_VALUE = 11;  //  maximum card value is 11 (corresponding to an ace of value = 11)
const int MIN_CARD_VALUE = 2;   //  corresponding to a 2 (Ace = 1 is a special case not considered here)

//  CARD RANK INFO
const int MAX_CARD_RANK = 12;   // maximum "rank" index integer corresponding to the value of an Ace
const int MIN_CARD_RANK = 1;    // smallest index corresponding to a card is 2 for the "2" card
//  CARD SUIT INFO
const int NUM_SUITS = 4;  //  number of suits

//  counters_t key IDs for value, suit, rank (will be the keys for corresponding counters_t * nodes containing count information needed to generate new cards)
const int VAL_COUNTER_ID = 1; 
const int SUIT_COUNTER_ID = 2; 
const int RANK_COUNTER_ID = 3; 



/*****************local types*********************/

/* deck_t - stores the deck of cards as an array of pointers to cards. */
typedef struct deck {
    int numberOfCards; 
    bool shuffled; 
    card_t** cards; 
} deck_t; 

/* player_t - stores the hand as an array of pointers to cards. */
typedef struct hand {
    card_t** cards; 
    int valueOfHand;
    int numberOfCards;  
} hand_t; 

typedef struct card {
  int value;  //  value of the card 0-11 (ace can be valued @ 1 or @ 11)
  char *suit; //  tracks the suit "C" (Clubs), "D" (Diamonds), "H" (Hearts), "S" (Spades)
  char *rank; //  tracks the name of the card ex: "J" (Jack), "Q" (Queen), "2" (two), "A" (Ace)
} card_t;


/*************function prototypes*****************/

/*getters for deck*/
int deckGetNumberOfCards (deck_t* deck);
bool deckIsShuffled (deck_t* deck); 
card_t** deckGetCards (deck_t* deck); 

/*getters for hand*/
card_t** handGetCards (hand_t* hand); 
int handGetValueOfHand(hand_t* hand);
int handGetNumberOfCards (hand_t* hand);

/*getters for card*/
int cardGetValue (card_t* card);
char* cardGetSuit (card_t* card); 
char* cardGetRank (card_t* card);

/*other methods*/
deck_t* createDeck(); 
void deleteDeck(deck_t* deck); 
void shuffleDeck(deck_t* deck); 
hand_t* newHand(); 
card_t* dealRandomCard(deck_t* deck); 
bool addCardToHand (hand_t* hand, card_t* card, bool faceUp); 
void calculateHandValue(hand_t* hand); 



int deckGetNumberOfCards (deck_t* deck) { 
    return deck -> numberOfCards; 
}

bool deckIsShuffled (deck_t* deck) {
    return deck -> shuffled; 
}

card_t** deckGetCards (deck_t* deck) {
    return deck -> cards; 
}

card_t** handGetCards (hand_t* hand) {
    return hand -> cards; 
}

int handGetValueOfHand(hand_t* hand) {
    return hand -> valueOfHand; 
}

int handGetNumberOfCards (hand_t* hand) {
    return hand -> numberOfCards; 
}

int cardGetValue (card_t* card) {
    return card -> value; 
}

char* cardGetSuit (card_t* card) {
    return card -> suit; 
}

char* cardGetRank (card_t* card) {
    return card -> rank; 
}


/* createDeck - creates a deck and an array of pointers to cards */
deck_t* createDeck() {
    
    deck_t* deck; 
    
    counters_t* valCount = counters_new(); 
    counters_t* suitCount = counters_new(); 
    counters_t* rankCount = counters_new(); 

    if (valCount == NULL || suitCount == NULL || rankCount == NULL) {
        fprintf(stderr, "Error creating counters.\n"); 
        exit(1); 
    }

    card_t* cards [CARDS_IN_DECK]; 

    for (int i = 0; i < CARDS_IN_DECK; i++) {

        card_t* newCard = cardNew(valCount, suitCount, rankCount); 

        if (newCard == NULL) {
            fprintf(stderr, "Error making card.\n"); 
        }

        cards[i] = newCard; 
        deck -> numberOfCards++; 

        printf("added a card\n");
        printf("number of cards: %d\n", deck -> numberOfCards); 

    }

    deck -> cards = cards; 
    deck -> shuffled = false; 

    counters_delete(valCount); 
    counters_delete(suitCount); 
    counters_delete(rankCount);

    return deck; 
}

/* deleteDeck - delete deck and allocated data stored in it */
void deleteDeck(deck_t* deck) {

    for (int i = 0; i < CARDS_IN_DECK; i++) {
        if (deck -> cards[i] != NULL) {
            cardDelete(deck -> cards[i]); 
        }
    }

    free(deck); 
}

/* shuffleDeck - shuffles deck
* note - implements Fisher-Yates algorithm for generating random permutations based on pseudocode found online */
void shuffleDeck(deck_t* deck) {

    srand(time(NULL)); 
    
    for (int i = CARDS_IN_DECK - 1; i > 0; i--) {

        int j = rand() % (i + 1); 
        
        card_t* cardOne = deck -> cards[i]; 
        card_t* cardTwo = deck -> cards[j]; 
        card_t* tempCard; 

        tempCard = cardOne; 
        cardOne = cardTwo; 
        cardTwo = tempCard; 
    }

    deck -> shuffled = true; 
}

/* newPlayer - create a new player and an array of card pointers for their hand */
hand_t* newHand() {

    hand_t* hand = malloc(sizeof(hand_t)); 

    if (hand == NULL) {
        fprintf(stderr, "Error creating player.\n"); 
        exit(1); 
    }

    card_t* cards [MAX_CARDS_IN_A_HAND]; 
    hand -> cards = cards; 

    hand -> numberOfCards = 0; 
    hand-> valueOfHand = 0; 

    return hand; 
}

/* dealCard - deals a card from the deck to a player */
card_t* dealRandomCard(deck_t* deck) {

    if (deck == NULL) {
        fprintf(stderr, "Error with parameters.\n"); 
        exit(1); 
    }

    if (deck -> shuffled == false) {
        fprintf(stderr, "Error with parameters.\n"); 
        exit(1); 
    }

    if (deck -> numberOfCards == 0) {
        fprintf(stderr, "Error with parameters.\n"); 
        exit(1); 
    }

    int sizeOfDeck = deck -> numberOfCards; 
    card_t* card; 

    card = deck -> cards[sizeOfDeck - 1]; 
    deck -> numberOfCards--; 

    return card; 
}

/* ASHER ALWAYS SET FACEUP TO FALSE! OTHERWISE YOUR CODE WILL TRY TO SEND A MESSAGE OVER THE SERVER */
bool addCardToHand (hand_t* hand, card_t* card, bool faceUp) {
    
    if (hand == NULL || card == NULL) {
        return false; 
    }

    hand -> cards[hand -> numberOfCards] = card; 
    hand -> numberOfCards++; 

    calculateHandValue(hand); 
     
    if (faceUp) {
        //communicate value over the server
    }

    return true; 
}


/* calculateHandValue - calculates the hand value for a player */
void calculateHandValue(hand_t* hand) {
    
    int handValue = 0;
    int numAces = 0;

    for (int i = 0; i < hand -> numberOfCards; i++) {
        card_t* card = hand->cards[i];
        if (card->value == 11) {
            numAces++;
        } 
        handValue += card->value;
    }
    while (handValue > 21 && numAces > 0) {
        handValue -= 10;
        numAces--;
    }
    hand->valueOfHand = handValue;
}






    
