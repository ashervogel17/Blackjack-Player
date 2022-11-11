/* 
 * cards.c - CS50 'cards' module for blackjack game
 *
 * see cards.h for more information.
 *
 * Nate Roe, Asher Vogel, November 2022
 * CS 50, Fall 2022
 */

/*  include statements  */
#include "cards.h"
#include <time.h>


/**************** local types ****************/

/**************** global types ****************/
typedef struct card {
  int value;  //  value of the card 2-11 (ace is stored as 11)
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

/* card methods */

/** 
 * Caller provides:
 *    valid rank (Ace, Two, Three, ..., Ten, Jack, Queen, King)
 * We return:
 *    0 if the rank provided is invalid
 *    the value of that rank in blackjack
 * */
static int rankToValue(char* rank) {
  if (rank == NULL) {
    return 0;
  }
  else if (strcmp(rank, "Ace") == 0) {
    return 11;
  }
  else if (strcmp(rank, "Two") == 0) {
    return 2;
  }
  else if (strcmp(rank, "Three") == 0) {
    return 3;
  }
  else if (strcmp(rank, "Four") == 0) {
    return 4;
  }
  else if (strcmp(rank, "Five") == 0) {
    return 5;
  }
  else if (strcmp(rank, "Six") == 0) {
    return 6;
  }
  else if (strcmp(rank, "Seven") == 0) {
    return 7;
  }
  else if (strcmp(rank, "Eight") == 0) {
    return 8;
  }
  else if (strcmp(rank, "Nine") == 0) {
    return 9;
  }
  else if (strcmp(rank, "Ten") == 0 || strcmp(rank, "Jack") == 0 || strcmp(rank, "Queen") == 0 || strcmp(rank, "King") == 0) {
    return 10;
  }
  else {
    return 0;
  }
}

/**
 * Caller provides:
 *    valid rank
 * We return:
 *    true is rank is one of (Ace, Two, Three, ..., Ten, Jack, Queen, King)
 *    false otherwise
 * */
bool validateRank(char* rank) {
  if (strcmp(rank, "Ace") == 0) {
    return true;
  }
  else if (strcmp(rank, "Two") == 0) {
    return true;
  }
  else if (strcmp(rank, "Three") == 0) {
    return true;
  }
  else if (strcmp(rank, "Four") == 0) {
    return true;
  }
  else if (strcmp(rank, "Five") == 0) {
    return true;
  }
  else if (strcmp(rank, "Six") == 0) {
    return true;
  }
  else if (strcmp(rank, "Seven") == 0) {
    return true;
  }
  else if (strcmp(rank, "Eight") == 0) {
    return true;
  }
  else if (strcmp(rank, "Nine") == 0) {
    return true;
  }
  else if (strcmp(rank, "Ten") == 0) {
    return true;
  }
  else if (strcmp(rank, "Jack") == 0) {
    return true;
  }
  else if (strcmp(rank, "Queen") == 0) {
    return true;
  }
  else if (strcmp(rank, "King") == 0) {
    return true;
  }
  else {
    return false;
  }
}

/**
 * Caller provides:
 *    valid suit
 * We return:
 *    true is suit is one of (Clubs, Spades, Hearts, Diamonds)
 *    false otherwise
 * */
bool validateSuit(char* suit) {
  if (strcmp(suit, "Clubs") == 0) {
    return true;
  }
  else if (strcmp(suit, "Spades") == 0) {
    return true;
  }
  else if (strcmp(suit, "Hearts") == 0) {
    return true;
  }
  else if (strcmp(suit, "Diamonds") == 0) {
    return true;
  }
  else {
    return false;
  }
}

card_t* cardNew(char* rank, char* suit) {
  // safety checks
  if (rank == NULL) {
    fprintf(stderr, "Cannot create card with NULL rank\n");
    return NULL;
  }
  if (suit == NULL) {
    fprintf(stderr, "Cannot create card with NULL suit\n");
    return NULL;
  }
  if (!validateSuit(suit)) {
    fprintf(stderr, "Cannot create card with suit %s\n", suit);
    return NULL;
  }
  if (!validateRank(rank)) {
    fprintf(stderr, "Cannot create card with rank %s\n", rank);
    return NULL;
  }
  // construct card
  card_t* card = malloc(sizeof(card_t));
  card->value = rankToValue(rank);
  card->rank = malloc(sizeof(char)*(strlen(rank)+1));
  strcpy(card->rank, rank);
  card->suit = malloc(sizeof(char)*(strlen(suit)+1));
  strcpy(card->suit, suit);
  return card;
}

card_t* cardParse(char *cardString) {
  // safety checks
  if (cardString == NULL) {
    fprintf(stderr, "Cannot create card with NULL card string\n");
    return NULL;
  }
  char* rank = malloc(sizeof(char)*50);
  char* ofString = malloc(sizeof(char)*50);
  char* suit = malloc(sizeof(char)*50);
  if (sscanf(cardString, "%s %s %s", rank, ofString, suit) != 3) {
    fprintf(stderr, "Cannot create card from string %s\n", cardString);
    free(rank);
    free(ofString);
    free(suit);
    return NULL;
  }
  // construct card with cardNew
  card_t* card = cardNew(rank, suit);
  free(ofString);
  free(rank);
  free(suit);
  return card;
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

void cardDelete (card_t* card) {
  if (card != NULL) {
    free(card->rank);
    free(card->suit);
    free(card);
  }
}

char* cardGetName(card_t* card) {
  if (card == NULL) {
    return NULL;
  }
  char* name = malloc(sizeof(char)*20);
  strcpy(name, cardGetRank(card));
  strcat(name, " of ");
  strcat(name, cardGetSuit(card));
  return name;
}

void cardPrint(card_t* card) {
  if (card != NULL) {
    char* name = cardGetName(card);
    printf("%s", name);
    free(name);
  } 
}

/* hand methods */

hand_t* handNew() {
    // allocate memory with safety check
    hand_t* hand = malloc(sizeof(hand_t)); 
    if (hand == NULL) {
        fprintf(stderr, "Error creating hand\n"); 
        return NULL;
    }

    // initialize cards to empty array
    card_t** cards = calloc(MAX_CARDS_IN_A_HAND + 1, sizeof(card_t*)); 
    hand -> cards = cards; 
    // intialize other variables to 0
    hand -> numberOfCards = 0; 
    hand-> valueOfHand = 0; 

    return hand; 
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

bool handAddCard (hand_t* hand, card_t* card) {
    if (hand == NULL || card == NULL) {
        return false; 
    }
    hand->cards[(hand->numberOfCards)] = card;
    hand -> numberOfCards ++;
    handCalculateValue(hand);
    return true; 
}

void handCalculateValue(hand_t* hand) {
  int handValue = 0;
  int numAces = 0;

  // iterate over cards
  for (int i = 0; i < hand -> numberOfCards; i++) {
    if (hand -> cards[i] != NULL) {
      card_t* card = hand -> cards[i];
      // increment ace count
      if (card -> value == 11) {
          numAces++;
      } 
      // increment value
      handValue += card->value;
    }
  }
  // make aces into 1's if hand is busted
  while (handValue > 21 && numAces > 0) {
      handValue -= 10;
      numAces--;
  }
  hand->valueOfHand = handValue;
}

void handDelete (hand_t* hand) {
  // printf("Deleting hand\n");
  int loc = 0;
  while (hand->cards[loc] != NULL) {
      card_t* card = hand -> cards[loc];
      // printf("Deleting card: ");
      // cardPrint(card);
      // printf("\n");
      cardDelete(card);
      loc++;
      if (loc == hand->numberOfCards) {
        break;
      }
  }
  free(hand->cards);
  free(hand); 
}

void handPrint(hand_t* hand) {
  if (hand != NULL) {
    int loc = 0;
    while (hand->cards[loc] != NULL) {
      card_t* card = hand -> cards[loc];
      cardPrint(card);
      printf("\n");
      loc++;
      if (loc == hand->numberOfCards) {
        break;
      }
    }
  }
}


/* deck methods */

deck_t* deckNew() {
  deck_t* deck = malloc(sizeof(deck_t)); 

  deck -> numberOfCards = 52; 
  deck -> shuffled = false; 
  deck -> cards = malloc(52*sizeof(card_t*));

  char* ranks[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
  char* suits[] = {"Diamonds", "Clubs", "Spades", "Hearts"}; 

  for (int i=0; i < 13; i++){
    for (int j=0; j < 4; j++) {
      int index = j*13 + i;
      card_t* card = cardNew(ranks[i], suits[j]);
      deck->cards[index] = card;
    }
  }

  return deck;
}

int deckGetNumberOfCards (deck_t* deck) { 
    return deck -> numberOfCards; 
}

bool deckIsShuffled (deck_t* deck) {
    return deck -> shuffled; 
}

card_t** deckGetCards (deck_t* deck) {
    return deck -> cards; 
}

/**
 * Caller provides:
 *      a deck struct
 * We do:
 *      shuffle the cards in the deck (put the same cards in a different order)
 * 
 * Note: Implementation of Fisher-Yates algorithm for generation of random permutation 
 * in linear time. Adapted from pseudocode found online at geeksforgeeks.com
 * */
void deckShuffle(deck_t* deck) {

  if (deck != NULL) { //safety check

    srand (time(NULL)); //generate random number seed 
  
    card_t* cardOne; 
    card_t* cardTwo; 

    card_t** cards = deck -> cards; //get array of cards in deck
    int sizeOfDeck = deck -> numberOfCards; 

    //iterate through deck and implement Fisher-Yates swap
    for (int i = sizeOfDeck - 1; i > 0; i--) { 

      int j = rand() % (i + 1); 
          
      cardOne = cards[i];  
      cardTwo = cards[j]; 
      card_t* tempCard; 

      tempCard = cardOne; 
      cardOne = cardTwo; 
      cardTwo = tempCard; 

      cards[i] = cardOne; 
      cards[j] = cardTwo; 
    }

    deck -> shuffled = true; //set shuffled to true 

  } else { //safety check 
    fprintf(stderr, "Cannot shuffle a NULL deck.\n");
  }

}


/**
 * Caller provides:
 *      a deck struct
 * We do:
 *      check that the deck is shuffled - if not, shuffle it
 *      remove one card from the deck and return it
 *      decrement number of cards
 * */
card_t* deckDealRandomCard(deck_t* deck) {

  if (deck == NULL) {
    fprintf(stderr, "Cannot deal a card from a NULL deck.\n"); 
    return NULL; 
  }

  if (!(deck -> shuffled)) { //ensure deck is shuffled
    deckShuffle(deck); 
  }

  int sizeOfDeck = deck -> numberOfCards;
  card_t** cards = deck -> cards; //get array of cards from deck
  card_t* card; 

  if (sizeOfDeck > 0) { //safety check
    card = cards[sizeOfDeck -1]; //get card at 'last' index of array 
  } else { 
    fprintf(stderr, "Cannot deal cards from an empty deck.\n"); 
    return NULL;
  }

  deck -> numberOfCards--; //decrement pointer to 'last' card

  return card; 

}

/**
 * Free all memory associated with the given deck
 * */
/*  deckDelete()  */
/* see cards.h for explanation*/
void deckDelete (deck_t* deck) {
  // printf("Deleting hand\n");
  int loc = 0;
  while (deck->cards[loc] != NULL) {
      card_t* card = deck -> cards[loc];
      // printf("Deleting card: ");
      // cardPrint(card);
      // printf("\n");
      cardDelete(card);
      loc++;
      if (loc == deck->numberOfCards) {
        break;
      }
  }
  free(deck->cards);
  free(deck);
}