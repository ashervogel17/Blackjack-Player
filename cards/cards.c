/* 
 * cards.c - CS50 'cards' module for blackjack game
 *
 * see cards.h for more information.
 *
 * Nate Roe, November 2022
 * CS 50, Fall 2022
 */

/*  include statements  */
#include "cards.h"

/**************** file-local global variables ****************/
/* none */
const int CARDS_IN_DECK = 52;
const int MAX_CARDS_IN_A_HAND = 22; // draw all aces at ace value = 1 and hit again to bust with 22 card hand
const int MAX_CARD_VALUE = 11;  //  maximum card value is 11 (corresponding to an ace of value = 11)
const int MIN_CARD_VALUE = 2;   //  corresponding to a 2 (Ace = 1 is a special case not considered here)
const int NUM_SUITS = 4;  //  number of suits
/**************** local types ****************/


/**************** global types ****************/
typedef struct card {
  int value;  //  value of the card 0-11 (ace can be valued @ 1 or @ 11)
  char *suit; //  tracks the suit "C" (Clubs), "D" (Diamonds), "H" (Hearts), "S" (Spades)
  char *rank; //  tracks the name of the card ex: "J" (Jack), "Q" (Queen), "2" (two), "A" (Ace)
} card_t;


typedef struct hand {
  card_t *currentHand; // array of pointers with size = MAX_CARDS_IN_A_HAND to card_t type 
  int valueOfhand;  //  value of hand; computed by the handCalculate fxn 
} hand_t;

/**************** global functions ****************/

/**************** bag_new() ****************/
/* see cards.h for description */
card_t* cardNew()
{
  //  initialize variables
  card_t *returnCard = NULL;  //  card struct to be returned
  int cardValue = 0;  //  tracks the card value
  int suitCounter = 0;  //  tracks the suit 

  //  1. allocate memory for the card
  returnCard = malloc(sizeof(card_t)); 

  if (returnCard == NULL) {
    fprintf(stderr, "failed to create card\n");
    return NULL;
  } 

  //  2. set the value, suit, and rank of the card
  
  //  set the value of the card (2-11)
  for (cardValue = MIN_CARD_VALUE; cardValue <= MAX_CARD_VALUE; cardValue++)  {
    returnCard->value = cardValue;  //  assign card value
    // reset cardValue if approaching maximum
    if (cardValue == MAX_CARD_VALUE)  {cardValue = MIN_CARD_VALUE;}
  }

  //  set the suit of the card "C" (Clubs), "D" (Diamonds), "H" (Hearts), "S" (Spades)
  for (suitCounter = 0; suitCounter < NUM_SUITS; suitCounter++)  {
    
    switch(suitCounter) {
      case 0: //  clubs "C" case 
        strcpy(returnCard->suit, "C");
        break;
      case 1: //  diamonds "D" case 
        strcpy(returnCard->suit, "D");
        break;
      case 2: //  hearts "H" case 
        strcpy(returnCard->suit, "H");
        break;
      case 3: //  spades "S" case 
        strcpy(returnCard->suit, "S");
        break;
    }

    //  reset suitCounter to ensure for loop doesn't exit 
    if (suitCounter == (NUM_SUITS - 1)) {suitCounter = 0;}

    }




}

/**************** local functions ****************/
/* not visible outside this file */


/**************** bag_insert() ****************/
/* see bag.h for description */


