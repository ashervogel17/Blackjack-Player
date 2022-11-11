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
#include "../cards/cards.h"
#include "../network/clientNetwork.h"
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

const int MAX_DECISIONS = 21;
const int MAX_CARD_CHARS = 20;

static int parseArgs(const int argc, char* argv[], char** name, char** IPAddress, int* port,
    char** decisionmakerFilename, bool* isTraining);

static void play(bool isTraining, decisionmaker_t* decisionmaker, char* name, char* IPAdress, int port, char* decisionmakerFilename);

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
        free(*name);
        free(name);
        free(*IPAddress);
        free(IPAddress);
        free(port);
        free(*decisionmakerFilename);
        free(decisionmakerFilename);
        free(isTraining);
        // decisionmaker_delete(decisionmaker);
        return 0;
    }

    // play the game
    play(*isTraining, decisionmaker, *name, *IPAddress, *port, *decisionmakerFilename);

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

static void play(bool isTraining, decisionmaker_t* decisionmaker, char* name, char* IPAddress, int port, char* decisionmakerFilename) {
    // declare variables
    char* dealerCard = NULL;
    char* playerHand = NULL;
    char* state = NULL;
    int action;
    int* actionArray = NULL;
    char** stateArray = NULL;
    int loc;
    int reward;
    hand_t* hand; // player hand
    int game_count = 0;
    int win_count = 0;
    int push_count = 0;
    int loss_count = 0;
    char* message = NULL; // string to receive message from server

    // messages to send to server
    char* join = malloc(sizeof(char)*(strlen("JOIN ") + strlen(name) + 1));
    char* hit = malloc(sizeof(char)*4);
    char* stand = malloc(sizeof(char)*6);
    strcpy(join, "JOIN ");
    strcat(join, name);
    strncpy(hit, "HIT", strlen("HIT") + 1);
    strncpy(stand, "STAND", strlen("STAND") + 1);

    // establish connection to server and send join message
    int* socketPointer = establish_client_connection(IPAddress, port);
    int new_socket = *socketPointer; 
    send_message(join, new_socket); 
    free(join);
    
    // int sent_join_message = -1;
    
    // main while loop
    while (true) {
        message = malloc(500*sizeof(char));
        receive_message(new_socket, 500, message); 

        // handle message
        if (strcmp(message, "BEGIN") == 0) {
            // printf("\n\n NEW GAME (#%d)\n\n", game_count);
            hand = handNew();
            actionArray = calloc(MAX_DECISIONS, sizeof(int));
            stateArray = calloc(MAX_DECISIONS, sizeof(char*));
            loc = 0;
        }
        else if (strcmp(message, "DECISION") == 0) {
            #ifdef DEBUG
            printf("My hand:\n");
            handPrint(hand);
            printf("Dealer showing: %s\n", dealerCard);
            #endif
            if (handGetValueOfHand(hand) >= 19) { 
                action = 0;
            }
            else if (handGetValueOfHand(hand) <= 11) {
                action = 1;
            }
            else {
                if (isTraining) { // training mode
                    action = rand() % 2;
                }
                else { // tournament mode
                    action = decisionmaker_decide(decisionmaker, state);
                }
            }
            
            playerHand = handSortedString(hand);

            stateArray[loc] = malloc(sizeof(char)*(strlen(dealerCard)) + 1 + strlen(playerHand) + 1);
            strcpy(stateArray[loc], dealerCard);
            strcat(stateArray[loc], " ");
            strcat(stateArray[loc], playerHand);

            free(playerHand);

            #ifdef DEBUG
            printf("added state: %s\n\n", stateArray[loc]);
            printf("all states:\n");
            for (int i=0; i<=loc; i++) {
                printf("%s\n", stateArray[i]);
            }
            printf("\n");
            #endif
            if (action == 0) {
                send_message(stand, new_socket);
            }
            else {
                send_message(hit, new_socket);
            }
            
            actionArray[loc] = action;
            loc++;
        }
        

        // message is either CARD, DEALER, or RESULT
        else if (*message == 'C') {
            // char* cardString = malloc(sizeof(char)*MAX_CARD_CHARS);
            char* rank = calloc(10, sizeof(char));
            char* suit = calloc(10, sizeof(char));
            if (sscanf(message, "CARD %s of %s", rank, suit) != 2) {
                fprintf(stderr, "Invalid CARD message received\n");
                free(rank);
                free(suit);
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(actionArray);
                free(stateArray);
                handDelete(hand);
                free(hit);
                free(stand);
                exit(1);
            }
            card_t* card = cardNew(rank, suit);
            if (card == NULL) {
                free(rank);
                free(suit);
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(actionArray);
                free(stateArray);
                handDelete(hand);
                free(hit);
                free(stand);
                exit(1);
            }
            handAddCard(hand, card);
            free(rank);
            free(suit);
        }
        else if (*message == 'D') {
            dealerCard = calloc(10, sizeof(char));
            char* suit = calloc(10, sizeof(char));
            if (sscanf(message, "DEALER %s of %s", dealerCard, suit) != 2) {
                fprintf(stderr, "Invalid DEALER message received\n");
                free(dealerCard);
                free(suit);
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(actionArray);
                free(stateArray);
                handDelete(hand);
                free(hit);
                free(stand);
                exit(1);
            }
            if (strcmp(dealerCard, "Jack") == 0 || strcmp(dealerCard, "Queen") == 0 || strcmp(dealerCard, "King") == 0) {
                    strcpy(dealerCard, "Ten");
                }
            card_t* dealerCardStruct = cardNew(dealerCard, suit);
            if (dealerCardStruct == NULL) {
                fprintf(stderr, "Invalid DEALER message received\n");
                free(dealerCard);
                free(suit);
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(actionArray);
                free(stateArray);
                handDelete(hand);
                free(hit);
                free(stand);
                exit(1);
            }
            cardDelete(dealerCardStruct);
            free(suit);
        }
        else if (*message == 'R') {
            if (strcmp(message, "RESULT WIN") == 0 || strcmp(message, "RESULT LOOSE") == 0 || strcmp(message, "RESULT PUSH") == 0 || strcmp(message, "RESULT BUST") == 0) {
                // update average rewards
                game_count++;
                if (strcmp(message, "RESULT WIN") == 0) {
                    reward = 1; 
                    // printf("Win\n");
                    win_count += 1;
                }
                else if (strcmp(message, "RESULT LOOSE") == 0 || strcmp(message, "RESULT BUST") == 0) {
                    reward = -1;
                    // printf("Lose\n");
                    loss_count += 1;
                }
                else {
                    reward = 0;
                    // printf("Push\n");
                    push_count += 1;
                }
                for (int i=0; i < loc; i++) {
                    decisionmaker_update(decisionmaker, stateArray[i], actionArray[i], reward);
                }
                
                if (game_count % 1000 == 0) {
                    printf("%d %*s | %d %*s | %d %*s | %*s %f%s",
                        game_count, 5, "games", win_count, 5, "wins", push_count, 5, "pushes",
                        5, "win percentage:", (100*(float) win_count/(float) game_count), "%\n");
                    fflush(stdout);
                }

                // free memory
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(dealerCard);
                free(actionArray);
                free(stateArray);
                handDelete(hand);
            }
            else {
                fprintf(stderr, "Invalid RESULT message received\n");
                for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
                }
                free(dealerCard);
                free(actionArray);
                free(stateArray);
                handDelete(hand);
                free(hit);
                free(stand);
                exit(1);
            }
        }
        else if (strcmp(message, "QUIT") == 0) {
            printf("got quit message\n");
            free(message);
            break;
        }
        else {
            fprintf(stderr, "Received unfamiliar command: %s\n", message);
            for (int i=0; stateArray[i] != NULL; i++) {
                    free(stateArray[i]);
            }
            free(dealerCard);
            free(actionArray);
            free(stateArray);
            handDelete(hand);
            free(hit);
            free(stand);
            exit(1);
        }
        
        if (message != NULL) {
            free(message);
        }
    }
    printf("closing connection\n");
    // printf("%d games , we won %d, pushed %d, and lost %d.\n", game_count, win_count, push_count, loss_count);
    terminate_client_connection(new_socket);
    free(hit);
    free(stand);
    printf("%d %*s | %d %*s | %d %*s | %*s %f%s",
        game_count, 5, "games", win_count, 5, "wins", push_count, 5, "pushes",
        5, "win percentage:", (100*(float) win_count/(float) game_count), "%\n");
    fflush(stdout);
    #ifdef DEBUG
    printf("terminated connection\n");
    fflush(stdout);
    #endif
}
