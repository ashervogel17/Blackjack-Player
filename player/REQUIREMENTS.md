# CS50 Player
## Requirements Specification

> In a requirements spec, **shall do** means **must do**.


The player  **shall**:

* run from the command line taking the player’s name, server’s IP address, and PORT number as parameters
* connect to the server using a socket
* have a training mode where it plays many games with the dealer program, choosing random actions
* must be able to write its decisionMaker (Q) table to disk and read it back
* must be able to continue training after reading the decisionMaker table from disk
* have a play mode where it makes optimal decisions based on what it learned during training
* reads decisionMaker table written to disk during training
* uses table data to make optimal decisions

## command line execution
1. execute from a command line with usage syntax `./player name IPAdress port decisionmakerFilename (training case)`
    * where `name` is the string name of the player
    * where `IPAdress` is the string IPAddress through which the socket connection is facilitated
    * where `port` is an integer indicating the port number of the connection
    * where `decisionmakerFilename` is a string of the decisionMakerfilename from which data is written in the training case. This file contains the saved gameplay and training data for the decisionmaker structure so that training can easily run over time.
    
2. The player module will after parsing the arguments implement a play function which establishes a connection to the server, sends a join message, reads messages from the server and either plays random games in a training mode or decides what to do based on the data compiled in the decisionMaker hashtable of information 

## parseArgs 
* the player module implements a parseArgs() function which will ensure that all of the mentioned parameters needed in the command line execution are valid.

**Assumption**:
The `pageDirectory` does not already contain any files whose name is an integer (i.e., `1`, `2`, ...).

**Limitation**:
The Crawler shall pause at least one second between page fetches, and shall ignore non-internal and non-normalizable URLs.
(The purpose is to avoid overloading our web server and to avoid causing trouble on any web servers other than the CS50 test server.)