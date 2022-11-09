/*
header file for setting client connection to an already active server
Does all the work to get a client connected and sending string messages to the server socket. 

All the complicated functionality of esatblishing a connection to the server is accomplished by calling establish_client_connection with the 
same IPAdress and PORT used by the server

Users send and receive messages with wrapper functions send_message and receive_message, and end the client's connection with another wrapper function 
called terminate_client_connection

Elias Rosenberg, 22F, CS50
*/
#ifndef __CLIENT_NETWORK_H
#define __CLIENT_NETWORK_H




/*
The caller provides: 
char* IPAddress (ex. "129.170.64.104"), int PORT to connect our socket to, here we are using 8094 (8080 + our team number)

We do: establish connection between client and server, allowing the client to send/receive messages. 

Notes: 
How the client actually connects to the server is kind of complicated, but is explained thorougly here: https://www.geeksforgeeks.org/socket-programming-cc/
- In Short: 
1. The client creates a blank 'socket' object, which is the bridge that will eventually connect to our server
2. We connect that socket to the server through our shared IPAddress and PORT

*/
int* establish_client_connection(char* IPAdress, int PORT); //needs to return pointer to right socket, should be 'sock'


/*
The caller provides: 
The number representing the socket object the client is currently listening on. 

We do: exit the client from the server, and delete that socket object

Notes: Most of these functions are just wrappers for pre-existing network module functions. This one is a wrapper for 'close()'
- in our testing file, typing "QUIT" will exit the loop, bring us the calling of this function. 

*/
void terminate_client_connection(int client_fd); 

/*
The caller provides: 
The socket we're listening on, the estimated number of bytes needed for the string we're receiving from the server (I use 1024 here for safety but shouldn't need more than 100)
and the string buffer we're saving our message to. If we need to move this string around functions, buffer should be mem-alloc'd

We do: 
Read chars in from the server and save them to our buffer. 

Notes: 
-this is a wrapper method for the network module function read()
-If user saves the message to a string that is alloc'd in memory, they are responsible for freeing it. 


*/ 
int receive_message(int sock, size_t nbytes, char* buffer); 


/*
The caller provides: 
A string of the message they would like to send to the server, as well as the socket they are currently connected to the server on. 

We do: 
Send the string message over the given socket to the server

Notes: 
Calls the module function send()

*/
int send_message(const char* message, int new_socket); 

/*
We need our own implementation of a delay function 
*/
void delay();

#endif //__SERVER_H