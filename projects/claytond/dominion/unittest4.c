/*
Darnel Clayton
unittest4.c
Testing shuffle() function from Dominion.c
Referenced testUpdateCoins.c example.
CS 362
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int n;
    int r;
    int passed = 0;
    int seed = 1000;
    int numPlayer = 2;
    //int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf ("TESTING shuffle():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    //Check if the current decks are equal (no pass or fail here)
    n = memcmp(G.deck[0], G.deck[1], sizeof(G.deck[0]));
    if(n == 0) {
        printf("Starting decks are equal\n");
    }
    else {
        printf("Starting decks are not equal, copying first deck into second deck for further testing\n");
        memcpy(G.deck[0], G.deck[1], sizeof(G.deck[0])); //Copy the contents of first deck into second deck
        n = memcmp(G.deck[0], G.deck[1], sizeof(G.deck[0]));
        if(n == 0) {
            printf("Decks are now equal. Moving on.\n");
        }
    }

    printf("\nTest 1: Shuffling the first deck\n");
    shuffle(0, &G);
    printf("Test 1: Checking if decks are different\n");
    n = memcmp(G.deck[0], G.deck[1], sizeof(G.deck[0]));
    if(n == 0) {
        printf("Test 1: FAILED\n");
    }else {
        printf("Test 1: PASSED\n");
        passed++;
    }

    printf("\nTest 2: Shuffling the second deck\n");
    shuffle(1, &G);
    printf("Test 2: Checking if decks are different\n");
    n = memcmp(G.deck[0], G.deck[1], sizeof(G.deck[0]));
    if(n == 0) {
        printf("Test 2: FAILED\n");
    }else {
        printf("Test 2: PASSED\n");
        passed++;
    }

    if(passed == 2) {
        printf("\nAll Tests Passed\n");
    }

    return 0;
}
