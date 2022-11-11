## CS50 Blakcjack Project
## Asher Vogel, Rory Doyle, Eli Rosenberg, Nate Roe

## Requirements Specification 
This is the requirements specification for dealer for the blackjack project for CS50.
The requirements are taken from the Dartmouth CS50 course webpage: 

"The dealer shall:

run from the command line
set up a server socket listening for clients (players) to connect (see this server example)
once a client connects (you need only handle one client, mine will handle up to six players), pass messages back and forth over socket as shown in diagram below, and
create a deck of 52 cards for each game
shuffle the deck
deal cards to the player by sending messages with the card suit and rank as a string (e.g., “Seven of Hearts”)
receive HIT/STAND decisions from the client
calculate the game’s result (WIN, LOOSE, BUST, or PUSH) and send a message to the client
reset and play again (you decide on how many games to play)
send a QUIT message to the client when done
Your dealer program need only accommodate a single player."

Another important requirement for the dealer is that it uses stndardized messaging protocols as specified on the course webpage. 
"JOIN <player name>: player asks to join game, player name should not have spaces (use underscore for spaces e.g., team_one_is_here)
BEGIN: to keep dealer and player in sync, if a player gets a BEGIN message, they should reset for a new game (e.g., discard any cards)
CARD: dealer sends player a card, rank will be strings “Two” through “Ten”, “Jack”, “Queen”, “King”, or “Ace”, suit will be “Diamonds”, “Hearts”, “Clubs” or “Spades” (e.g., “CARD Nine of Hearts”)
DEALER: dealer tells player the Rank of Suit of dealer’s face-up card (e.g., “DEALER Ace of Clubs”)
DECISION: dealer asks the player to make a decision (either HIT or STAND)
HITT: dealer tells player to quit"

These are the reuirements which the dealer must fulfil without bugs or memory leaks. 
