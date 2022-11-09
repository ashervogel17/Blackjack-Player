// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "serverNetwork.h"
#include <stddef.h>
#define _BSD_SOURCE
#include <unistd.h>
#include <time.h>
#define EXAMPLE_PORT 8093

typedef struct server_data {   // Structure declaration
  int* socket;           // pointer to listen to the proper socket
  int* server_fd;       // used to close the server
}server_data_t; 


server_data_t* serverData_new(int* socket, int* server_fd){
  server_data_t* data = malloc(sizeof(server_data_t));

  if (data == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    data->socket = socket; //this is the actual correct way to store nodes. Honestly unecessary to malloc keys and items tbh. 
    data->server_fd= server_fd;
    return data;
  }
}

server_data_t* establish_server_connection(char* IPAdress, int PORT){

	printf("Establishing server connection...\n"); 
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_BROADCAST, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}


	printf("Server listening on port: %d\n", PORT); 
	printf("Waiting for client..\n"); 


	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
		perror("accept");
		exit(EXIT_FAILURE);
	}

	int* socketPointer = &new_socket; 
	int* server_fd_Pointer = &server_fd; 

	server_data_t* data = serverData_new(socketPointer, server_fd_Pointer); 
	return data; 
}


void terminate_server_connection(server_data_t* data){
	close(*data->socket); 
	printf("Server closed\n"); 
	shutdown(*data->server_fd, SHUT_RDWR); 
}

int send_message(const char* message, int new_socket){
	delay();
	if (send(new_socket, message, strlen(message), 0) != -1){
		printf("message sent %s\n", message); 
		return 0; 
	}
	else{
		printf("message not sent!!\n"); 
	}
	return 1; 
	//message not sent 
}


int receive_message(int sock, size_t nbytes, char *buffer){
	if (read(sock, buffer, 1024) != -1){
		printf("message received: %s\n", buffer); //we read the response on the socket. 
		return 0; 
	} 

	if (buffer == NULL){
		printf("Invalid response from server\n"); 
		return 1; 
	}
	return 1; 
}

void delay()
{
	int c, d;
   
   	for (c = 1; c <= 32767; c++) {
		for (d = 1; d <= 3000; d++) {
			;
		}
	}
}