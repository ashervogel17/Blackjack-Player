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

/*************function prototypes*****************/
deck_t* createDeck(); 
void deleteDeck(deck_t* deck); 
void shuffleDeck(deck_t* deck); 
player_t* newPlayer(); 
bool dealCard(player_t* player, deck_t* deck, bool faceUp); 
void calculateHandValue(player_t* player); 
int getDeckSize(deck_t* deck); 
bool isShuffled(deck_t* deck); 
int getHandSize(player_t* player);
int getValueOfHand(player_t* player);  


/*****************local types*********************/

/* deck_t - stores the deck of cards as an array of pointers to cards. */
typedef struct deck {
    int numberOfCards; 
    bool shuffled; 
    card_t** cards; 
} deck_t; 

/* player_t - stores the hand as an array of pointers to cards. */
typedef struct player {
    card_t** hand; 
    int valueOfHand;
    int numberOfCards;  
} player_t; 

/* getDeckSize - getter for size of deck */
int getDeckSize(deck_t* deck) {
    return deck -> numberOfCards; 
}

/* isShuffled - getter for whether deck is shuffled */
bool isShuffled(deck_t* deck) {
    return deck -> shuffled; 
}

/* getHandSize - getter for number of cards player has */
int getHandSize(player_t* player) {
    return player -> numberOfCards; 
}

/* getValueOfHand - getter for value of a player's hand */
int getValueOfHand(player_t* player) {
    return player -> valueOfHand; 
}

/* createDeck - creates a deck and an array of pointers to cards */
deck_t* createDeck() {
    
    deck_t* deck = malloc(sizeof(deck_t)); 
    
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
            free(deck -> cards[i]); 
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
player_t* newPlayer() {

    player_t* player = malloc(sizeof(player_t)); 

    if (player == NULL) {
        fprintf(stderr, "Error creating player.\n"); 
        exit(1); 
    }

    card_t* cards [MAX_CARDS_IN_A_HAND]; 
    player -> hand = cards; 

    player -> numberOfCards = 0; 
    player -> valueOfHand = 0; 

    return player; 
}

/* dealCard - deals a card from the deck to a player */
bool dealCard(player_t* player, deck_t* deck, bool faceUp) {

    if (player == NULL || deck == NULL || player -> hand == NULL) {
        return false; 
    }

    if (deck -> shuffled == false) {
        return false; 
    }

    if (deck -> numberOfCards == 0) {
        return false; 
    }

    int sizeOfDeck = deck -> numberOfCards; 
    card_t* card; 

    card = deck -> cards[sizeOfDeck - 1]; 
    deck -> numberOfCards--; 

    player -> hand[player -> numberOfCards] = card; 
    player -> numberOfCards++; 

    calculateHandValue(player); 
     
    if (faceUp) {
        //communicate value over the server
    }

    return true; 
}

/* calculateHandValue - calculates the hand value for a player */
void calculateHandValue(player_t* player) {

    for (int i = 0; i < player -> numberOfCards; i++) { 
        int currentCardValue = getRank(player -> hand[i]);
        player -> valueOfHand += currentCardValue;  
    }
}


int main(const int argc, char* argv[]) {

    if (argc != 1) {
        fprintf(stderr, "usage: \n", argv[0]); 
        exit(1); 
    }

    player_t* player; 
    player_t* dealer; 
    
    deck_t* deck = createDeck(); 

    if (deck == NULL) {
        fprintf(stderr, "Error making deck.\n");
        return 1;
    }

    shuffleDeck(deck); 



    return 0;

}




    
