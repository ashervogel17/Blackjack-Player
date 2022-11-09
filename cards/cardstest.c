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
#include <unittest.h>


/****************************UNIT TESTING********************************/

int test_cardNew_and_cardDelete() {
    START_TEST_CASE("cardNew and cardDelete");

    card_t* card1 = cardNew(NULL, "C");
    EXPECT(card1 == NULL);
    card1 = cardNew("A", NULL);
    EXPECT(card1 == NULL);
    card1 = cardNew("P", "S");
    EXPECT(card1 == NULL);
    card1 = cardNew("K", "T");
    EXPECT(card1 == NULL);
    
    card1 = cardNew("Eight", "Diamonds");
    card_t* card2 = cardNew("Ace", "Clubs");
    card_t* card3 = cardNew("Queen", "Spades");

    EXPECT(strcmp(cardGetRank(card1), "Eight") == 0);
    EXPECT(strcmp(cardGetSuit(card1), "Diamonds") == 0);
    EXPECT(cardGetValue(card1) == 8);
    EXPECT(strcmp(cardGetRank(card2), "Ace") == 0);
    EXPECT(strcmp(cardGetSuit(card2), "Clubs") == 0);
    EXPECT(cardGetValue(card2) == 11);
    EXPECT(strcmp(cardGetRank(card3), "Queen") == 0);
    EXPECT(strcmp(cardGetSuit(card3), "Spades") == 0);
    EXPECT(cardGetValue(card3) == 10);

    cardDelete(card1);
    cardDelete(card2);
    cardDelete(card3);
    
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_cardParse_and_cardGetName(){
    START_TEST_CASE("cardParse");

    card_t* card1 = cardParse(NULL);
    EXPECT(card1 == NULL);
    card1 = cardParse("Water Buffalo");
    EXPECT(card1 == NULL);
    card1 = cardParse("Thirteen of Spades");
    EXPECT(card1 == NULL);
    card1 = cardParse("Four of Buildings");
    EXPECT(card1 == NULL);

    card1 = cardParse("Seven of Spades");
    card_t* card2 = cardParse("Jack of Clubs");
    card_t* card3 = cardParse("Ace of Diamonds");

    EXPECT(strcmp(cardGetRank(card1), "Seven") == 0);
    EXPECT(strcmp(cardGetSuit(card1), "Spades") == 0);
    EXPECT(cardGetValue(card1) == 7);
    EXPECT(strcmp(cardGetRank(card2), "Jack") == 0);
    EXPECT(strcmp(cardGetSuit(card2), "Clubs") == 0);
    EXPECT(cardGetValue(card2) == 10);
    EXPECT(strcmp(cardGetRank(card3), "Ace") == 0);
    EXPECT(strcmp(cardGetSuit(card3), "Diamonds") == 0);
    EXPECT(cardGetValue(card3) == 11);

    char* card1Name = cardGetName(card1);
    char* card2Name = cardGetName(card2);
    char* card3Name = cardGetName(card3);

    EXPECT(strcmp(card1Name, "Seven of Spades") == 0);
    EXPECT(strcmp(card2Name, "Jack of Clubs") == 0);  
    EXPECT(strcmp(card3Name, "Ace of Diamonds") == 0);

    cardDelete(card1);
    cardDelete(card2);
    cardDelete(card3);
    free(card1Name);
    free(card2Name);
    free(card3Name);

    END_TEST_CASE;
    return TEST_RESULT;
}

int test_handFunctions() {
    START_TEST_CASE("handAddCard and handCalculateValue");

    hand_t* hand = handNew();
    card_t* card1 = cardParse("Ace of Diamonds");
    card_t* card2 = cardParse("Seven of Spades");
    card_t* card3 = cardParse("Jack of Clubs");
    card_t* card4 = cardParse("Ace of Clubs");

    EXPECT(handAddCard(hand, NULL) == false);
    EXPECT(handGetValueOfHand(hand) == 0);

    EXPECT(handAddCard(hand, card1) == true);
    EXPECT(handGetValueOfHand(hand) == 11);
    char* hand1Str = handSortedString(hand);
    EXPECT(strcmp(hand1Str, "Ace") == 0);

    EXPECT(handAddCard(hand, card2) == true);
    EXPECT(handGetValueOfHand(hand) == 18);
    char* hand2Str = handSortedString(hand);
    EXPECT(strcmp(hand2Str, "Seven Ace") == 0);

    EXPECT(handAddCard(hand, card3) == true);
    EXPECT(handGetValueOfHand(hand) == 18);
    char* hand3Str = handSortedString(hand);
    EXPECT(strcmp(hand3Str, "Seven Jack Ace") == 0);

    EXPECT(handAddCard(hand, card4) == true);
    EXPECT(handGetValueOfHand(hand) == 19);
    char* hand4Str = handSortedString(hand);
    EXPECT(strcmp(hand4Str, "Seven Jack Ace Ace") == 0);

    printf("Built hand: \n");
    handPrint(hand);

    handDelete(hand);
    free(hand1Str);
    free(hand2Str);
    free(hand3Str);
    free(hand4Str);

    END_TEST_CASE;
    return TEST_RESULT;
}

int main(const int argc, char* arv[]) {
    int failed = 0;

    failed += test_cardNew_and_cardDelete();
    failed += test_cardParse_and_cardGetName();

    failed += test_handFunctions();
    
    if (failed) {
        printf("FAIL %d test cases\n", failed);
        return failed;
    }
    else {
        printf("PASS all test cases\n");
        return 0;
    }

    return 0;
}