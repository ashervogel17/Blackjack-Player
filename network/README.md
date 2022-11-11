## The Networking Module
The networking module is built to encompass all functionality necessary for establishing connection between a server and client over sockets in C. 
The core of the code was altered from https://www.geeksforgeeks.org/socket-programming-cc/ and is seperated out into clientNetwork.h and serverNetwork.h which 
deal with client-side connection and server-side connection, respectively. Because the code for network connection is fairly complicated, clientNetwork.h and 
serverNetwork.h establish wrapper functions for all module functions from sys/socket.h and arpa/inet.h. We compile these two files into a network module 'network.a'
that can then be used by our dealer and player to connect over a network and play black-jack. 

## To Run 
To run the methods to establish server-client connection in other modules, import the network directory and run the given Makefile. 
To run testing files serverTest.c and clientTest.c run `gcc serverTest.c serverNetwork.c ../cards/cards.c -o serverTest` and `clientTest.c clientNetwork.c ../cards/cards.c -o clientTest`

## serverNetwork.h
Holds methods for establishing a server that a client can then connect to, sending/receiving messages from clients, and terminating all server-client sockets as well as
the server itself. 

## clientNetwork.h
Holds methods for connecting a client to a server, sending/receiving messages from teh server, and terminating connection. 

## Testing
Before hooking up our player to Pierson's dealer, we have been testing running games over our own dealer.c and player.c that utilize methods from this network module. The basic wrapper functions have all been tested in serverTest.c and clientTest.c that simply allows for undless client-server communication through stdin. 