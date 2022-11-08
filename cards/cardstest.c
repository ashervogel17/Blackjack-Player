/* 
* cardstest.c - test program for cards module 
* includes unit tests of all methods and also 
* functionality test for all methods working together 
* as expected for dealer and player modules for blackjack project
* 
* Rory Doyle, Nate Roe, Eli Rosenberg, Asher Vogel 
* CS50, Fall 2022 
*/

#include "cards.h" 


/****************************UNIT TESTING********************************/


void printCard(card_t* card) {
    fprintf(stdout, "Rank: %s, Suit: %s, Value: %d\n", cardGetRank(card), cardGetSuit(card), cardGetValue(card)); 
}


//deck 
void testDeck(int counter) {
    
    deck_t* deck = deckNew(); 
    
    if (deck == NULL) {
        fprintf(stdout, "Error with deckNew.\n");
        counter += 1;  
    }

    //test deck getter methods
    if (deckGetNumberOfCards(deck) != 52) {
        fprintf(stdout, "Error with numberOfCards.\n"); 
        counter += 1;  
    }

    if (deckIsShuffled(deck)) {
        fprintf(stdout, "Error with shuffled\n"); 
        counter += 1;  
    }

    card_t** cards = deckGetCards(deck); 
    int cardCount = 0; 
    for (int i = 0; i < sizeof(cards); i++) {
        cardCount++; 
    }

    if (cardCount != 52) {
        fprintf(stdout, "Error with cards\n"); 
        counter += 1;  
    }

    deckShuffle(deck); 
    if (!(deckIsShuffled(deck))) {
        fprintf(stdout, "Error with deckShuffle\n"); 
        counter += 1;  
    }

    card_t* card = deckDealRandomCard(deck); 
    if (card == NULL || deckGetNumberOfCards(deck) != 52) {
        fprintf(stdout, "Error with deckDealRandomCard\n"); 
        counter += 1; 
    }

    deckDelete(deck); 
}

//test hand
void testHand(int counter) {

    hand_t* hand = handNew(); 
    if (hand == NULL) {
        fprintf(stdout, "Error with handNew\n"); 
        counter += 1; 
    }

    deck_t* deck = deckNew(); 
    deckShuffle(deck); 
    card_t* card = deckDealRandomCard(deck);

    if (!(handAddCard(hand, card, false))) {
        fprintf(stdout, "Error with handAddCard\n"); 
        counter += 1;  
    } 

    if (handGetNumberOfCards(hand) != 1) {
        fprintf(stdout, "Error with handGetNumberOfCards\n"); 
        counter += 1; 
    }

    if (handGetValueOfHand(hand) != cardGetValue(card)) {
        fprintf(stdout, "Error with handGetValueOfHand\n"); 
        counter += 1; 
    }

    card_t** cards = handGetCards(hand); 
    if (cards == NULL) {
        fprintf(stdout, "Error with handGetCards\n"); 
        counter += 1; 
    }

    if (cards[0] != card) {
        fprintf(stdout, "Error with handGetCards\n"); 
        counter += 1; 
    }

    fprintf(stdout, "Test for handSortedString: %s\n", handSortedString(hand));

    handDelete(hand); 
}


//card test 
void testCard(int counter) {

    card_t* card = cardParse("Seven of Hearts"); 

    if (cardGetValue(card) != 7) {
        fprintf(stdout, "Error with cardParse\n"); 
        counter += 1; 
    }

    if (strcmp(cardGetSuit(card), "H") != 0) {
        fprintf(stdout, "Error with cardParse\n"); 
        counter += 1; 
    }

    if (strcmp(cardGetRank(card), "7") != 0) {
        fprintf(stdout, "Error with cardParse\n"); 
        counter += 1; 
    }

    cardDelete(card); 
}

int main(const int argc, char* argv[]) {

    int numberOfErrors = 0; 

    testDeck(numberOfErrors); 
    testHand(numberOfErrors); 
    testCard(numberOfErrors); 

    fprintf(stdout, "Number of errors: %d\n", numberOfErrors); 

    //test for expected functionality 
    deck_t* deck = deckNew(); 
    deckShuffle(deck); 
    card_t** cardsInDeck = deckGetCards(deck); 
    
    for (int i = 0; i < 52; i++) {
        printCard(cardsInDeck[i]); 
    }

    hand_t* hand = handNew(); 
    handAddCard(hand, deckDealRandomCard(deck), false);
    handAddCard(hand, deckDealRandomCard(deck), false);
    card_t** cardsInHand = handGetCards(hand); 

    for (int i = 0; i < 2; i++) {
        printCard(cardsInHand[i]); 
    }  

    handDelete(hand); 
    deckDelete(deck); 
    
    return numberOfErrors; 
}
