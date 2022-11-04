/*
Purpose: Header file for server.h
As I understand it, the server is setup (through our executable './server') before any clients can connect to it. First, it creats a socket object that then binds/
listens to a port on an IP address. Here I am using local host, but in our actual project we need to use 'localhost:8000 + team#'. Then, it waits for clients that 
are trying to connect through their own socket that binds to the same address. Once a client sucessfully connects, we can read requests and write responses back to them. 

-We're going to have to figure out some internal string parsing methods to actually communicate between client and server. 

Elias Rosenberg, 22F, CS50
*/

#ifndef __SERVER_H
#define __SERVER_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8014

int socket (int family, int type, int protocol);
int bind(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);

















#endif //__SERVER_H