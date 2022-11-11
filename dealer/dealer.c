/* 
* dealer.c - dealer program for blackjack project
* Serves as driver forgram for server and also deals with logic to calculate 
* winner and loser of game. Also serves as driver for cards module--creates 
* deck, cards, and hands. 
* 
* Authors- Asher Vogel, Eli Rosenberg, Nate Roe, Rory Doyle
* Dartmouth CS50, Fall 2022
*/

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "./serverNetwork.h"
#include <unistd.h>
#include "../cards/cards.h"

#define EXAMPLE_PORT 8094 //port used for socket set up 
char* hello = "Message receieved!\n"; 
char buffer[1024] = { 0 };

const int NUM_GAMES = 3; //int used to declare number of games to play to train algorithm

/******************************STRUCTS************************************/
typedef struct server_data {   // Structure declaration
  int* socket;           // pointer to listen to the proper socket
  int* server_fd;       // used to close the server
}server_data_t; 


/*****************************FUNCTION PROTOTYPES*************************/
void parseServerMessage(char* buffer, int new_socket, deck_t* deck, hand_t* dealerHand, hand_t* playerHand, bool* gameOnGoing); 



/*************************************************************************/
int main(const int argc, char* argv[])
{

	server_data_t* data = establish_server_connection("129.170.64.104", EXAMPLE_PORT); //use plank's IP address to create server

	int new_socket = *data->socket; //store docket data

	printf("We are now listnening for messages on new_socket: %d\n", new_socket); 
	printf("\n"); 

	int SIZE = 100; //size of buffer character to receive messages 
	char buffer[SIZE]; 

    int game_count = 1; //preset number of games to play
    
    printf("\n\n NEW GAME (#%d)\n\n", game_count);

    //set up deck and hands for game
	deck_t* deck = deckNew(); 
	hand_t* dealerHand = handNew();
	hand_t* playerHand = handNew();

    if (deck == NULL || dealerHand == NULL || playerHand == NULL) {
        fprintf(stderr, "Error alocating memory.\n");
        return 1; 
    }
	
    deckShuffle(deck); //shuffle the deck

    //set a boolean to aid in game flow
	bool* gameOnGoing = malloc(sizeof(bool*)); 
	*gameOnGoing = true; 

    //play specified number of games 
    while (game_count < NUM_GAMES) {
		
        //if first game wait for client to connect
		if (*gameOnGoing) {

            //wait for client to connect and send a message
			if (recv(new_socket, buffer, SIZE, 0) != 0) {
				printf("Client: "); 
				printf("%s\n", buffer);
				parseServerMessage(buffer, new_socket, deck, dealerHand, playerHand, gameOnGoing); //set game 
			}
		}

		//new game
		else {

			game_count++;
			printf("\n\n NEW GAME (#%d)\n\n", game_count);

            //delete old game data and clean up memory
			deckDelete(deck);
			handDelete(playerHand);
			handDelete(dealerHand);

            //create new deck
			deck = deckNew();

            //safety check
            if (deck == NULL) {
                fprintf(stderr, "Error allocating memory.\n");
                exit(1); 
            }

            for (int i = 0; i < 3; i++) {
                deckShuffle(deck); //shuffle deck
            }
            
            //create the new hands
			dealerHand = handNew();
			playerHand = handNew();

            //safety checks
            if (dealerHand == NULL || playerHand == NULL) {
                fprintf(stderr, "Error allocating memory.\n"); 
                exit(1); 
            }

			parseServerMessage(buffer, new_socket, deck, dealerHand, playerHand, gameOnGoing); //call parser method
		}

	}
	// closing the connected socket
	send_message("QUIT", new_socket); 
	terminate_server_connection(data); 
	return 0;
}

/*
* parseServerMethod - recieve a message, send messages, and play game accordingly 
*
* Expected: 
    - string of message received 
    - socket 
    - pointers ot a deck and two hands
    - boolean to aid in game flow 
* Returns: void 
*/
void parseServerMessage(char* buffer, int new_socket, deck_t* deck, hand_t* dealerHand, hand_t* playerHand, bool* gameOnGoing){
	
    char* message = malloc(sizeof(char)*(50)); //allocate space for a message to send

    //check for 'JOIN' method 
	if ((strcmp(buffer, "JOIN") == 0) || (*gameOnGoing == false)) {
		
        *gameOnGoing = true;
		send_message("BEGIN", new_socket); 

		// send first player card and add it to their hand
		message = malloc(sizeof(char)*(50));
		card_t* playerCard1 = deckDealRandomCard(deck);
		handAddCard(playerHand, playerCard1);
		strcpy(message, "CARD ");
		strcat(message, cardGetName(playerCard1));
		send_message(message, new_socket);
		free(message);

		// send second player card and add it to their hand
		message = malloc(sizeof(char)*(50));
		card_t* playerCard2 = deckDealRandomCard(deck);
		handAddCard(playerHand, playerCard2);
		strcpy(message, "CARD ");
		strcat(message, cardGetName(playerCard2));
		send_message(message, new_socket);
		free(message);
		
		// send first dealer card and add it to their hand
		message = malloc(sizeof(char)*(50));
		card_t* dealerCard1 = deckDealRandomCard(deck);
		handAddCard(dealerHand, dealerCard1);
		strcpy(message, "DEALER ");
		strcat(message, cardGetName(dealerCard1));
		send_message(message, new_socket);
		free(message);
		
		// add dealer second card to their hand but do not send
		card_t* dealerCard2 = deckDealRandomCard(deck);
		handAddCard(dealerHand, dealerCard2);

		//print the hands
		printf("\nCards dealt.\nPlayer hand:\n");
		handPrint(playerHand);
		printf("\nDealer hand:\n");
		handPrint(dealerHand);
		printf("\n");

		send_message("DECISION", new_socket); //send message for decision 
	}

	//if we receive 'HIT'
	else if(strcmp(buffer, "HIT") == 0){

		//send a message of a new card and add it to the hand of player
		card_t* nextPlayerCard = deckDealRandomCard(deck);
		handAddCard(playerHand, nextPlayerCard);
		message = malloc(sizeof(char)*(50));
		strcpy(message, "CARD ");
		strcat(message, cardGetName(nextPlayerCard));
		send_message(message, new_socket);
		free(message);
		
		// check if player busted
		if (handGetValueOfHand(playerHand) > 21) { // bust
			printf("\nPlayer busted\n");
			send_message("RESULT LOSE", new_socket);
			*gameOnGoing = false;
		}

		else { // send card message
			send_message("DECISION", new_socket);
		}
	}

	//if we receive 'STAND'
	else if(strcmp(buffer, "STAND") == 0){
		
		printf("Player stood.\n");

		//code the logic of playing for dealer
		while (handGetValueOfHand(dealerHand) < 17) {
			card_t* nextDealerCard = deckDealRandomCard(deck);
			handAddCard(dealerHand, nextDealerCard);
		}

		printf("Player hand: %d\n", handGetValueOfHand(playerHand));
		handPrint(playerHand);
		printf("Dealer hand: %d\n", handGetValueOfHand(dealerHand));
		handPrint(dealerHand);

		// send result
		if (handGetValueOfHand(dealerHand) > 21 || handGetValueOfHand(dealerHand) < handGetValueOfHand(playerHand)) {
			send_message("RESULT WIN", new_socket);
		}
		else if (handGetValueOfHand(dealerHand) == handGetValueOfHand(playerHand)) {
			send_message("RESULT PUSH", new_socket);
		}
		else {
			send_message("RESULT LOSE", new_socket);
		}
		*gameOnGoing = false;
	}

	else{
		printf("other message sent\n"); 
	}
}