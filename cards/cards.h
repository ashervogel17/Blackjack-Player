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
#include "../../libcs50/counters.h"
#include "../../libcs50/mem.h"

/**************** global types ****************/
typedef struct card card_t;  // card; opaque to users of the module
typedef struct hand hand_t; //  hand; opaque to users of the module 

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

/**************** cardNew()****************/
/* Create a new card structure .
 *
 * We return:
 *   a pointer to a new "card" structure .
 * We guarantee:
 *   The card is assigned at creation (ex: 2 of clubs)
 * Caller is responsible for:
 *   later freeing allocated space for the card via cardDelete()
 */
card_t* cardNew(counters_t *valCount, counters_t *suitCount, counters_t *rankCount);


/**************** cardParse()****************/
/* Create a new card from a passed in string.
 * receive a string and from that string get the card data
 * parse the string for 3 strings (format: Seven of Hearts, Ace of Diamonds)
 * after parsing the string, allocate memory for a card structure
 * caller is responsible for later freeing the memory for the created card
 * 
 */
hand_t* handNew();


/**************** handNew()****************/
/* Create a new hand structure .
 *
 * We return:
 *   a pointer to a new "hand" structure .
 * We guarantee:
 *   The hand is empty when initialized
 * Caller is responsible for:
 *   later freeing allocated space for the hand via handDelete()
 */
hand_t* handNew();

#endif // __BAG_H
