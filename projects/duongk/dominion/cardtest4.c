#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "embargo"

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
    int choice1 = 0;
    int drawntreasure = 0;
    int temphand[MAX_HAND];
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};


    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    //copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("Testing Card: %s \n", TESTCARD);

    //previous number of coins stored
    int prevCoins = testG.coins;

    //pevious number of embargo tokens placed on piles stored
    int prevEmbargoToken = testG.embargoTokens[choice1];

    //previous amount of discarded cards stored
    int prevDiscard = testG.discardCount[thisPlayer];

    //calls the embargo card function and asserts 2 treasure cards were drawn
    embargo_card(thisPlayer, handpos, choice1,  &testG);
    printf("Previous Coins = %d, Expected = %d, Final = %d\n", prevCoins, prevCoins + 2, testG.coins);
    //printf("Previous Discard = %d, Expected = %d, Final = %d\n", prevDiscard, prevDiscard + 1, testG.discardCount[thisPlayer]);   
    
    //Asserts 2 treasure cards were drawn.
    printf("Asserting correct number of treasures drawn.\n");
    assert(testG.coins == prevCoins + 2);
    //Asserts embargo token was placed
    printf("Asserting embargo token placed correctly.\n");
    assert(testG.embargoTokens[choice1] == prevEmbargoToken + 1);
    //Asserts embargo card was discarded from hand
   // assert(testG.discardCount[thisPlayer] == (prevDiscard + 1));
    //assert(testG.handCount[thisPlayer] = prevHand - 1);

    printf("%s card passed all tests.\n", TESTCARD);

    return 0;
}