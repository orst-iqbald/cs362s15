/**
 * Unit Tests for the function int buyCard(int supplyPos, struct gameState *state)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(void) {
    // game parameters
    int seed = 500;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    // test parameters

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    G.whoseTurn = 1; // set turn to player 1
    G.handCount[1] = 1;
    G.hand[1][0] = 1;
    G.coins = 10;
    G.numBuys = 1;

    // begin test
    printf ("TESTING buyCard():\n");

    printf("Coins before purchase: %d\n", G.coins);
    printf("Card at max discard position: %d\n", G.discard[1][G.discardCount[1] - 1]);
    buyCard(2, &G);
    printf("Coints after purchase: %d\n", G.coins);
    printf("Card at max discard position: %d\n", G.discard[1][G.discardCount[1] - 1]);
    printf("buyCard() = %d, expected = %d\n", buyCard(3, &G), -1);

    return 0;
}

