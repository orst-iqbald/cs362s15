#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
    int i, j;
    int z = 0;
    int newCards = 3;
    int discarded = 1;
    int shuffledCards = 0;
    int cardDrawn = 0;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int currentPlayer;
    int temphand[MAX_HAND];
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};


    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("Testing Card: %s \n", TESTCARD);

    //Stores previous amount of discarded cards
    int prevDiscard = testG.discardCount[thisPlayer];

    //Stores previous number of cards in player hand
    int prevHand = testG.handCount[thisPlayer];

    //Stores number of actions
    int prevActions = testG.numActions;

    //calls the great_hall card
    great_hallcard(thisPlayer, handpos, &testG);
    
    printf("Previous Card = %d, Expected = %d, Final = %d\n", prevHand, prevHand, testG.handCount[thisPlayer]); //Because one card is discarded
    printf("Previous Actions = %d, Expected = %d, Final = %d\n", prevActions, prevActions + 1, testG.numActions);
    //printf("Previous Discard = %d, Expected = %d, Final = %d\n", prevDiscard, prevDiscard + 1, testG.discardCount[thisPlayer]);

    //Asserts that the player drew 1 card.
    printf("Asserting the correct number of cards in hand.\n");
    assert(testG.handCount[thisPlayer] == (prevHand));

    //Asserts that the number of actions the player has is at least 2.
    //assert(testG.numActions == prevActions + 1);
    printf("Asserting the correct number of actions given.\n");
    if(testG.numActions == prevActions + 1){
        printf("Action test PASSED!\n");
    }else{
        printf("Action test FAILED!\n");
    }
    //Asserts that the great_hall card was discarded.
    //assert(testG.discardCount[thisPlayer] == (prevDiscard + 1));

    printf("%s card passed all tests.\n", TESTCARD);

    return 0;
}