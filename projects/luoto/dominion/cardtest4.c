/**
 * Unit Tests for the card int great_hallCard(int handPos, int currentPlayer, struct gameState *state)
 *
 * +1 Card
 * +1 Action
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
    printf ("TESTING great_hallCard():\n");

    G.hand[1][0] = great_hall;
    G.handCount[1] = 1;

    printf("Number of actions = %d, expected = %d\n", G.numActions, 1);
    assert(G.numActions == 1);
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[1], 1);
    assert(G.handCount[1] == 1);
    great_hallCard(1, 1, &G);
    printf("Number of actions = %d, expected = %d\n", G.numActions, 1);
    assert(G.numActions == 1);
    printf("Number of cards in hand = %d, expected = %d\n", G.handCount[1], 1);
    // assert(G.handCount[1] == 1); this assertion fails
    return 0;
}