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
#include "../cards/cards.h"

/*****************local types*********************/
typedef struct deck {
    int numberOfCards; 
    bool shuffled; 
    card_t** cards; 
} deck_t; 

typedef struct player {
    hand_t* hand; 
    card_t** cards; 
    int valueOfHand; 
} player_t; 

/*************function prototypes*****************/
deck_t* createDeck(); 
void deleteDeck(deck_t* deck); 
void shuffleDeck(deck_t* deck); 

/******FXN DEFINITIONS*******/

deck_t* createDeck() {
    
    deck_t* deck = malloc(sizeof(deck_t)); // allocate memory for the deck
    
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

void deleteDeck(deck_t* deck) {

    for (int i = 0; i < CARDS_IN_DECK; i++) {
        if (deck -> cards[i] != NULL) {
            free(deck -> cards[i]); 
        }
    }

    free(deck); 
}

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


int main(const int argc, char* argv[]) {

    if (argc != 1) {
        fprintf(stderr, "usage: %s \n", argv[0]); 
        exit(1); 
    }

    player_t* player; 
    player_t* dealer; 
    
    deck_t* deck = createDeck(); 
    // deleteDeck(deck); 

    return 0;

}