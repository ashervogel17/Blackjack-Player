# CS50 TSE Querier
## Requirements Spec

> In a requirements spec, **shall do** means **must do**.

The network module gives the user wrapper methods to establish a server, client, and begin sending messages between the two. The server functions are necessary for
our dealer program that must host a server players can connect to, and run black-jack games. The client functions allow players to join a dealer-hosted server and play
a game. The game is played by messages sent back and forth between the server and its clients that are strings sent over sockets. 

The network module **shall**:

1. provide functions that allow a caller to establish a server, listen for connecting clients, send messages, receive messages, and terminate the server.
2. provide functions that allow a caller to establish a client socket, connect to a server, send messages, receive messages, and terminate the client. 

## Networks

Networks operate on a few basic building blocks that are shared between a server and a client. For both the server and the client we first create a *socket* object that 
servers as our bridge of internet protocol to pass messages. The server *binds* its socket object to an *IPAdress* and *PORT* given by the caller. It then listens for clients to connect their socket object to the same IPAdress and PORT. Once a server *accepts* a client's request to connect, they can begin sending and receiving messages
to eachother over their shared socket. 

### Jargon

A *socket* is a networking object that allows for the transfer of data (chars in this case) between server and client. The socket follows a given  
set of internet messaging protocols. In our case we will be using AF_INET and AF_I NET

*binding* is the process by which a server begins listening to a specific IPAdress and PORT

*IPAddress*: "a unique string of characters that identifies each computer using the Internet Protocol to communicate over a network."

*PORT*: "a number assigned to uniquely identify a connection endpoint and to direct data to a specific service"


Example structure of a client-server connection. 
![Alt text](https://media.geeksforgeeks.org/wp-content/uploads/20220330131350/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png "client-server connection diagram"); 