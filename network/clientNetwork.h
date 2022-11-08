/*
header file for setting up server connection on client side
Does all the work to get a client connected and sending messages to the server socket. 

All the functionality is accompllished through one method that does all the work for you, since the real work begins with string parsing. The below method
just sets up the client so that it's sending/receiving messages from the server. 



Elias Rosenberg, 22F, CS50
*/
#ifndef __CLIENT_NETWORK_H
#define __CLIENT_NETWORK_H

/**************** establish_client_connection ****************/
/* 
The basic idea for client connection 



 */

//return client_fd
int establish_client_connection(char* IPAdress, int PORT);



void terminate_client_connection(int client_fd);


//read(sock, buffer, 1024); //we read the response on the socket. 
int receive_message(int sock, size_t nbytes); 


//send(sock, line, strlen(hello), 0); //send here is equivalent to write
int send_message(int sock, const char* message, size_t line_size); 



    



#endif //__SERVER_H