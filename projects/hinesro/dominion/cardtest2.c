/********************************
*      Test for adventurer      *
********************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main() {
    struct gameState testState;
    int handCount = testState.handCount[0];
    int randSeed = 1024;
    int test = 0;
    int treasure = 0;
    int i = 0;
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

    initializeGame(2, cards, randSeed, &testState);
    printf ("Begin adventure card test:\n");  
    testState.hand[0][0] = adventurer;

    for (i = 0; i < testState.handCount[0]; i++) {
        if (testState.hand[0][i] == copper || testState.hand[0][i] == silver || testState.hand[0][i] == gold) {
            treasure++;
        }
    }

    adventurerCard(0, 0, &testState);

    for (i = 0; i < testState.handCount[0]; i++) {
        if (testState.hand[0][i] == copper || testState.hand[0][i] == silver || testState.hand[0][i] == gold) {
            test++;
        }
    }

    if (test == treasure + 2) {
        printf("Adventure card treasure test passed.\n");
    } else {
        printf("Adventure card treasure test FAILED.\n");
    }

    if(testState.handCount[0] == handCount + 1 ) {
        printf("Adventure card hand count test passed.\n");
    } else {
        printf("Adventure card hand count test FAILED.\n");
    }

    return 0; 
}