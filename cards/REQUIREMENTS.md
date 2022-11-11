# CS50 REQUIREMENTS.md Cards
## Requirements Specification

> In a requirements spec, **shall do** means **must do**.

The cards module will facilitate blackjack gameplay by providing data structures for a card, hand, and deck of cards with corresponding functions to implement the desired blackjack card behavior and gameplay
The cards module **shall**:

1. be called from the dealer module and from the player module from within routines and functions 

## calling cards from the dealer module
* the cards function deckNew() called from the main() routine
* the cards function cardParse(char *cardString), which will *  return cards objects for use in gameplay 
* the cards function deckShuffle(deck_t *deck) which will shuffle the deck 
* the cards function deckDealRandomCard(deck) which will return a card_t object after popping a card off the deck 
* handAddCard(dealerHand, dealerCard) will be called to add cards to the hand of the dealer 
* handGetValueOfHand(playerHand) will return the value of the player hand 
* handDelete(playerHand) and handDelete(dealerHand) will be called to free the memory associated with the current hands being played 
* deckDelete(deck) will be called to free the current deck of cards

## calling cards from the player module 
* in the player module function play(), the function handSortedString(hand) will be used to return the ranked value of the playerHand and the dealerHand used in the gameplay
* in the player module in the play() function the getter functions from cards handGetValueOfHand(hand) will be used to decide on the outcome of gameplay between the dealer and the player in training and gameplay modes
* in the player function play() the cards function handDelete() will be called to free the memory associated with the hand 
**Assumption**:
The assumptions in using any of the cards.c module functions is that the Ace default value will be an 11, unless in the event of employing an ace at a value of 11 will result in a bust. In that case the Ace is treated as a 1 and the handGetValueOfHand function will return a value for the hand to reflect such a case. 

**Limitation**:
The cards module does not have any limitations in its functionality related to its use in the player and dealer modules