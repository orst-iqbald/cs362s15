/********************************
*  	   Test for great hall	    *
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
    int currentHand = 0;
    int actions = 0;
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

    printf("Begin great hall card test:\n");
    initializeGame(playerCount, cards, randSeed, testState);
    testState->currentHand[0][0] = great_hall;
    currentHand = testState->handCount[0];
    actions = testState->numActions;
    actionGreat_hall();

    if (testState->handCount[0] == currentHand) {
    	printf("Great hall card hand count test passed.\n");
    } else {
    	printf("Great hall card hand count test FAILED.\n");
    }

    if(testState->numActions == actions + 1 ) {
    	printf("Great hall card action count test passed.\n");
    } else {
    	printf("Great hall card action count test FAILED.\n");
    }

    return 0;
}