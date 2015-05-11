/**
 * Random Tests for the card int smithyCard(int handPos, int currentPlayer, struct gameState *state)
 *
 * + 3 Cards
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

int checkSmithyCard(int p, struct gameState *G, int j);

int main(void) {
    srand(time(NULL));
    // game parameters
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};
    int seed, i, j, r, p;
    int testIterations = 15;

    // begin test
    printf ("TESTING smithyCard():\n");
    printf ("RANDOM TESTS.\n");

    for (i = 0; i < testIterations; i++) {
        seed = floor(rand() * 600 + 100);
        r = initializeGame(2, k, seed, &G);
        p = floor(Random() * 2); // player
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);
        j = floor(Random() * G.handCount[p]);
        G.hand[p][j] = smithy; 
        checkSmithyCard(p, &G, j);
    }

    printf("TEST COMPLETED\n");

    return 0;
}

int checkSmithyCard(int p, struct gameState *G, int j) {
    struct gameState G2;
    memcpy (&G2, G, sizeof(struct gameState));

    // gather intial state
    //int deckCount = G.deckCount[p];
    //int discardCount = G.discardCount[p];
    int handCount = G2.handCount[p];
    int playedCardCount = G2.playedCardCount;

    // play smithy card
    smithyCard(j, p, &G2);

    // compare to expected results
    printf("Cards in hand = %d, expected cards in hand = %d\n", G2.handCount[p], handCount + 2);
    printf("Cards in play = %d, expected cards in play = %d\n", G2.playedCardCount, playedCardCount + 1);
    assert(G.playedCardCount == playedCardCount + 1);

    return 0;
}