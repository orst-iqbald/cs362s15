/********************************
*        Test for smithy        *
********************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
    struct gameState testState;
    int randSeed = 1024;
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

    printf ("Begin smithy card test:\n");
    initializeGame(2, cards, randSeed, &testState);
    testState.hand[0][0] = smithy;
    int curHandCount = testState.handCount[0];
    smithyCard(0,&testState,0);

    if(testState.handCount[0] == curHandCount + 2) {
        printf("Smithy card hand count test passed.\n");
    } else {
        printf("Adventure card hand count test FAILED.\n");
    }

    return 0;
}