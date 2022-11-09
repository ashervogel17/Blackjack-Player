/*
Purpose: Header file for server.h
Wraps all methods from sys/socket.h into easier wrapper methods. For the client-server functionality to work THE SERVER MUST BE SETUP FIRST USING THESE METHODS.
We hide all the complicated server setup behind establish_server_connection, and give wrapper methods for terminating the all the sockets attached to clients
(we only handle one client, but Pierson's implementaion can handle up to six) and deleting the server socket itself. We also give methods for sending and receiving 
messages from the client. 

Elias Rosenberg, 22F, CS50
*/

#include <stddef.h>

#ifndef __SERVER_NETWORK_H
#define __SERVER_NETWORK_H

/*
When we establish ther server, we need pointers to two important things: the actual socket object the server is listening on, as well as the socket descriptor
- I never figured out what the socket descriptor actually does, but it is necessary for shutting down the server so we need it here. 
*/
typedef struct server_data server_data_t; 

/*
This method is called internally in establish_server_connection. It takes a pointer to the final socket the server will be listening on for messages and a pointer
to the server descriptor needed to shut down the server. 
*/
server_data_t* serverData_new(int* socket, int* server_fd); 

/*
The caller provides: 
A desired IPAddress the server will connect to, as well as a PORT. In our case, the IPAddress should be Plank's (129.170.64.104), and the PORT is 8094

We do: All the steps needed to setup a socket listening to that PORT and IPAddress that will also accept connections from new clients

Notes: 
How this actually works is best described here https://www.geeksforgeeks.org/socket-programming-cc/
In summary: 
1) we establish a socket object and what protocols it will be using for communication. We're using AF_INET
2) we then bind this socket to our given IPAddress and PORT
3) we then listen for new connections from potential clients, and accept them if the connection is valid
4) We can now send and receive messages from clients. 
*/
server_data_t* establish_server_connection(char* IPAddress, int PORT);


/*
Caller provides: server_data_t struct returned by establish_server_connection. To terminate a server, we need to close the sockets it is communicating with clients on, 
as well as the server's own socket. This struct holds both as pointers to 'socket' and 'server_fd'

We do: Close all connections between server and its clients, as well as the socket the server is running on

Notes: 
Like clientNetwork.h, we are building a wrapper for network module functionality. This function calls close() on the server/client socket, and shutdown() on the server
descriptor. 
*/
void terminate_server_connection(server_data_t* data); 


/*
Caller provides: The socket our client/server connection is currently on, the number of bytes we roughly believe our message from the server will be, and a string buffer
to save our string to

We do: Save the chars read from the client to our string buffer

Notes: 
- Wrapper for the method send(), which is the same as our client's send() --> Sending and receiving messages from either client or server is basically the same. 
If the user provides a mem_alloc'd string buffer they are responsible to free it. 
*/
int receive_message(int sock, size_t nbytes, char *buffer); 


/*
Caller provides: The string they want to send to the client on given socket 'new_socket'

We do: send the given message over the socket to the client through calling send()

Notes: 
If confused about any of this, please look at clientTest.c and serverTest.c to see how to establish a client/server connection and send messages back and forth through stdin. 

*/
int send_message(const char* message, int new_socket); 

/*
We need our own implementation of a delay function 
*/
void delay();


#endif //__SERVER_H