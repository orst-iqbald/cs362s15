#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include "rngs.h"

int main() {
    int i, randSeed = 999, numTests = 100;;
    SelectStream(1);
    PutSeed((long)randSeed);
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

    for(i = 0; i < numTests; ++i) {
        int j, position, errNo = 0;

        struct gameState *testState = malloc(sizeof(struct gameState));
        struct gameState *lastState = malloc(sizeof(struct gameState));
        randSeed = floor((Random() * 999) + 1);

        int playerCount = floor((Random() * 3) + 2);
        initializeGame(playerCount, cards, randSeed, testState);

        testState->whoseTurn = floor(Random() * playerCount);
        testState->handCount[testState->whoseTurn] = floor(Random() * (MAX_HAND / 3));
        testState->deckCount[testState->whoseTurn] = floor(Random() * (MAX_DECK / 3));
        testState->discardCount[testState->whoseTurn] = floor(Random() * (MAX_DECK / 3));
        testState->playedCardCount = floor(Random() * 5);
        testState->numBuys = floor((Random() * 4) + 1);


        for(j = 0; j < testState->handCount[testState->whoseTurn]; j++) {
            testState->hand[testState->whoseTurn][j] = floor(Random() * 17);
        }

        for(j = 0; j < testState->deckCount[testState->whoseTurn]; j++) {
            testState->deck[testState->whoseTurn][j] = floor(Random() * 17);
        }

        for(j = 0; j < testState->discardCount[testState->whoseTurn]; j++) {
            testState->discard[testState->whoseTurn][j] = floor(Random() * 17);
        }

        position = floor(Random() * testState->handCount[testState->whoseTurn]);
        testState->hand[testState->whoseTurn][position] = council_room;
        memcpy(lastState, testState, sizeof(struct gameState));
        callCouncilRoom(testState, position);

        for(j = 0; j < testState->numPlayers; j++) {
            if(j == testState->whoseTurn) {
                if(testState->handCount[j] != (lastState->handCount[j] + 3)) {
                    printf("Test failed incrementing current player's hand.\n");
                    errNo = 1;
                }
            } else if(testState->handCount[j] != (lastState->handCount[j] + 1)) {
                printf("Test failed incrememnting other player hand.\n");
                errNo = 2;
            }
        }

        if(testState->numBuys != (lastState->numBuys + 1)) {
            printf("Test failed incrementing buys.\n");
            errNo = 3;
        }

        if(errNo == 0) {
          printf("All tests pass.\n");
        }
    }

    return 0;
}