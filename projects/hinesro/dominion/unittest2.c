/************************
*    isGameOver test    *
************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define OUTPUT_TEST_RESULTS 1

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));
    int i, j;
    int randSeed = 1000;
    int playerCount = 2;
    int actions[10] = {
        adventurer, 
        council_room, 
        feast, 
        gardens, 
        mine, 
        remodel, 
        smithy, 
        village, 
        baron, 
        great_hall
    };
    initializeGame(playerCount, actions, randSeed, testState);
    printf ("Beggining isGameOver test...\n");
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Testing scenario: Supplies are still available...\n");
    #endif
    j = isGameOver(testState);
    #if (OUTPUT_TEST_RESULTS == 1)
        if(j == 0) {
            printf("Test Passed!\n");
        } else {
            printf("Test Failed!\n");
        }
    #endif
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Testing scenario: All supplies are gone...\n");
    #endif
    initializeGame(playerCount, actions, randSeed, testState);
    for (i = 0; i < 3; ++i) {
        testState->supplyCount[i] = 0;
    }
    j = isGameOver(testState);
    #if (OUTPUT_TEST_RESULTS == 1)
        if(j == 1) {
            printf("Pass\n");
        } else {
            printf("FAIL\n");
        }
    #endif
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Testing scenario: Province cards are empty...\n");
    #endif
    initializeGame(playerCount, actions, randSeed, testState);
    testState->supplyCount[province] = 0;
    j = isGameOver(testState);
    #if (OUTPUT_TEST_RESULTS == 1)
        if(j == 1) {
            printf("Pass\n");
        } else {
            printf("FAIL\n");
        }
    #endif
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Testing scenario: Province cards available...\n");
    #endif
    initializeGame(playerCount, actions, randSeed, testState);
    testState->supplyCount[province] = 1;
    j = isGameOver(testState);
    #if (OUTPUT_TEST_RESULTS == 1)
        if(j == 0) {
            printf("Pass\n");
        }
        else {
            printf("FAIL\n");
        }
    #endif
    return 0;
}