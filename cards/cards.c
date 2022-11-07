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

//   1 = "2" (Two)
//   3 = "3" (Three)
//  ....
//   10 = "J" (Jack)
//   11 = "Q" (Queen)
//  ...
//   13 = "A" (Ace)

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
      strcpy(returnRank, "10");
      break;
    case 10:
      strcpy(returnRank, "J");
      break;
    case 11:
      strcpy(returnRank, "Q");
      break;
    case 12:
      strcpy(returnRank, "K");
      break;
    case 13: 
      strcpy(returnRank, "A");
      break;
    
    default: 
      fprintf(stderr, "value of rankCount is outside the 1-12 scope to choose the correct rank\n");
  }
  return(returnRank);
}

/**************** global function bodies ****************/



/*******************cardParse()*******************/
//  see cards.h for explanation
card_t *cardParse(char *cardString)
{
  //  initialize vars
  card_t *cardFromString; //  card structure to be returned ; caller responsible for later freeing()
  char *cardStringCopy; //  copy of passed in card 
  char *rankUnFixed;  //  rank; un-fixed to match correct card_t structure formatting
  char *rankFixed;  // the fixed rank formatted according to the card_t structure (ex: "K" from 'unfixed' "King")
  char *suitUnFixed;  //  suit; un-fixed to match correct card_t structure formatting
  char *suitFixed;  // the fixed suit formatted according to the card_t structure (ex: "C" from 'unfixed "Clubs" )
  
  char *ofString; //  string to capture the "of" component of a card name (ex: Queen "of" Clubs)

  int suitCount = 0; // for tracking the suit 
  int rankCount = 0; // for tracking the rank

  //  allocate space for cardString copy 
  cardStringCopy = malloc(  sizeof(char) *  (strlen(cardString) + 1)  );  //  allocate space for string copy
  //  defensive check
  if (cardStringCopy == NULL) {
    fprintf(stdout, "failed to allocate memory for copied cardString information\n");
    return NULL;
  }

  //  copy cardString to cardStringCopy
  bool stringCopySuccess = strncpy(cardStringCopy, cardString, (strlen(cardString) + 1);

  //  defensive check
  if (!stringCopySuccess) {
    fprintf(stderr, "failed to copy cardString information\n");
    return NULL; 
  }

  // allocate space for rank 
  rankUnFixed = malloc(  sizeof(char) * MAX_SUIT_LETTERCOUNT );  //  allocate space for rank un-fixed
  //  defensive check
  if (rankUnFixed == NULL) {
    fprintf(stdout, "failed to copy allocate space for Rank\n");
    return NULL;
  }

  // allocate space for "of" string 
  ofString = malloc(  sizeof(char) * MAX_SUIT_LETTERCOUNT );  //  allocate space for rank un-fixed
  //  defensive check
  if (ofString == NULL) {
    fprintf(stdout, "failed to copy allocate space for 'of' string\n");
    return NULL;
  }

  // allocate space for suit
  suitUnFixed = malloc(  sizeof(char) * MAX_SUIT_LETTERCOUNT );  //  allocate space for rank un-fixed
  //  defensive check
  if (suitUnFixed == NULL) {
    fprintf(stdout, "failed to copy allocate space for suit\n");
    return NULL;
  }

  //  read and parse the string for desired contents 
  int readStrings = sscanf(cardStringCopy, "%s %s %s", rankUnFixed, ofString, suitUnFixed);
  if (readStrings != 3) {
    fprintf(stderr, "failed to read rank, of, suit from cardstring\n");
    return NULL;
  }

  // allocate memory for the added card 
  cardFromString = malloc(sizeof(card_t));
  if (cardFromString == NULL) {
    fprintf(stderr, "failed to allocate memory for the card added for the read string\n");
    return NULL;
  }
  
  // fix the card suit
  
  if (!strcpy(suitUnFixed, "Clubs"))  {
    suitCount = 1; // set the index for the suit; to ensure proper function of suitChoose fxn
    suitFixed = suitChoose(suitCount); // get the suit 
    strcpy(cardFromString->suit,suitFixed); // add the suit to the card
  }

  if (!strcpy(suitUnFixed, "Diamonds"))  {
    suitCount = 2; // set the index for the suit; to ensure proper function of suitChoose fxn
    suitFixed = suitChoose(suitCount); // get the suit 
    strcpy(cardFromString->suit,suitFixed); // add the suit to the card
  }

  if (!strcpy(suitUnFixed, "Hearts"))  {
    suitCount = 3; // set the index for the suit; to ensure proper function of suitChoose fxn
    suitFixed = suitChoose(suitCount); // get the suit 
    strcpy(cardFromString->suit,suitFixed); // add the suit to the card
  }

  if (!strcpy(suitUnFixed, "Spades"))  {
    suitCount = 4; // set the index for the suit; to ensure proper function of suitChoose fxn
    suitFixed = suitChoose(suitCount); // get the suit 
    strcpy(cardFromString->suit,suitFixed); // add the suit to the card
  }

  // fix the card rank
  
  if (!strcpy(rankUnFixed, "Two"))  {
    rankCount = 1; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 0; 
  }

  if (!strcpy(rankUnFixed, "Three"))  {
    rankCount = 2; // set the index for the rankt; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 1; 
  }

  if (!strcpy(rankUnFixed, "Four"))  {
    rankCount = 3; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 2; 
  }

  if (!strcpy(rankUnFixed, "Five"))  {
    rankCount = 4; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 3; 
  }

  if (!strcpy(rankUnFixed, "Six"))  {
    rankCount = 5; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 4; 
  }

  if (!strcpy(rankUnFixed, "Seven"))  {
    rankCount = 6; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 5; 
  }

  if (!strcpy(rankUnFixed, "Eight"))  {
    rankCount = 7; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 6; 
  }

  if (!strcpy(rankUnFixed, "Nine"))  {
    rankCount = 8; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 7; 
  }

  if (!strcpy(rankUnFixed, "Ten"))  {
    rankCount = 9; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 8; 
  }

  if (!strcpy(rankUnFixed, "Jack"))  {
    rankCount = 10; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 9; 
  }

  if (!strcpy(rankUnFixed, "Queen"))  {
    rankCount = 11; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 10; 
  }

  if (!strcpy(rankUnFixed, "King"))  {
    rankCount = 12; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 11; 
  }

  if (!strcpy(rankUnFixed, "Ace"))  {
    rankCount = 12; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 12; 
  }

  return (cardFromString);
}
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

  //  2. allocate space for all of the cards
  newHand->currentHand = malloc(sizeof(card_t*) * MAX_CARDS_IN_A_HAND);
  
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

  hand_t *newHand = handNew();
  return 0;
}




