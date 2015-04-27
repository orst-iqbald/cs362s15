/**
 * Unit Tests for the function int shuffle(int player, struct gameState *state)
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
    int seed = 700;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    // counter
    int i, j;

    // comparison arrays
    int before[100];
    int after[100];

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    // begin test
    printf ("TESTING shuffle():\n");

    // print current cards in deck
    for(i = 0; i < G.deckCount[1]; i++) {
        printf("%d  ", G.deck[1][i]);
        before[i] = G.deck[1][i];
    }
    printf("\n");

    shuffle(1, &G);

    // print cards after shuffle
    for(i = 0; i < G.deckCount[1]; i++) {
        printf("%d  ", G.deck[1][i]);
        after[i] = G.deck[1][i];
    }
    printf("\n");

    // check if they are 100% the same
    for(i = 0; i < G.deckCount[1]; i++) {
        if(before[i] == after[i]) {
            j++;
        }
    }
    assert(j != G.deckCount[1]);

    return 0;
}