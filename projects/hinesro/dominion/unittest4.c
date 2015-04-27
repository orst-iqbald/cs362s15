/**********************
*    handCard test    *
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define OUTPUT_TEST_RESULTS 1

int main() {
    const char *cards[] = {
        "curse", 
        "estate", 
        "duchy", 
        "province", 
        "copper", 
        "silver", 
        "gold", 
        "adventurer", 
        "council_room",
        "feast", 
        "gardens", 
        "mine", 
        "remodel", 
        "smithy", 
        "village", 
        "baron", 
        "great_hall", 
        "minion", 
        "steward", 
        "tribute",
        "ambassador", 
        "cutpurse", 
        "embargo", 
        "outpost", 
        "salvager", 
        "sea_hag", 
        "treasure_map"
    };
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
    struct gameState *testState = malloc(sizeof(struct gameState));
    int randSeed = 1000;
    int playerCount = 2;
    int curHandCnt = 5;
    int i, j, k;
    initializeGame(playerCount, actions, randSeed, testState);
    printf ("Beginning handCard test...\n");
    for (j = 0; j < numPlayer; j++) {  
        #if (OUTPUT_TEST_RESULTS == 1)
                printf("Testing player %d cards...\n", j);
        #endif
        testState->whoseTurn = j;
        if (j == 0) {
            testState->hand[j][0] = village;
            testState->hand[j][1] = copper;
            testState->hand[j][2] = smithy;
            testState->hand[j][3] = feast;
            testState->hand[j][4] = gardens;
        }
        if (j == 1) {
            testState->hand[j][0] = gold;
            testState->hand[j][1] = adventurer;
            testState->hand[j][2] = council_room;
            testState->hand[j][3] = remodel;
            testState->hand[j][4] = mine;
        }
        for (i = 0; i < curHandCnt; ++i) {
            k = handCard(i, testState);
            #if (OUTPUT_TEST_RESULTS == 1)
                if (testState->hand[j][i] == k) {
                    printf("Card %d in player %d's hand is %s. Test passed.\n", i, j, cards[k]);
                } else {
                    printf("FAILED.\n"); 
                }       
            #endif
        }
    }

    return 0;
}