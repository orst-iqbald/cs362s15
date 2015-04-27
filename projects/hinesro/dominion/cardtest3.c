/********************************
*       Test for village        *
********************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
    struct gameState *testState = malloc(sizeof(struct gameState));
    int randSeed = 1024;
    int playerCount = 2;
    int curHand = 0;
    int actionCount = 0;
    int cards[10] = {
        estate, 
        duchy, 
        province, 
        copper, 
        silver, 
        gold, 
        adventurer, 
        smithy, 
        gardens, 
        feast
    };

    printf ("Begin village card test:\n");
    initializeGame(playerCount, cards, randSeed, testState);
    testState->curHand[0][0] =village;
    curHand = testState->handCount[0];
    actionCount = testState->numActions;
    actionVillage(0,0, testState);

    if (testState->numActions == actionCount + 1) {
        printf("Village card action count test passed.\n");
    } else {
        printf("Village card action count test FAILED.\n");
    }

    if(testState->handCount[0] == curHand) {
        printf("Village card hand count test passed.\n");
    } else {
        printf("Village card hand count test FAILED.\n");
    }

    return 0;
}