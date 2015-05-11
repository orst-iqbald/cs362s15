#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
    int numTests = 100, randSeed = 999, i;
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

    for(i = 0; i < numTests; i++) {
        struct gameState *testState = malloc(sizeof(struct gameState));
        struct gameState *lastState = malloc(sizeof(struct gameState));
        int errNo = 0, treasureBefore = 0, treasureAfter = 0, pos, j;
        randSeed = floor((Random() * 999) + 1);
        int playerCount = floor((Random() * 3) + 2);
        initializeGame(playerCount, cards, randSeed, testState);

        testState->whoseTurn = floor(Random() * playerCount);
        testState->handCount[testState->whoseTurn] = floor(Random() * (MAX_HAND / 3));
        testState->deckCount[testState->whoseTurn] = floor(Random() * (MAX_DECK / 3));
        testState->discardCount[testState->whoseTurn] = floor(Random() * (MAX_DECK / 3));
        testState->playedCardCount = floor(Random() * 5);

        for(j = 0; j < testState->handCount[testState->whoseTurn]; j++) {
            testState->hand[testState->whoseTurn][j] = floor(Random() * 17);
        }

        for(j = 0; j < testState->deckCount[testState->whoseTurn]; j++) {
            testState->deck[testState->whoseTurn][j] = floor(Random() * 17);
        }

        for(j = 0; j < testState->discardCount[testState->whoseTurn]; j++) {
            testState->discard[testState->whoseTurn][j] = floor(Random() * 17);
        }

        pos = floor(Random() * testState->handCount[testState->whoseTurn]);
        testState->hand[testState->whoseTurn][pos] = adventurer;
        memcpy(lastState, testState, sizeof(struct gameState));
        callAdventurer(testState, pos);

        for(j = 0; j < lastState->handCount[lastState->whoseTurn]; j++) {
            if(lastState->hand[lastState->whoseTurn][j] == gold || lastState->hand[lastState->whoseTurn][j] == silver || lastState->hand[lastState->whoseTurn][j] == copper) {
                treasureBefore++;
            }
        }

        for(j = 0; j < testState->handCount[testState->whoseTurn]; j++) {
            if(testState->hand[testState->whoseTurn][j] == copper || testState->hand[testState->whoseTurn][j] == silver || testState->hand[testState->whoseTurn][j] == gold) {
                treasureAfter++;
            }
        }

        if((lastState->deckCount[lastState->whoseTurn] + lastState->discardCount[lastState->whoseTurn]-2) != (testState->deckCount[testState->whoseTurn] + testState->discardCount[testState->whoseTurn])) {
            printf("Test failed totalling cards in deck and discard pile.\n");
            errNo = 1;
        }

        if((lastState->playedCardCount+1) != testState->playedCardCount) {
            printf("Test failed incrementing total number of cards played.\n");
            errNo = 2;
        }

        if((treasureBefore+2) != treasureAfter) {
            printf("Test failed totalling player hand treasure cards.\n");
            errNo = 3;
        }

        if(lastState->handCount[lastState->whoseTurn]+2 != testState->handCount[testState->whoseTurn]) {
            printf("Test failed incrementing total handcount.\n");
            errNo = 4;
        }

        if(errNo == 0) {
            printf("All tests pass.\n");
        }
    }

    return 0;
}