/*****************************
*    Adventurer card test    *
*****************************/

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
    int i, startCoins, newCoins, p, handCount;
    int randSeed = 1000;
    int playerCount = 2;
    int maxHand = 5;
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

    printf ("Beginning adventurer test...\n");
    for (p = 0; p < playerCount; p++) {
        for (handCount = 1; handCount <= maxHand; handCount++) {
            startCoins = 0;
            newCoins = 0;
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Testing player %d with adventure card and %d cards in hand...\n", p, handCount);
            #endif        
            initializeGame(playerCount, cards, randSeed, testState);
            testState->handCount[p] = handCount;
            testState->hand[p][0] = adventurer;
            for (i = 0; i < testState->handCount[p]; ++i) {
                if ( testState->hand[p][i] == gold || testState->hand[p][i] == silver || testState->hand[p][i] == copper ) {
                    startCoins++;
                }
            }
            playAdventurer(p, testState);
            for (i = 0; i < testState->handCount[p]; ++i) {
                if ( testState->hand[p][i] == gold || testState->hand[p][i] == silver || testState->hand[p][i] == copper ) {
                    newCoins++;
                }
            }
            #if (OUTPUT_TEST_RESULTS == 1)
                printf("Testing player %d for treasure cards, %d in hand and at least 2 in deck...", p, startCoins);
                if (newCoins == startCoins + 2) {
                    printf("Passed test. New count is %d. Expected = %d\n", newCoins, startCoins + 2);
                } else {
                    printf("FAILED test. New count is %d. Expected = %d\n", newCoins, startCoins + 2);
                }
            #endif
        }
    }

    return 0;
}