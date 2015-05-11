/**
 * Random Tests for the card int adventurerCard(int currentPlayer, struct gameState *state)
 *
 * Reveal cards from deck until 2 treasure cards are drawn
 * Treasure cards are placed in player's hand, all other cards are discarded
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

int checkAdventurerCard(int p, struct gameState *G);

int main(void) {
    srand(time(NULL));
    // game parameters
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};
    int seed, i, r, p, n;
    int testIterations = 15;

    // begin test
    printf ("TESTING adventurerCard():\n");
    printf ("RANDOM TESTS.\n");

    for (i = 0; i < testIterations; i++) {
        seed = floor(rand() * 600 + 100);
        r = initializeGame(2, k, seed, &G);
        p = floor(Random() * 2); // player
        G.deckCount[p] = floor(Random() * MAX_DECK);
        // fill deck with random cards
        for(n = 0; n < G.deckCount[p]; n++) {
            G.deck[p][n] = floor(rand() * 26 + 1);
        }
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_HAND);
        checkAdventurerCard(p, &G);
    }

    printf("TEST COMPLETED\n");

    return 0;
}

int checkAdventurerCard(int p, struct gameState *G) {
    struct gameState G2;
    memcpy (&G2, G, sizeof(struct gameState));

    // gather intial state
    int handCount = G2.handCount[p];
    printf("Initial cards in hand: %d\n", handCount);

    // play adventurer card
    adventurerCard(p, &G2);

    // compare to expected results
    printf("Current cards in hand = %d, expected cards in hand = %d\n", G2.handCount[p], handCount + 2);

    return 0;
}