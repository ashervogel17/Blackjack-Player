/* 
 * decisionmaker.h - wrapper for CS50 hashtable module
 *
 * A *hashtable* where:
 *      the keys represent the current state of the blackjack game
 *      the items are structs that store:
 *          number of hands won when staying
 *          number of hands won when hitting
 *          number of hands played when staying
 *          number of hands played when hitting
 * 
 * Asher Vogel
 * CS 50, Fall 2022
 */

#ifndef __DECISIONMAKER_H
#define __DECISIONMAKER_H

#include <stdbool.h>
#include <hashtable.h>

typedef struct hashtable decisionmaker_t;

typedef struct decision_outcomes decision_outcomes_t;

/* Create a new (empty) decisionmaker.
 *
 * We return:
 *   pointer to the new decisionmaker; return NULL if error.
 * We guarantee:
 *   decisionmaker is initialized empty.
 * Caller is responsible for:
 *   later calling decisionmaker_delete.
 */
decisionmaker_t* decisionmaker_new();

/* Insert decisionmaker_outcomes, identified by state (string), into the given decisionmaker.
 *
 * Caller provides:
 *   valid pointer to decisionmaker, valid string for state, valid pointer for decisionmaker_outcomes.
 * We return:
 *   false if key exists in decisionmaker, any parameter is NULL, or error;
 *   true iff new decisionmaker_outcomes was inserted.
 * Notes:
 *   The state string is copied for use by the decisionmaker; that is, the module
 *   is responsible for allocating memory for a copy of the state string, and
 *   later deallocating that memory; thus, the caller is free to re-use or 
 *   deallocate its state string after this call.  
 */
bool decisionmaker_insert(decisionmaker_t* decisionmaker, const char* state, decision_outcomes_t* decision_outcomes);


/* Return the decision_outcomes associated with the given state.
 *
 * Caller provides:
 *   valid pointer to decisionmaker, valid string for state.
 * We return:
 *   pointer to the decision_outcomes corresponding to the given state, if found;
 *   NULL if decisionmaker is NULL, state is NULL, or key is not found.
 * Notes:
 *   the decisionmaker is unchanged by this operation.
 */
decision_outcomes_t* decisionmaker_find(decisionmaker_t* decisionmaker, const char* state);

/**
 * Function used for tournament gameplay. Decide the optimal move given current state.
 * Caller provides:
 *      valid pointer to decisionmaker, valid string for state
 * We return:
 *      1 if the win probability for hitting is higher
 *      0 if the win probability for staying is higher
 *      0 is something goes wrong (NULL decisionmaker or state)
 * Notes:
 *      We hit if the win probailities are equal
 *      The decisionmaker is unchanged by this operation
 *      This function allocates memory for "hit" or "stay". The caller is responsible for freeing this memory.
 * 
 * */
bool decisionmaker_decide(decisionmaker_t* decisionmaker, const char* state);

/**
 * Update average reward for given action in given state - can handle new states
 * Caller provides:
 *      valid decionsmaker, state, action (0 or 1), and reward (-1, 0, or 1)
 * We do:
 *      nothing if decisionmaker is NULL, state is NULL, action is neither 0 nor 1, or reward is neither -1 nor 0 nor 1
 *      otherwise, if the state does not already exist in decisionmaker, create a new state where the four outcome values are all 0
 *      increment the games played for the given state and given action and update the average reward
 * */
void decisionmaker_update(decisionmaker_t* decisionmaker, const char* state, int action, int reward);


/* Delete decisionmaker.
 *
 * Caller provides:
 *   valid decisionmaker pointer,
 * We do:
 *   if decisionmaker==NULL, do nothing.
 *   free all the state strings, call decision_outcomes_delete on each decision_outcomes, and free the decisionmaker itself.
 * Notes:
 *   We free the strings that represent state for each item because 
 *   this module allocated that memory in decisionmaker_insert.
 */
void decisionmaker_delete(decisionmaker_t* decisionmaker);

/**
 * Save the decisionmaker to disk.
 * 
 * Caller provides:
 *      valid decisionmaker pointer
 *      valid decisionmakerFilename
 * We do:
 *      if decisionmaker is null, print error message and do nothing
 *      if decisionmakerFilename is null, print error message and do nothing
 *      if the file cannot be opened for writing, print error message and do nothing
 *      otherwise, write to file in the following format:
 *          one line with the state string
 *          one line with handsWonHit handsWonStay handsPlayedHit handsPlayedStay
 *          repeat for each state
 * Notes:
 *      decisionmakerFilename is a complete filename (path included)
 *      does not alter decisionmaker
*/
void decisionmaker_save(decisionmaker_t* decisionmaker, const char *decisionmakerFilename);

/**
 * Load decisionmaker into memory from disk.
 * 
 * Caller provides:
 *      valid decisionmakerFilename
 * We do:
 *      print error and return NULL if decisionmakerFilename is null, cannot open file for reading, or file is empty
 *      otherwise, read file state by state and build and return decisionmaker
 * Notes:
 *      decisionmakerFilename is a complete filename (path included)
 *      file is not altered
 *      caller is responsible for calling decisionmaker_delete and freeing decisionmakerFilename later
*/
decisionmaker_t* decisionmaker_load(const char *decisionmakerFilename);

/**
 * Create new decision_outcomes and initialize values to corresponding parameter
 * We return pointer to new decision_outcomes
 * Caller is responsible for freeing pointer to decision_outcomes - (will get deleted if it's added to decisionmaker and we call decisionmaker_delete)
 * */
decision_outcomes_t* decision_outcomes_new(float hitAvgReward, float stayAvgReward, int handsPlayedHit, int handsPlayedStay);

#endif //DECISIONMAKER