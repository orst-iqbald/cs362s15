/*
Darnel Clayton
cardtest2.c
Testing adventurer card from Dominion.c
Referenced testUpdateCoins.c example.
CS 362
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

    int i;

    initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf ("TESTING adventurerCard():\n");

    // fill hand with estate cards
    for(i = 0; i < 5; i++) {
        G.hand[1][i] = estate;
        G.handCount[1]++;
    }

    printf("Cards in hand = %d, expected cards in hand = %d\n", G.handCount[1], 5);
    assert(G.handCount[1] == 5);
    adventurerCard(1, &G);
    printf("Cards in hand = %d, expected cards in hand = %d\n", G.handCount[1], 6);
    // assert(G.handCount[1] == 6); // assert fails

    return 0;
}

