/* -----------------------------------------------------------------------
 * Test for isGameOver() function from dominion.c
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);
    printf ("TESTING isGameOver():\n");

//testing block for supply piles   
#if (NOISY_TEST == 1)
    printf("Test if game is over when there are not yet 3 empty supply piles... ");
#endif
    r = isGameOver(G);
#if (NOISY_TEST == 1)
    //conditional to test the return value from isGameOVer()
    if(r == 0) {
        printf("Test Passed!\n");
    }
    else {
        printf("Test Failed!\n");
    }
#endif

#if (NOISY_TEST == 1)
    printf("Test if game is over when 3 or more supply piles are empty... ");
#endif
    initializeGame(numPlayer, k, seed, G);
    for (i = 0; i < 3; ++i) {
        G->supplyCount[i] = 0;
    }
    r = isGameOver(G);
#if (NOISY_TEST == 1)
    //conditional to test the return value from isGameOVer()
    if(r == 1) {
        printf("Test Passed!\n");
    }
    else {
        printf("Test Failed!\n");
    }
#endif

    
//testing block for province cards   
#if (NOISY_TEST == 1)
    printf("Test if game is over when province cards are empty... ");
#endif
    initializeGame(numPlayer, k, seed, G);
    G->supplyCount[province] = 0;
    r = isGameOver(G);
#if (NOISY_TEST == 1)
    //conditional to test the return value from isGameOVer()
    if(r == 1) {
        printf("Test Passed!\n");
    }
    else {
        printf("Test Failed!\n");
    }
#endif

#if (NOISY_TEST == 1)
    printf("Test if game is over when province cards are NOT empty... ");
#endif
    initializeGame(numPlayer, k, seed, G);
    G->supplyCount[province] = 1;
    r = isGameOver(G);
#if (NOISY_TEST == 1)
    //conditional to test the return value from isGameOVer()
    if(r == 0) {
        printf("Test Passed!\n");
    }
    else {
        printf("Test Failed!\n");
    }
#endif

    printf("Testing Complete!\n");

    return 0;
}