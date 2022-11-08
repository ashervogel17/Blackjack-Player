// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "clientNetwork.h"
//#define PORT 8094 //port 8000 + team number --> 8014

int establish_client_connection(char* IPAddress, int PORT)
{
	int sock = 0, client_fd;
	struct sockaddr_in serv_addr;
	//char* hello = "Hello from client";
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { //create the socket object
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, IPAddress, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr, //connect to the address saved by serv_adder
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	return client_fd; 
}


int send_message(int sock, const char* message, size_t line_size){
	if (send(sock, message, strlen(message), 0) != -1){
		printf("message sent %s\n", message); 	

	}
	return 1; 
	//message not sent 
}


int receive_message(int sock, size_t nbytes){
	char buffer[1024] = { 0 };
	if (read(sock, buffer, 1024) != -1){
		printf("message received: %s\n", buffer); //we read the response on the socket. 
	} 
	return 1; 
}


void terminate_client_connection(int client_fd){
	// closing the connected socket
	close(client_fd);
}