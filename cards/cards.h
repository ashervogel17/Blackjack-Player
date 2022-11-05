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
