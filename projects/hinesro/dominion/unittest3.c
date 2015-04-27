/****************************
*    initializeGame test    *
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
    int randSeed = 1000;
    int playerCount = 4;
    int i, j;
    int actions[10] = {
        adventurer, 
        council_room, 
        feast, gardens, 
        mine, 
        remodel, 
        smithy, 
        village, 
        baron, 
        great_hall
    };
    printf ("Beginning initializeGame test...\n");
    for (i = 0; i <= playerCount + 1; i++) {  
        #if (OUTPUT_TEST_RESULTS == 1)
                printf("Test case: Start game with %d players.\n", i);
        #endif        
            j = initializeGame(i, actions, randSeed, testState);           
        #if (OUTPUT_TEST_RESULTS == 1)
            if (j == -1) {
                printf("Test case: Too many players--%d.\n", i);
            }
            else {
                printf("Player count is %d. Expected %d.\n", testState->numPlayers, i);
                if (testState->numPlayers == 2) {
                    printf(" %d player game with %d curses. Expected %d.\n", 
                    testState->numPlayers, testState->supplyCount[curse], 10);
                }
                if (testState->numPlayers == 3) {
                    printf("%d player game with %d curses. Expected %d.\n", 
                    testState->numPlayers, testState->supplyCount[curse], 20);
                }
                if (testState->numPlayers == 4) {
                    printf("%d player game with %d curses. Expected %d.\n", 
                    testState->numPlayers, testState->supplyCount[curse], 30);
                }
                printf("%d player game with %d copper. Expected %d.\n", 
                testState->numPlayers, testState->supplyCount[copper], 60 - (7 * i));
                printf("%d player game with %d silver. Expected %d.\n", 
                testState->numPlayers, testState->supplyCount[silver], 40);
                printf("%d player game with %d gold. Expected %d.\n", 
                testState->numPlayers, testState->supplyCount[gold], 30);
                printf("Beginning test for victory card counts...");
                if(testState->numPlayers == 2 && testState->supplyCount[province] == 8) {
                    printf("%d player game with %d provinces. Expected %d. Test passed.\n", i, testState->supplyCount[province], 8);
                }
                if((testState->numPlayers == 3 || testState->numPlayers == 4) && testState->supplyCount[province] == 12) {
                    printf("%d player game with %d provinces. Expected %d. Test passed.\n", i, testState->supplyCount[province], 12);
                }
            }   
        #endif
    }
    return 0;
}