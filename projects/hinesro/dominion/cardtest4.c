/****************************
*    Cutpurse card test     *
****************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define OUTPUT_TEST_RESULTS 1

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));
    int i;
    int randSeed = 1000;
    int playerCount = 4;
    int priorCoins = 0;
    int k[10] = {
        adventurer, 
        council_room, 
        cutpurse, 
        gardens, 
        mine, 
        remodel, 
        smithy, 
        village, 
        baron, 
        great_hall
    };
    
    printf ("Beginning cutpurse test...\n");  
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Testing that p1 has cutpurse card and all players except last have 1 copper.\n");
    #endif
    initializeGame(playerCount, k, randSeed, testState);
    for (i = 0; i < playerCount; ++i) {
        testState->handCount[i] = 5;
    }
    testState->hand[0][0] = cutpurse;
    testState->hand[1][0] = copper;
    testState->hand[2][0] = copper;
    priorCoins = testState->coins;
    playCutpurse(0, testState, 0);
    #if (OUTPUT_TEST_RESULTS == 1)
        printf("Coin count = %d, expected = %d\n", testState->coins, priorCoins + 2);
        for (i = 0; i < playerCount; ++i) {
            printf("Hand count for player %d after cutpurse is played.\n", i);
            if (i == 3) {
                printf("No copper found. Expected: %d, Actual: %d\n", 5, testState->handCount[i]);
            } else {
                printf("Copper found. Expected: %d, Actual: %d\n", 4, testState->handCount[i]);
            }
        }
    #endif

    return 0;
}