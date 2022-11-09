/* 
 * decisionmaker.c - implementation of decisionmaker.h
 *
 * See decisionmaker.h for more information
 * 
 * compile for testing: mygcc -o decisionmaker_test decisionmaker.c ../libcs50/libcs50-given.a -I../libcs50 -DUNITTEST
 * test: ./decisionmaker_test
 * test with valgrind: myvalgrind ./decisionmaker_test
 * 
 * Asher Vogel
 * CS 50, Fall 2022
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <hashtable.h>
#include <file.h>
#include "decisionmaker.h"

const int HASHTABLE_SIZE = 52*51*50*49;

typedef struct hashtable decisionmaker_t;

typedef struct decision_outcomes {
    float hitAvgReward;
    float stayAvgReward;
    int handsPlayedHit;
    int handsPlayedStay;
} decision_outcomes_t;

decisionmaker_t* decisionmaker_new() {
    decisionmaker_t* decisionmaker = hashtable_new(HASHTABLE_SIZE);
    return decisionmaker;
}

bool decisionmaker_insert(decisionmaker_t* decisionmaker, const char* state, decision_outcomes_t* decision_outcomes) {
    return hashtable_insert(decisionmaker, state, decision_outcomes);
}

decision_outcomes_t* decisionmaker_find(decisionmaker_t* decisionmaker, const char* state) {
    return hashtable_find(decisionmaker, state);
}

bool decisionmaker_decide(decisionmaker_t* decisionmaker, const char* state) {
    // compare values and return 0 or 1
    decision_outcomes_t* outcomes = decisionmaker_find(decisionmaker, state);
    if (outcomes != NULL) {
        if (outcomes->hitAvgReward >= outcomes->stayAvgReward) {
        return true;
        }
    }
    return false;
}

void decisionmaker_update(decisionmaker_t* decisionmaker, const char* state, int action, int reward) {
    // safety checks
    if (decisionmaker == NULL) {
        fprintf(stderr, "Cannot update average reward for NULL decisionmaker\n");
        return;
    }
    if (state == NULL) {
        fprintf(stderr, "Cannot update average reward for NULL state");
        return;
    }
    if (action != 0 && action != 1) {
        fprintf(stderr, "Invalid action (must be 0 or 1)\n");
        return;
    }
    if (reward != -1 && reward != 0 && reward != 1) {
        fprintf(stderr, "Invalid reward (must be -1, 0, or 1)\n");
        return;
    }
    // handle new state
    if (decisionmaker_find(decisionmaker, state) == NULL) {
        decision_outcomes_t* new_outcomes = decision_outcomes_new(0, 0, 0, 0);
        decisionmaker_insert(decisionmaker, state, new_outcomes);
    }
    // update reward and games played
    decision_outcomes_t* outcomes = decisionmaker_find(decisionmaker, state);
    if (action == 0) { // stay
        outcomes->handsPlayedStay++;
        outcomes->stayAvgReward += (1 / (float) outcomes->handsPlayedStay)*((float) reward - outcomes->stayAvgReward);
    }
    else { // hit
        outcomes->handsPlayedHit++;
        outcomes->hitAvgReward += (1 / (float) outcomes->handsPlayedHit)*((float) reward - outcomes->hitAvgReward);
    }
}

/** Helper function for decisionmaker_delete*/
static void decision_outcomes_delete(void* item) {
    if (item != NULL) {
        free(item);
    }
}

void decisionmaker_delete(decisionmaker_t* decisionmaker) {
    hashtable_delete(decisionmaker, decision_outcomes_delete);
}

/** Helper function for decisionmaker_save*/
static void print_decisionmaker_item(void *arg, const char *key, void* item) {
    // printf("printing data for key: %s\n", key);
    // fflush(stdout);
    FILE* fp = (FILE*) arg;
    decision_outcomes_t* outcomes = (decision_outcomes_t*) item;
    fprintf(fp, "%s\n", key);
    fprintf(fp, "%f %f %d %d\n", outcomes->hitAvgReward, outcomes->stayAvgReward, outcomes->handsPlayedHit, outcomes->handsPlayedStay);
}

void decisionmaker_save(decisionmaker_t* decisionmaker, const char *decisionmakerFilename) {
    // safety checks
    if (decisionmaker == NULL) {
        fprintf(stderr, "Cannot save NULL decisionmaker to disk\n");
        return;
    }
    if (decisionmakerFilename == NULL) {
        fprintf(stderr, "Cannot save decisionmaker with NULL filename");
        return;
    }
    // attempt to open file for writing
    FILE* fp = fopen(decisionmakerFilename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s for writing\n", decisionmakerFilename);
        return;
    }
    // write to disk
    hashtable_iterate(decisionmaker, fp, print_decisionmaker_item);
    fclose(fp);
}

decisionmaker_t* decisionmaker_load(const char *decisionmakerFilename) {
    // safety check
    if (decisionmakerFilename == NULL) {
        fprintf(stderr, "Cannot load decisionmaker with NULL filename\n");
        return NULL;
    }
    // attempt to open file for reading
    FILE* fp = fopen(decisionmakerFilename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open %s for reading\n", decisionmakerFilename);
        return NULL;
    }
    // declare variables
    decisionmaker_t* decisionmaker = decisionmaker_new();
    char* state;
    char* outcomesStr;
    float hitAvgReward, stayAvgReward;
    int handsPlayedHit, handsPlayedStay;
    // read lines, two at a time, and insert data into decisionmaker
    while ((state = file_readLine(fp)) != NULL) {
        outcomesStr = file_readLine(fp);
        if (sscanf(outcomesStr, "%f %f %d %d", &hitAvgReward, &stayAvgReward, &handsPlayedHit, &handsPlayedStay) != 4) {
            fprintf(stderr, "Error reading outcome values from %s (program continuing)", decisionmakerFilename);
        }
        decision_outcomes_t* outcomes = decision_outcomes_new(hitAvgReward, stayAvgReward, handsPlayedHit, handsPlayedStay);
        decisionmaker_insert(decisionmaker, state, outcomes);
        free(state);
        free(outcomesStr);
    }
    fclose(fp);
    return decisionmaker;
}


decision_outcomes_t* decision_outcomes_new(float hitAvgReward, float stayAvgReward, int handsPlayedHit, int handsPlayedStay) {
    decision_outcomes_t* outcomes = malloc(sizeof(decision_outcomes_t));
    outcomes->hitAvgReward = hitAvgReward;
    outcomes->stayAvgReward = stayAvgReward;
    outcomes->handsPlayedHit = handsPlayedHit;
    outcomes->handsPlayedStay = handsPlayedStay;
    return outcomes;
}







#ifdef UNITTEST
#include <unittest.h>

/**
 * Caller provides: two float
 * We return:
 *      true if the floats are within 0.00001 of eachother
 *      false otherwise
 * */
static bool compareFloats(float float1, float float2) {
    if (float1 == float2) {
        return true;
    }
    else if (float1 > float2) {
        if (float1 - float2 < 0.00001) {
            return true;
        }
    }
    else {
        if (float2 - float1 < 0.00001) {
            return true;
        }
    }
    return false;
}

int test_decisionmaker_insert(decisionmaker_t* decisionmaker) {
    START_TEST_CASE("decisionmaker_insert");

    int success = -1;

    decision_outcomes_t* outcomes1 = decision_outcomes_new((float) 0, (float) 0, 0, 0);
    success = decisionmaker_insert(NULL, "10 5 6", outcomes1);
    EXPECT(success == 0);

    success = decisionmaker_insert(decisionmaker, NULL, outcomes1);
    EXPECT(success == 0);

    success = decisionmaker_insert(decisionmaker, "10 5 6", NULL);
    EXPECT(success == 0);

    success = decisionmaker_insert(decisionmaker, "10 5 6", outcomes1);
    EXPECT(success == 1);

    decision_outcomes_t* outcomes2 = decision_outcomes_new(0.4, 0.4, 11, 13);
    success = decisionmaker_insert(decisionmaker, "8 4 10", outcomes2);
    EXPECT(success == 1);

    decision_outcomes_t* outcomes3 = decision_outcomes_new(0.2, 0.9, 14, 10);
    success = decisionmaker_insert(decisionmaker, "9 A 5 5", outcomes3);
    EXPECT(success == 1);

    success = decisionmaker_insert(decisionmaker, "9 A 5 5", outcomes3);
    EXPECT(success == 0);

    END_TEST_CASE;
    return TEST_RESULT;
}

int test_decisionmaker_find(decisionmaker_t* decisionmaker) {
    START_TEST_CASE("decisionmaker_find");

    EXPECT(decisionmaker_find(decisionmaker, "10") == NULL);

    decision_outcomes_t* outcomes1 = decisionmaker_find(decisionmaker, "10 5 6");
    decision_outcomes_t* outcomes2 = decisionmaker_find(decisionmaker, "8 4 10");
    decision_outcomes_t* outcomes3 = decisionmaker_find(decisionmaker, "9 A 5 5");

    EXPECT(compareFloats(outcomes1->hitAvgReward, (float) 0));
    EXPECT(compareFloats(outcomes1->stayAvgReward, (float) 0));
    EXPECT(outcomes1->handsPlayedHit == 0);
    EXPECT(outcomes1->handsPlayedStay == 0);
    EXPECT(compareFloats(outcomes2->hitAvgReward,0.4));
    EXPECT(compareFloats(outcomes2->stayAvgReward, 0.4));
    EXPECT(outcomes2->handsPlayedHit == 11);
    EXPECT(outcomes2->handsPlayedStay == 13);
    EXPECT(compareFloats(outcomes3->hitAvgReward,0.2));
    EXPECT(compareFloats(outcomes3->stayAvgReward, 0.9));
    EXPECT(outcomes3->handsPlayedHit == 14);
    EXPECT(outcomes3->handsPlayedStay == 10);

    END_TEST_CASE;
    return TEST_RESULT;
}


int test_decisionmaker_update(decisionmaker_t* decisionmaker) {
    START_TEST_CASE("decisionmaker_update");

    for (int i=1; i<=12; i++) {
        decisionmaker_update(decisionmaker, "10 5 6", 0, -1); // stay and lose
        if (i % 2 == 0) {
            decisionmaker_update(decisionmaker, "10 5 6", 1, 1); // hit and win
        }
        if (i % 3 == 0) {
            decisionmaker_update(decisionmaker, "10 5 6", 1, -1); // hit and lose
        }
        if (i % 4 == 0) {
            decisionmaker_update(decisionmaker, "10 5 6", 0, 1); // stay and win
        }
        if (i % 6 == 0) {
            decisionmaker_update(decisionmaker, "10 5 6", 1, 0); // hit and push
        }
        if (i % 12 == 0) {
            decisionmaker_update(decisionmaker, "10 5 6", 0, 0); // stay and push
        }
    }
    decision_outcomes_t* outcomes1 = decisionmaker_find(decisionmaker, "10 5 6");

    EXPECT(compareFloats(outcomes1->hitAvgReward, (float) 2 / (float) 12));
    EXPECT(compareFloats(outcomes1->stayAvgReward, (float) -9 / (float) 16));
    EXPECT(outcomes1->handsPlayedHit == 12);
    EXPECT(outcomes1->handsPlayedStay == 16);

    END_TEST_CASE;
    return TEST_RESULT;
}

int test_decisionmaker_decide(decisionmaker_t* decisionmaker) {
    START_TEST_CASE("decisionmaker_decide");

    EXPECT(decisionmaker_decide(NULL, "10 5 6") == 0);
    EXPECT(decisionmaker_decide(decisionmaker, NULL) == 0);
    EXPECT(decisionmaker_decide(decisionmaker, "10 5 6") == 1);
    EXPECT(decisionmaker_decide(decisionmaker, "8 4 10") == 1);
    EXPECT(decisionmaker_decide(decisionmaker, "9 A 5 5") == 0);

    END_TEST_CASE;
    return TEST_RESULT;
}

void test_decisionmaker_save(decisionmaker_t* decisionmaker, const char* decisionmakerFilename) {
    printf("test decisionmaker_save\n");
    decisionmaker_save(decisionmaker, decisionmakerFilename);
}

decisionmaker_t* test_decisionmaker_load(const char* decisionmakerFilename) {
    printf("test decisionmaker_load\n");
    return decisionmaker_load(decisionmakerFilename);
}

int main(const int argc, char* argv[]) {
    int failed = 0;

    decisionmaker_t* decisionmaker = decisionmaker_new();
    char* decisionmakerFilename = malloc(sizeof(char)*24);
    strcpy(decisionmakerFilename, "decisionmaker_test_data");

    failed += test_decisionmaker_insert(decisionmaker);

    test_decisionmaker_save(decisionmaker, decisionmakerFilename);
    decisionmaker_delete(decisionmaker);
    decisionmaker = test_decisionmaker_load(decisionmakerFilename);

    failed += test_decisionmaker_find(decisionmaker);
    failed += test_decisionmaker_update(decisionmaker);

    test_decisionmaker_save(decisionmaker, decisionmakerFilename);
    decisionmaker_delete(decisionmaker);
    decisionmaker = test_decisionmaker_load(decisionmakerFilename);

    failed += test_decisionmaker_decide(decisionmaker);

    test_decisionmaker_save(decisionmaker, decisionmakerFilename);
    
    free(decisionmakerFilename);
    decisionmaker_delete(decisionmaker);

    if (failed) {
        printf("FAIL %d test cases\n", failed);
        return failed;
    }
    else {
        printf("PASS all test cases\n");
        return 0;
    }
}

#endif // UNITTEST