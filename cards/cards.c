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
  int value;  //  value of the card 2-11 (ace can be valued @ 2 or @ 11)
  char *suit; //  tracks the suit "C" (Clubs), "D" (Diamonds), "H" (Hearts), "S" (Spades)
  char *rank; //  tracks the name of the card ex: "J" (Jack), "Q" (Queen), "2" (two), "A" (Ace)
} card_t;

typedef struct hand {
    card_t** cards; 
    int valueOfHand;
    int numberOfCards;  
} hand_t; 

typedef struct deck {
    int numberOfCards; 
    bool shuffled; 
    card_t** cards; 
} deck_t; 
/**************** local function prototypes ****************/
/* not visible outside this file */
static char *suitChoose(int suitCount);
static char *rankChoose(int rankCount);


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
static char *suitChoose(int suitCount) 
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
static char *rankChoose(int rankCount) 
{
  char* returnRank = NULL;  //  string to return 
  returnRank = malloc(sizeof(char)*4);  // locally malloc a char
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
deck_t* deckNew() {
    
    deck_t* deck = malloc(sizeof(deck_t));  // allocate m 
  
  //  initialize counters objects to be passed to cardNew()
  counters_t *valCount = NULL;
  counters_t *suitCount = NULL;
  counters_t *rankCount = NULL;

  //  initialize the counters
  counters_set(valCount, VAL_COUNTER_ID, 2);  // initialize the valCount to 2 (minimum card value for card = 2)
  counters_set(suitCount, SUIT_COUNTER_ID, 1);
  counters_set(rankCount, RANK_COUNTER_ID, 1);

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


void cardDelete (card_t* card) {
    
    if (card != NULL) {
        free(card -> suit); 
        free(card -> rank); 
        free(card);
    }  
}


/* deleteDeck - delete deck and allocated data stored in it */
void deckDelete(deck_t* deck) {

    for (int i = 0; i < CARDS_IN_DECK; i++) {
        if (deck -> cards[i] != NULL) {
            cardDelete(deck -> cards[i]); 
        }
    }

    free(deck); 
}

/* shuffleDeck - shuffles deck
* note - implements Fisher-Yates algorithm for generating random permutations based on pseudocode found online */
void deckShuffle(deck_t* deck) {

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
hand_t* handNew() {

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
card_t* deckDealRandomCard(deck_t* deck) {

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
bool handAddCard (hand_t* hand, card_t* card, bool faceUp) {
    
    if (hand == NULL || card == NULL) {
        return false; 
    }

    hand -> cards[hand -> numberOfCards] = card; 
    hand -> numberOfCards++; 

    handCalculateValue(hand); 
     
    if (faceUp) {
        //communicate value over the server
    }

    return true; 
}


/* calculateHandValue - calculates the hand value for a player */
void handCalculateValue(hand_t* hand) {
    
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

void handDelete (hand_t* hand) {

    for (int i = 0; i < hand -> numberOfCards; i++) {
        cardDelete(hand -> cards[i]); 
    }

    free(hand); 
}


char* handSortedString(hand_t* hand) {
  if (hand == NULL) {
    return NULL;
  }
  bool added[hand->numberOfCards];
  for (int i=0; i < hand->numberOfCards; i++) {
    added[i] = false;
  }
  char* res = calloc(7*hand->numberOfCards, sizeof(char));
  for (int i=0; i < hand->numberOfCards; i++) {
    char* nextCard = calloc(7, sizeof(char));
    int nextCardVal = 20;
    int nextCardIndex = 0;
    for (int j=0; j < hand->numberOfCards; j++) {
      if (added[j]) {
        continue;
      }
      if (hand->cards[j]->value < nextCardVal) {
        nextCardVal = hand->cards[j]->value;
        strcpy(nextCard, hand->cards[j]->rank);
        nextCardIndex = j;
      }
    }
    strcat(res, nextCard);
    if (i < hand->numberOfCards - 1) {
      strcat(res, " ");
    }
    added[nextCardIndex] = true;
    free(nextCard);
  }
  return res;
}

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
  bool stringCopySuccess = strncpy(cardStringCopy, cardString, (strlen(cardString) + 1));

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
    cardFromString->value = 2; 
  }

  if (!strcpy(rankUnFixed, "Three"))  {
    rankCount = 2; // set the index for the rankt; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 3; 
  }

  if (!strcpy(rankUnFixed, "Four"))  {
    rankCount = 3; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 4; 
  }

  if (!strcpy(rankUnFixed, "Five"))  {
    rankCount = 4; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 5; 
  }

  if (!strcpy(rankUnFixed, "Six"))  {
    rankCount = 5; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 6; 
  }

  if (!strcpy(rankUnFixed, "Seven"))  {
    rankCount = 6; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 7; 
  }

  if (!strcpy(rankUnFixed, "Eight"))  {
    rankCount = 7; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 8; 
  }

  if (!strcpy(rankUnFixed, "Nine"))  {
    rankCount = 8; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 9; 
  }

  if (!strcpy(rankUnFixed, "Ten"))  {
    rankCount = 9; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 10; 
  }

  if (!strcpy(rankUnFixed, "Jack"))  {
    rankCount = 10; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 10; 
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
    cardFromString->value = 10; 
  }

  if (!strcpy(rankUnFixed, "Ace"))  {
    rankCount = 12; // set the index for the rank; to ensure proper function of suitChoose fxn
    rankFixed = rankChoose(rankCount); // get the suit 
    strcpy(cardFromString->rank,rankFixed); // add the rank to the card
    cardFromString->value = 11; 
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
    rslt = counters_set(valCount, VAL_COUNTER_ID, MIN_CARD_VALUE); // reset card suit index 
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

/**************** main() for testing ****************/

int main(int argc, char *argv[]) {
  
  //  initialize counters objects to be passed to cardNew()
  counters_t *valCount = NULL;
  counters_t *suitCount = NULL;
  counters_t *rankCount = NULL;

  //  initialize the counters
  counters_set(valCount, VAL_COUNTER_ID, 2);  // initialize the valCount to 2 (minimum card value for card = 2)
  counters_set(suitCount, SUIT_COUNTER_ID, 1);
  counters_set(rankCount, RANK_COUNTER_ID, 1);

  // set
  // // add relevant counters keys for value, suit, and rank
  // counters_add(valCount, VAL_COUNTER_ID);
  // counters_add(suitCount, SUIT_COUNTER_ID);
  // counters_add(rankCount, RANK_COUNTER_ID);
  
  //  create a card
  // card_t *newCard = cardNew(valCount, suitCount, rankCount);

  return 0;
}
