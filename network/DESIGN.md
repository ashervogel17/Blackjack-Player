# CS50 Final Project Network Module
## Design Spec

Based on our Requirements.md, we are tasked with writing out the functions that wrap the methods for forming and utilizing server-client connections. Apart from dealing
with server/client mishaps and shutdowns, there are no args we have to parse, and most error catching is done on the part of the programs in which these wrapper methods
are utilized. 

### Inputs and outputs

**Input**: When setting up the the both the client and server connections, the caller is required to give the desired IPAddress and PORT number they'd like to connect to. 

**Output**: We print `Connection esatblished at address: yourAddress, listening on port: yourPort` to stdout if connection has been successful. Other than that, we print all messages sent between client and server to show successful use. 
### Functional decomposition into modules

We anticipate the following functions...

For the client: 
1. int* establish_client_connection(char* IPAdress, int PORT); //needs to return pointer to right socket, should be 'sock'
2. void terminate_client_connection(int client_fd); 
3. int receive_message(int sock, size_t nbytes, char* buffer); 
4. int send_message(const char* message, int new_socket); 
5. void delay(int number_of_milliseconds);

For the server: 
1. int* establish_server_connection(char* IPAdress, int PORT); //needs to return pointer to right socket, should be 'sock'
2. void terminate_server_connection(server_data_t* data); 
3. int receive_message(int sock, size_t nbytes, char* buffer); 
4. int send_message(const char* message, int new_socket); 
5. void delay(int number_of_milliseconds);



### Pseudo code for logic/algorithmic flow

The general outline for our server is as follows...
1. Begin the server by calling establish_server_connection. This creates the socket object, binds it to our PORT and IPAddress, listens for client connections, accepts new clients, and then listens to server messages. 
2. We then parse messages from the client, parse them, and send back the necessary message to keep the game going. 
3. When we reach the desired number of games, or either party sends the message "QUIT", we terminate the server by calling terminate_server_connection(). 

The general outline for our client is fairly similar...
1. Once the server is established, we connect our client to the server using establish_client_connection(). 
2. On our first iteration of games, we send "JOIN" to the server, who then responds with "BEGIN" which starts our game. 
3. We converse with the server as long as we haven't hit our game limit, the connection times out, or the client sends "QUIT" ()

---the core pseudocode for both programs--

establish_server_client_connection(IPAddress, PORT); 
build the new deck
while user message != "QUIT" && gameCount < maxGames;
    parseServerMessage(); 
        follow Pierson's message diagram
        if user is done playing: 
            break; 
free game objects; 
terminate_server_connection(server_data_t* data); 

### Major data structures

All key data structures for the networking module are prebuilt in the imported networking modules. The main programs that use these functions are dealer and player, 
each of which utilize the *deck* *card* and *hand* objects. Those data structures are thoroughly documented in their respective .md files. 

### Testing plan
The only testing done for our network module will be implementation testing in serverTest.c and clientTest.c to make sure we can send messages back and forth between our 
own client and server.  

Testing these functions and learning how to code for networks in c is best done incrementally. My work process was as follows. 

1. Using the code given from geeksforgeeks, try to send a single message from a server to a client. 
2. Alter that code to send messages continuously from the client to a server. 
3. Implement endless, bidirectional messaging.
4. Begin parsing the specific messages needed to play the game of black-jack on both the player and dealer sides. 
5. Run 100 successive games. 
6. Run 1000 successive games. 