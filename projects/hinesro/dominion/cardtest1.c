/*************************
*    Smithy card test    *
*************************/

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
    int randomSeed = 1000;
    int playerCount = 2;
    int p, handCount;
    int maxHandCount = 5;
    int cards[10] = {
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

    printf ("Beginning smithy test...\n");
    for (p = 0; p < playerCount; p++) {  
        for (handCount = 1; handCount <= maxHandCount; handCount++) {
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Testing player %d with smithy card and %d cards in hand.\n", p, handCount);
            #endif        
            initializeGame(playerCount, cards, randomSeed, testState);
            testState->hand[p][0] = smithy;
            testState->handCount[p] = handCount;
            playSmithy(p, testState, 0);
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Current hand count: %d.\nExpected = %d\n", testState->handCount[p], handCount + 2);
            #endif
        }
    }

    return 0;
}