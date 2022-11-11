## CS50 Blackjack Project
## Asher Vogel, Rory Doyle, Eli Rosenberg, Nate Roe

## Requirements Specification 
The goal of this project is to create a reinforcement learning algorithm to learn and play blackjack. This means that this project requires the following taken from the Dartmouth CS50 course webpage. 

"We will use the idea of reinforcement learning to create a program that learns to play the popular card game 21 (also known as blackjack) in an optimal manner. Your program will play hundreds, maybe thousands, of hands of 21 and learn which actions work well (e.g., the program wins), and which do not (e.g., the program looses). On the last day of class we will have a tournament where each team’s program will play the game together and we will ultimately crown a CS50 champion."

Perhaps the most crucial requirement of this project is that communication over the server requires standardized protocols: 

"JOIN <player name>: player asks to join game, player name should not have spaces (use underscore for spaces e.g., team_one_is_here)
BEGIN: to keep dealer and player in sync, if a player gets a BEGIN message, they should reset for a new game (e.g., discard any cards)
CARD: dealer sends player a card, rank will be strings “Two” through “Ten”, “Jack”, “Queen”, “King”, or “Ace”, suit will be “Diamonds”, “Hearts”, “Clubs” or “Spades” (e.g., “CARD Nine of Hearts”)
DEALER: dealer tells player the Rank of Suit of dealer’s face-up card (e.g., “DEALER Ace of Clubs”)
DECISION: dealer asks the player to make a decision (either HIT or STAND)
HIT or STAND: player tells the dealer their decision based on player’s cards and dealer’s face-up card (repeat until STAND or BUST)
RESULT: dealer tells the player if they WIN, LOOSE, BUST, or PUSH (followed by BEGIN if playing multiple rounds)
QUIT: dealer tells player to quit"

This project must also run without bugs and memory leaks. 
