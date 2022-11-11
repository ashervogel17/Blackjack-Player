/*
Testing c file to our client-side network wrapper functions

Elias Rosenberg, 22F, CS50
*/


#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "./clientNetwork.h"
#include <unistd.h>
#define EXAMPLE_PORT 8094
int* socketPointer; 



int main(const int argc, char* argv[])
{
	socketPointer = establish_client_connection("129.170.64.104", EXAMPLE_PORT); //save the pointer to the socket our client is currently on that is sucessfully connected to the server
    int new_socket = *socketPointer; //for ease of printing and method calling, we dereference this pointer to an integer that we will use for all our wrappper methods. 

    printf("client connected to server with socket %d over PORT: %d\n", new_socket, EXAMPLE_PORT); 

	int SIZE = 100; //All this code is an example of continuously sending and receiving messages to and from the server we've connected to. 
	char line[SIZE]; 
	printf("Please enter your message to server...\n"); 
    fgets(line, SIZE, stdin);

    while (strcmp(line, "QUIT\n") != 0) {
        char buffer[1024] = { 0 }; //empty string to store our messages received from the server. 
        printf("message: %s\n", line); 
		send_message(line, new_socket); //callling the send_message wrapper function to send our line from stdin to the server
		receive_message(new_socket, 1024, buffer); //receiving whatever message is sent back. In our actually code what we send back is conditional based on the Client's message. 

        if (line == NULL){
            printf("Invalid message \n"); //if our query is invalid, go to next iteration to get new query
            return 1; 
        }

		printf("Please enter your message to server...\n");
        fgets(line, SIZE, stdin);

    }
    printf("Ending client connection to server...\n");
    terminate_client_connection(new_socket); //calling the wrapper method to end our connection to the server. '

}