/*
Implementation of header file for clientNetwork.h. We simply provide wrapper functions for the functions given by arap/inet.h and sys/socket.h
The core of the code was gotten from. 

Elias Rosenberg, CS50, 22F
*/


#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "clientNetwork.h"
#include <time.h>
#define PORT_EXAMPLE 8094 //port 8000 + team number --> 8014

int* establish_client_connection(char* IPAddress, int PORT)
{
	int sock, client_fd;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { //create the socket object
		//printf("\n Socket creation error \n");
		exit(EXIT_FAILURE);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, IPAddress, &serv_addr.sin_addr)
		<= 0) {
	//printf("\nInvalid address/ Address not supported \n");
		exit(EXIT_FAILURE);
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr, //connect this socket to the PORT and IPAddress
				sizeof(serv_addr)))
		< 0) {
		//printf("\nConnection Failed \n");
		exit(EXIT_FAILURE);
	}
	int* socketPointer = NULL;
	socketPointer = &sock;  
	return socketPointer;  
}


int send_message(const char* message, int new_socket){
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = 26000000;
	
	if (send(new_socket, message, strlen(message) + 1, 0) != -1){
		// printf("message sent %s\n", message); 
		nanosleep(&tim, NULL);
		return 0; 
	}
	else{
		// printf("message not sent!!\n"); 
	}
	nanosleep(&tim, NULL);
	return 1; 
	//message not sent 
}


int receive_message(int sock, size_t nbytes, char* buffer){
	if (read(sock, buffer, nbytes) != -1){
		//printf("message received: %s\n", buffer); //we read the response on the socket. 
		return 0; 
	} 
	return 1; 
}


void terminate_client_connection(int client_fd){
	// closing the connected socket
	close(client_fd); 
}