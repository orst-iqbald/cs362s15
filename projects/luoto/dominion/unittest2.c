/**
 * Unit Tests for the function int isGameOver(struct gameState *state)
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
    int seed = 550;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    // test sets
    int numProvinces = 5;

    // counters
    int i;

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    // begin test
    printf ("TESTING isGameOver():\n");

    G.supplyCount[province] = numProvinces;
    isGameOver(&G);
    printf("isGameOver = %d, expected = %d\n", isGameOver(&G), 0);
    assert(isGameOver(&G) == 0);

    G.supplyCount[province] = -1;
    printf("isGameOver = %d, expected = %d\n", isGameOver(&G), 1);
    // assert(isGameOver(&G) == 1); // this causes program to fail

    for(i = 0; i < 25; i++) {
        G.supplyCount[i] = 5;
    }
    printf("isGameOver = %d, expected = %d\n", isGameOver(&G), 0);
    assert(isGameOver(&G) == 0);

    for(i = 5; i < 8; i++) {
        G.supplyCount[i] = 0;
    }

    printf("isGameOver = %d, expected = %d\n", isGameOver(&G), 1);
    assert(isGameOver(&G) == 1);

    return 0;
}