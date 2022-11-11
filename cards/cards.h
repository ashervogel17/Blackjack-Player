/* 
 * cards.h - header file for CS50 'cards' module
 * 
 * In the blackjack game the card and the functionality associated with the card is of critical importance.
 * The cards module will implement a series of data structures through several gameplay-related functions.
 * The functions will be described in this document and implemented in the file cards.c
 *
 * Nate Roe, November 2022
 * CS 50, Fall 2022
 */

#ifndef __CARDS_H
#define __CARDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../libcs50/counters.h"

/**************** global types ****************/
typedef struct card card_t;  // card; opaque to users of the module
typedef struct hand hand_t; //  hand; opaque to users of the module 
typedef struct deck deck_t;  // stores the deck of cards as an array of pointers to cards
/**************** file-local global variables ****************/
/* none */

//  DECK INFO
#define CARDS_IN_DECK 52
#define MAX_CARDS_IN_A_HAND 22 // draw all aces at ace value = 1 and hit again to bust with 22 card hand

//  CARD VALUE INFO
#define MAX_CARD_VALUE 11  //  maximum card value is 11 (corresponding to an ace of value = 11)
#define MIN_CARD_VALUE 2   //  corresponding to a 2 (Ace = 1 is a special case not considered here)

//  CARD RANK INFO
#define MAX_CARD_RANK 13   // maximum "rank" index integer corresponding to the value of an Ace
#define MIN_CARD_RANK 1    // smallest index corresponding to a card is 2 for the "2" card
//  CARD SUIT INFO
#define NUM_SUITS 4  //  number of suits

//  counters_t key IDs for value, suit, rank (will be the keys for corresponding counters_t * nodes containing count information needed to generate new cards)
#define VAL_COUNTER_ID 1 
#define SUIT_COUNTER_ID 2 
#define RANK_COUNTER_ID 3 


//  for cardParse 
#define MAX_SUIT_LETTERCOUNT 20
#define MAX_RANK_LETTERCOUNT 20
/**************** functions ****************/

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

/* simple gett for hand value */
int handGetValueOfHand(hand_t* hand);

/* simple gett for hand number of cards */
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





#endif // __CARDS_H