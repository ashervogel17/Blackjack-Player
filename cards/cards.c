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

//  DECK INFO
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

/**************** local types ****************/

/**************** global types ****************/
typedef struct card {
  int value;  //  value of the card 0-11 (ace can be valued @ 1 or @ 11)
  char *suit; //  tracks the suit "C" (Clubs), "D" (Diamonds), "H" (Hearts), "S" (Spades)
  char *rank; //  tracks the name of the card ex: "J" (Jack), "Q" (Queen), "2" (two), "A" (Ace)
} card_t;

typedef struct hand {
  card_t **currentHand; // array of pointers with size = MAX_CARDS_IN_A_HAND to card_t type 
  int valueOfhand;  //  value of hand; computed by the handCalculate fxn 
} hand_t;

/**************** local function prototypes ****************/
/* not visible outside this file */
char *suitChoose(int suitCount);
char *rankChoose(int rankCount);

/**************** local function bodies ****************/
/* not visible outside this file */

//  suitChoose 
//   the following function will take in the integer count associated with the suit counters_t object 
//   and based on the count, choose a suit for a new card according to the following scheme based on the value of suitCount: 

//   1 = "C" (Clubs)
//   2 = "D" (Diamonds)
//   3 = "H" (Hearts)
//   4 = "S" (Spades)

// caller must later free character
char *suitChoose(int suitCount) 
{
  char *returnSuit = NULL;  //  string to return 
  returnSuit = malloc(sizeof(char)*2);  // locally malloc a char
  
  //  defensive check
  if (returnSuit == NULL) {
    fprintf(stderr, "failed to assign a suit\n");
    return NULL;
  }

  switch(suitCount) 
  {
    case 1: 
      strcpy(returnSuit, "C");  //  clubs
      break;
    case 2: 
      strcpy(returnSuit, "D");  //  diamonds
      break;
    case 3:
      strcpy(returnSuit, "H");  //  hearts
      break;
    case 4:
      strcpy(returnSuit, "S");  //  spades
      break;
    
    default: 
      fprintf(stderr, "value of suitCount is outside the 1-4 scope to choose the correct suit\n");
  }
  return(returnSuit);
}


//  rankChoose 
//   the following function will take in the integer count associated with the rank counters_t object 
//   and based on the count, choose a rank for a new card according to the following scheme based on the value of rankCount: 

//   2 = "2" (Two)
//   3 = "3" (Three)
//  ....
//   10 = "J" (Jack)
//   11 = "Q" (Queen)

// caller must later free character
char *rankChoose(int rankCount) 
{
  char* returnRank = NULL;  //  string to return 
  returnRank = malloc(sizeof(char)*2);  // locally malloc a char
  //  defensive check
  if (returnRank == NULL) {
    fprintf(stderr, "failed to assign a suit\n");
    return NULL;
  }

  switch(rankCount) 
  {
    case 1: 
      strcpy(returnRank, "2");
      break;
    case 2: 
      strcpy(returnRank, "3"); //  3
      break;
    case 3:
      strcpy(returnRank, "4");
      break;
    case 4:
      strcpy(returnRank, "5");
      break;
    case 5:
      strcpy(returnRank, "6");
      break;
    case 6:
      strcpy(returnRank, "7");
      break;
    case 7:
      strcpy(returnRank, "8");
      break;
    case 8:
      strcpy(returnRank, "9");
      break;
    case 9:
      strcpy(returnRank, "J");
      break;
    case 10:
      strcpy(returnRank, "Q");
      break;
    case 11:
      strcpy(returnRank, "K");
      break;
    case 12: 
      strcpy(returnRank, "A");
      break;
    
    default: 
      fprintf(stderr, "value of rankCount is outside the 1-12 scope to choose the correct rank\n");
  }
  return(returnRank);
}
//  createDeck fxn
// initializes counters of
//  creates an array of pointers to type cards_t

/**************** global function bodies ****************/

/**************** cardNew() ****************/
/* see cards.h for description */
card_t* cardNew(counters_t *valCount, counters_t *suitCount, counters_t *rankCount)
{
  //  initialize variables
  card_t *returnCard = NULL;  //  card struct to be returned
  int countValue = 0;  // value count 
  int countSuit = 0;  // suit count 
  int countRank = 0;  // rank count
  bool rslt = false;  // for counters_set checking; default to false
  //  1. allocate memory for the card
  returnCard = malloc(sizeof(card_t)); 

  if (returnCard == NULL) {
    fprintf(stderr, "failed to create card\n");
    return NULL;
  } 

  //  2. grab valueCount (card value (2-11))
  countValue = counters_get(valCount, VAL_COUNTER_ID);
  fprintf(stdout, "cardNew(), countValue = %d\n", countValue);
  if (countValue == MAX_CARD_VALUE) {
    returnCard->value = countValue; //  populate card value 
    rslt = counters_set(valCount, VAL_COUNTER_ID, 1); // reset card suit index 
    if (rslt == false)  {
      fprintf(stdout, "issue resettting valueCount\n");
      return NULL;
    }
  } else  {
      returnCard->value = countValue; //  populate card value 
      countValue = counters_add(valCount, VAL_COUNTER_ID);  //  increment counter
  }  

  //  3. grab suit 
  countSuit = counters_get(suitCount, SUIT_COUNTER_ID);
   fprintf(stdout, "cardNew(), suitValue = %d\n", countSuit);
  if (countSuit == NUM_SUITS) {
    returnCard->suit = suitChoose(countSuit); //  populate card suit
    rslt = counters_set(suitCount, SUIT_COUNTER_ID, 1); // reset card suit index  
    if (rslt == false)  {
      fprintf(stdout, "issue resettting suitCount\n");
      return NULL;
    }
  } else  {
      returnCard->suit = suitChoose(countSuit); //  populate card suit
      countSuit = counters_add(suitCount, SUIT_COUNTER_ID);  //  increment counter
  }  


  //  4. grab rank 
  countRank = counters_get(rankCount, RANK_COUNTER_ID);
   fprintf(stdout, "cardNew(), countRank = %d\n", countRank);
  if (countRank == MAX_CARD_RANK) {
    returnCard->rank = rankChoose(countRank); //  populate card rank
    rslt = counters_set(rankCount, RANK_COUNTER_ID, 1); // reset card value index  
    if (rslt == false)  {
      fprintf(stdout, "issue resettting rankCount\n");
      return NULL;
    }
  } else  {
      returnCard->rank = rankChoose(countRank); //  populate card rank
      countRank = counters_add(rankCount, RANK_COUNTER_ID);  //  increment counter
  }  

  return(returnCard);
}



/**************** handNew() ****************/
hand_t *handNew()
{
  //  1.  allocate space for the hand datastructure 
  hand_t *newHand = malloc(sizeof(hand_t));
  mem_assert(newHand, "failed to allocate space for hand\n");
  
    //  defensive programming 
    if (newHand ==  NULL) {
      fprintf(stderr, "failed to successfully create hand data structure\n");
      return NULL;
    }
    return(newHand);
}
/**************** main() for testing ****************/

int main(int argc, char *argv[]) {
  
  //  initialize counters objects to be passed to cardNew()
  counters_t *valCount = counters_new();
  counters_t *suitCount = counters_new();
  counters_t *rankCount = counters_new();

  // add relevant counters keys for value, suit, and rank
  counters_add(valCount, VAL_COUNTER_ID);
  counters_add(suitCount, SUIT_COUNTER_ID);
  counters_add(rankCount, RANK_COUNTER_ID);
  
  //  create a card
  card_t *newCard = cardNew(valCount, suitCount, rankCount);

  return 0;
}




