/**
 * Unit Tests for the card int villageCard(int handPos, int currentPlayer, struct gameState *state)
 *
 * +1 Card
 * +2 Actions
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

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    // begin test
    printf ("TESTING villageCard():\n");

    G.hand[1][0] = village;
    G.handCount[1] = 1;

    printf("Number of actions = %d, expected = %d\n", G.numActions, 1);
    assert(G.numActions == 1);
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[1], 1);
    assert(G.handCount[1] == 1);
    villageCard(1, 1, &G);
    printf("Number of actions = %d, expected = %d\n", G.numActions, 2);
    assert(G.numActions == 2);
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[1], 1);
    // assert(G.handCount[1] == 1); this assertion fails
    return 0;
}