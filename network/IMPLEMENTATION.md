# CS50 final project network module
## Implementation Specification

In this document we reference the [Requirements Specification](REQUIREMENTS.md) and [Design Specification](DESIGN.md) and focus on the implementation-specific decisions.
Here we focus on:

-  Control flow
-  Detailed function prototypes and their parameters
-  Error handling and recovery
-  Testing plan


## Control flow

Server-side methods are implemented in `serverNetwork.c` and client-side methods are implemented in `clientNetwork.c`

I have made `serverTest.c` and `clientTest.c` to make sure all of these methods work to meet our networking needs for the final project, and simulate
a real black-jack iteration. 

## Detailed function prototypes and their parameters
- Sending and receiving messages are functionally identical for the client and the server, so I will go over each of them once here. 


### 1. establish_server_connection

Given an IPAddress and PORT, establish a server listening on IPAdress and PORT that can 1) connect with incoming clients, 2) send and receive messages, and 3) terminate
Pseudocode: 
    initialize a socket; 
    bind our socket to the given IPAddress and PORT; 
    listen for incoming client connections; 
    accept client connections; 
    return serverData //struct that holds pointers to the server_fd and socket. Needed for server shutdown and messaging; 


### 2. establish_client connection
Pseudocode: 
    initialize a socket; 
    connect to server with this socket over given IPAddress and PORT; 
    listen for incoming client connections; 
    accept client connections; 
    return pointer to socket; 



### 3. send_message

Send a message to the client. Takes the message being sent as a char*. 
Simply calls the send() built into our imported networking modules.

Ex:   send(sock, hello, strlen(hello), 0) sends the message hello over a give socket with flags set to 0. We wrap this method in a function so our 
caller only needs to provide the message. 

### 4. receive_message

Receive a message from a client. Takes the socket we're communicating on, an estimated number of bytes for the incoming message, and string buffer to hold the message
Simply calls the read() built into our imported networking modules. 

Ex: read(sock, buffer, 1024); reads the chars coming over the socket into a buffer for later use. 

## Other modules

Other necessary modules like arpa/inet.h, sys/socket.h, and unistd.h are all imported at the beginning of clientNetwork.h and serverNetwork.h
which provide for us the built functions we create wrapper methods around for ease of use. 

## Function prototypes

### serverNetwork

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in `serverNetwork.h` and is not repeated here.

```c
int* establish_server_connection(char* IPAdress, int PORT); //needs to return pointer to right socket, should be 'sock'
void terminate_server_connection(server_data_t* data); 
int receive_message(int sock, size_t nbytes, char* buffer); 
int send_message(const char* message, int new_socket); 
void delay(int number_of_milliseconds);

```

### clientNetwork

Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's declaration in `clientNetwork.h` and is not repeated here.

```c
1. int* establish_client_connection(char* IPAdress, int PORT); //needs to return pointer to right socket, should be 'sock'
2. void terminate_client_connection(int client_fd); 
3. int receive_message(int sock, size_t nbytes, char* buffer); 
4. int send_message(const char* message, int new_socket); 
5. void delay(int number_of_milliseconds);

```

## Error handling and recovery


All wrapper functions handle for errors along every step of the connection process for both server and client. In the code provided by geeksforgeeks, establishing a client 
or server connection has each step wrapped in conditionals checking for propper return values. The connection process is sequential, so no next step can be completed if the prior one fails. If we do have a failure, we just message through stderr to the user and exit the function. 


Out-of-memory errors are handled in the same fashion as we have done in previous labs, through variants of the `mem_assert` functions, which result in a message printed to stderr and a non-zero exit status.We anticipate out-of-memory errors to be rare and thus allow the program to crash (cleanly) in this way.

All code uses defensive-programming tactics to catch and exit (using variants of the `mem_assert` functions), e.g., if a function receives bad parameters.

## Testing plan

All testing is accomplished through serverTesting.c and clientTesting.c

### Unit testing

There are only two parts: the client code and the server code.
We test both using basic executables from the above testing files. 


### Integration/system testing

We have written a bashscript to run conitnuous games of blackjack to train our player. This script includes programs that utilize the methods here to connect the player
to the dealer. 