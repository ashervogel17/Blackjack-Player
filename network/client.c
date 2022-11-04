// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8014 //port 8000 + team number --> 8014

int main(int argc, char const* argv[])
{
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { //create the socket object
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
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

	int SIZE = 200; 
	char line[SIZE];
	printf("Please enter your message to server...\n"); 
    fgets(line, SIZE, stdin);
    while (strcmp(line, "exit\n") != 0) {
        printf("message: %s\n", line); 
		send(sock, line, strlen(hello), 0); //send here is equivalent to write
		valread = read(sock, buffer, 1024); //we read the response on the socket. 
		printf("%s\n", buffer);

        
        if (line == NULL){
            printf("Invalid message \n"); //if our query is invalid, go to next iteration to get new query
            return 1; 
        }

		if (buffer == NULL){
			printf("Invalid response from server\n"); 
			return 2; 
		}
		printf("Please enter your message to server...\n");
        fgets(line, SIZE, stdin);
        
    }
	send(sock, line, strlen(hello), 0); //send here is equivalent to write
	// closing the connected socket
	close(client_fd);
	return 0;
}
