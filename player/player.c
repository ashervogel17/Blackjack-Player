/* 
 * player.c -

 * input:
 * output:
 *
 * compile: mygcc -o player player.c decisionmaker.c ../libcs50/libcs50-given.a -I../libcs50 -DDEBUG
 * usage: ./player name IPAdress port decisionmakerFilename [training]
 * 
 * Asher Vogel
 * CS 50, Fall 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <file.h>
#include "decisionmaker.h"

const int MAX_DECISIONS = 21;
const int MAX_CARD_CHARS = 20;

static int parseArgs(const int argc, char* argv[], char** name, char** IPAddress, int* port,
    char** decisionmakerFilename, bool* isTraining);

static void play(bool isTraining, decisionmaker_t* decisionmaker);

int main (const int argc, char* argv[]) {
    // allocate memory for pointers
    char** name = malloc(sizeof(char*));
    char** IPAddress = malloc(sizeof(char*));
    int* port = malloc(sizeof(int*));
    char** decisionmakerFilename = malloc(sizeof(char*));
    bool* isTraining = malloc(sizeof(bool*));

    // parse arguments
    int error = parseArgs(argc, argv, name, IPAddress, port, decisionmakerFilename, isTraining);
    if (error != 0) {
        free(name);
        free(IPAddress);
        free(port);
        free(decisionmakerFilename);
        free(isTraining);
        return 0;
    }
    #ifdef DEBUG
    else {
        printf("Parameters accepted\n");
    }
    #endif

    // load decisionmaker. If it's NULL, set it equal to an empty decisionmaker
    decisionmaker_t* decisionmaker = decisionmaker_load(*decisionmakerFilename);
    if (decisionmaker == NULL) {
        fprintf(stderr, "Unable to load decisionmaker. Initializing decisionmaker to empty\n");
        decisionmaker = decisionmaker_new();
    }

    // connect to server
    // THIS FUNCTION WILL BE WRITTEN BY ELI

    // play the game
    // play(*isTraining, decisionmaker);

    // save decisionmaker to memory
    decisionmaker_save(decisionmaker, *decisionmakerFilename);

    // clean up
    free(*name);
    free(name);
    free(*IPAddress);
    free(IPAddress);
    free(port);
    free(*decisionmakerFilename);
    free(decisionmakerFilename);
    free(isTraining);
    decisionmaker_delete(decisionmaker);
    return 0;
}

/**
 * Validate command-line parameters and set pointers to important variables
 * 
 * Notes:
 *      IP Address must be of the form "%d.%d.%d.%d"
 *      Port must be an integer on the range [1, 65535]
 *      Regardless of return value, the caller is responsible for:
 *          freeing all pointers passed as parameters
 * */
static int parseArgs(const int argc, char* argv[], char** name, char** IPAddress, int* port,
    char** decisionmakerFilename, bool* isTraining) {
        // validate number of parameters
        if (argc != 5 && argc != 6) {
            fprintf(stderr, "Incorrect usage. Usage: ./player name IPAdress port decisionmakerFilename [training]\n");
            return 1;
        }

        // allocate memory for and set name with safety check
        *name = malloc(strlen(argv[1]) + 1);
        if (strcpy(*name, argv[1]) == NULL) {
            fprintf(stderr, "An error occurred copying player name\n");
            free(*name);
            return 2;
        }
        
        // allocate memory for and set IPAddress with safety check
        *IPAddress = malloc(strlen(argv[2]) + 1);
        if (strcpy(*IPAddress, argv[2]) == NULL) {
            fprintf(stderr, "An error occurred copying IP Address\n");
            free(*name);
            free(*IPAddress);
            return 3;
        }

        // ensure valid IPAddress
        int one, two, three, four;
        if (sscanf(*IPAddress, "%d.%d.%d.%d", &one, &two, &three, &four) != 4) {
            fprintf(stderr, "Invalid IP Address\n");
            free(*name);
            free(*IPAddress);
            return 4;
        }

        // set port with safety check
        if (sscanf(argv[3], "%d", port) != 1) {
            fprintf(stderr, "Port must be an integer\n");
            free(*name);
            free(*IPAddress);
            return 5;
        }

        // ensure port lies on range [1, 65535]
        if (*port < 1 || *port > 65535) {
            fprintf(stderr, "Port must be an integer between 1 and 65,535 inclusive\n");
            free(*name);
            free(*IPAddress);
            return 6;
        }

        // allocate memory for and set decisionmakerFilename with safety check
        *decisionmakerFilename = malloc(strlen(argv[4]) + 1);
        if (strcpy(*decisionmakerFilename, argv[4]) == NULL) {
            fprintf(stderr, "An error occurred copying training filename\n");
            free(*name);
            free(*IPAddress);
            free(*decisionmakerFilename);
            return 7;
        }

        // tournament mode
        if (argc == 5) {
            *isTraining = false;
        }
        // training mode
        else {
            // validate training parameter
            if (strcmp(argv[5], "training") != 0) {
                fprintf(stderr, "Optional 5th parameter must be \"training\"\n");
                free(*name);
                free(*IPAddress);
                free(*decisionmakerFilename);
                return 8;
            }
            *isTraining = true;
        }

        return 0;
    }

static void play(bool isTraining, decisionmaker_t* decisionmaker) {
    char* dealerCard = NULL;
    char* playerHand = NULL;
    char* state = NULL;
    int action;
    int* actionArray = NULL;
    char* stateArray = NULL;
    int loc;
    int reward;

    char* message; // = message from server;
    // hand_t* hand = newHand();
    
    while (strcmp(message, "QUIT") != 0) {
        if (strcmp(message, "BEGIN") == 0) {
            // inialize empty hand
            actionArray = calloc(MAX_DECISIONS, sizeof(int));
            char* stateArray = calloc(MAX_DECISIONS, sizeof(char*));
            loc = 0;
        }
        else if (strcmp(message, "DECISION") == 0) {
            if (!isTraining) { // tournament mode
                action = decisionmaker_decide(decisionmaker, state);
            }
            else {
                // playerHand = sorted hand string (need to write this function)

                state = malloc(sizeof(char)*(strlen(dealerCard)) + 1 + strlen(playerHand) + 1);
                strcpy(state, dealerCard);
                strcat(state, " ");
                strcat(state, playerHand);

                free(dealerCard);
                free(playerHand);

                // if (hand score is 21) {
                //     action = 0;
                // }
                // else if (hand score <= 11) {
                //     action = 1;
                // }
                // else {
                //     action = rand() % 2;
                // }
                actionArray[loc] = action;
                stateArray[loc] = state;
                loc++;

                // send message with action
            }

        }
        // message is either CARD, DEALER, or RESULT
        if (*message == 'C') {
            char* cardString = malloc(sizeof(char)*MAX_CARD_CHARS);
            if (sscanf(message, "CARD %s", cardString) != 1) {
                fprintf(stderr, "Invalid CARD message received\n");
            }
            //card_t* card = parseCard(cardString);
            // addCardToHand(hand, card);
            free(cardString);
        }
        else if (*message == "D") {
            dealerCard = malloc(sizeof(char)*10);
            char* suit = malloc(sizeof(char)*10);
            if (sscanf(message, "DEALER %s of %s", dealerCard, suit) != 2) {
                fprintf(stderr, "Invalid DEALER message received\n");
            }
            free(suit);
        }
        else if (*message == "R") {
            if (strcmp(message, "WIN") == 0 || strcmp(message, "LOOSE") == 0 || strcmp(message, "PUSH") == 0) {
                // if training, update average rewards
                if (isTraining) {
                    if (strcmp(message, "WIN") == 0) {
                        reward = 1;
                    }
                    else if (strcmp(message, "LOOSE") == 0) {
                        reward = -1;
                    }
                    else {
                        reward = 0;
                    }
                    for (int i=0; stateArray[i] != NULL; i++) {
                        decisionmaker_update(decisionmaker, stateArray[i], actionArray[i], reward);
                    }
                }

                // free memory
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(actionArray);
                free(stateArray);
            }
            else {
                fprintf(stderr, "Invalid RESULT message received\n");
            }
        }
        else {
            fprintf(stderr, "Received unfamiliar command\n");
        }
        free(message);
        // get next message
        
    }
    

}