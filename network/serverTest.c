#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "./serverNetwork.h"
#include <unistd.h>
#include "../cards/cards.h"
#define EXAMPLE_PORT 8094
char* hello = "Message receieved!\n"; 
char buffer[1024] = { 0 };

const int NUM_GAMES = 1000;


typedef struct server_data {   // Structure declaration
  int* socket;           // pointer to listen to the proper socket
  int* server_fd;       // used to close the server
}server_data_t; 

void parseServerMessage(char* buffer, int new_socket, deck_t* deck, hand_t* dealerHand, hand_t* playerHand, bool* gameOnGoing); 

int main(const int argc, char* argv[])
{
	server_data_t* data = establish_server_connection("129.170.64.104", EXAMPLE_PORT); //use plank's IP address

	int new_socket = *data->socket;  

	printf("We are now listnening for messages on new_socket: %d\n", new_socket); 
	printf("\n"); 

	int SIZE = 100; //All this code is an example of continuously sending and receiving messages to and from the server we've connected to. 
	char buffer[SIZE]; 

	// set up deck, player hand, and dealer hand
    int game_count = 1; 
    printf("\n\n NEW GAME (#%d)\n\n", game_count);
	deck_t* deck = deckNew(); 
	deckShuffle(deck); 
	hand_t* dealerHand = handNew();
	hand_t* playerHand = handNew();
	

	bool* gameOnGoing = malloc(sizeof(bool*)); 
	*gameOnGoing = true; 

	



    while (game_count < NUM_GAMES) {
		// continnue game
		if (*gameOnGoing) {
			if (recv(new_socket, buffer, SIZE, 0) != 0){
				printf("Client: "); 
				printf("%s\n", buffer);
				parseServerMessage(buffer, new_socket, deck, dealerHand, playerHand, gameOnGoing); //we set game
			}
		}
		// new game
		else {
			game_count++;
			printf("\n\n NEW GAME (#%d)\n\n", game_count);
			deckDelete(deck);
			handDelete(playerHand);
			handDelete(dealerHand);
			deck = deckNew();
            for (int i=0; i<3; i++) {
                deckShuffle(deck);
            }
			dealerHand = handNew();
			playerHand = handNew();
			parseServerMessage(buffer, new_socket, deck, dealerHand, playerHand, gameOnGoing);
		}

	}
	// closing the connected socket
	send_message("QUIT", new_socket); 
	terminate_server_connection(data); 
	return 0;
}


void parseServerMessage(char* buffer, int new_socket, deck_t* deck, hand_t* dealerHand, hand_t* playerHand, bool* gameOnGoing){
	char* message = malloc(sizeof(char)*(50));
	if ((strcmp(buffer, "JOIN") == 0) || (*gameOnGoing == false)) {
		*gameOnGoing = true;
		send_message("BEGIN", new_socket); 

		// send first [player card
		message = malloc(sizeof(char)*(50));
		card_t* playerCard1 = deckDealRandomCard(deck);
		handAddCard(playerHand, playerCard1);
		strcpy(message, "CARD ");
		strcat(message, cardGetName(playerCard1));
		send_message(message, new_socket);
		free(message);

		// send second player card
		message = malloc(sizeof(char)*(50));
		card_t* playerCard2 = deckDealRandomCard(deck);
		handAddCard(playerHand, playerCard2);
		strcpy(message, "CARD ");
		strcat(message, cardGetName(playerCard2));
		send_message(message, new_socket);
		free(message);
		
		// send first dealer card
		message = malloc(sizeof(char)*(50));
		card_t* dealerCard1 = deckDealRandomCard(deck);

		handAddCard(dealerHand, dealerCard1);
		strcpy(message, "DEALER ");
		strcat(message, cardGetName(dealerCard1));
		send_message(message, new_socket);
		free(message);
		
		// dealer second dealer card but don't send
		card_t* dealerCard2 = deckDealRandomCard(deck);
		handAddCard(dealerHand, dealerCard2);

		printf("\nCards dealt.\nPlayer hand:\n");
		handPrint(playerHand);
		printf("\nDealer hand:\n");
		handPrint(dealerHand);
		printf("\n");

		send_message("DECISION", new_socket);
	}

	else if(strcmp(buffer, "HIT") == 0){
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