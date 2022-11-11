# Cards Module
The cards module will implement the functionality of 3 card data structures card, hand, and deck. The functionality contained in the cards functions will facilitate the gameplay flow included in the dealer and player modules.

### cards
 * In the blackjack game the card and the functionality associated with the card is of critical importance.
 * The cards module will implement a series of data structures through several gameplay-related functions.

#### cards assumptions 
* the value of an ace card will be defaulted to an 11 unless in calculating the value of the hand, the player would bust with an ace at a value of 11. In that case the ace will be revalued to a 1 and the value of the hand will be recalculated.

#### testing 
* the cards module is unit tested via a card unit testing module called cardtest which will implement unit testing on each of the functions within cards as well as check for memory leaks due to improper functionality of the card, hand, and deckNew() and delete functions.