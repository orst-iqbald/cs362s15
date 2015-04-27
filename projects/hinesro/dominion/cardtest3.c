/***************************
*    Village card test     *
***************************/

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
    int p, handCount;
    int randSeed = 1000;
    int playerCount = 2;
    int maxHandCount = 5;
    int priorActions = 0;
    int k[10] = {
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
    
    printf ("Beginning village test...\n");
    for (p = 0; p < playerCount; p++) {  
        for (handCount = 1; handCount <= maxHandCount; handCount++) {
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Testing player %d with village card and %d cards in hand.\n", p, handCount);
            #endif        
            initializeGame(playerCount, k, randSeed, testState);
            testState->hand[p][0] = village;
            testState->handCount[p] = handCount;
            priorActions = testState->numActions;
            playVillage(p, testState, 0);
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Current hand count is %d. Expected %d\n", testState->handCount[p], handCount);
                printf("Current action count is %d. Expected = %d\n", testState->numActions, priorActions + 2);
            #endif
        }
    }

    return 0;
}