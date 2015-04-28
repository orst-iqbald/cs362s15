#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    struct gameState G;

    /* Set all supply to 1. */
    for (i = 0; i < 25; ++i)
    {
      G.supplyCount[i] = 1;
    }

    assert(isGameOver(&G) == 0);
    printf("Game over when no card's supply has run out: false\n");

    G.supplyCount[0] = 0;
    assert(isGameOver(&G) == 0);
    printf("Game over when one card's supply has run out: false\n");

    G.supplyCount[1] = 0;
    assert(isGameOver(&G) == 0);
    printf("Game over when two cards' supplies have run out: false\n");

    G.supplyCount[2] = 0;
    assert(isGameOver(&G) == 1);
    printf("Game over when two cards' supplies have run out: true\n");

    printf("All tests passed!\n");

    return 0;
}
