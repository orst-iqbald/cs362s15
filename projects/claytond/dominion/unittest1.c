/*
Darnel Clayton
unittest2.c
Testing supplyCount() function from Dominion.c
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
	int r;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, outpost};
    struct gameState G;
    int failed = 0;

    printf ("TESTING supplyCount():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("TEST 1: Test initial supply count from initialization. All values should be set to 10.\n");
    for(int i = 0; i < 10; i++) {
    	printf("%d", supplyCount(k[i], &G));
    	if(supplyCount(k[i], &G) == 10) {
    		printf("Test 1: card %d ...PASSED\n", i);
    	}
    	else {
    		printf("Test 1: card %d ...FAILED\n", i);
    		failed++;
    	}
    }

    printf("\nTEST 2: Manually change supply count on cards and see if it returns the right value.\n");
    for(int i = 0; i < 10; i++) {
    	G.supplyCount[k[i]] = i;
    	if(supplyCount(k[i], &G) == i) {
    		printf("Test 1: card %d ...PASSED\n", i);
    	}
    	else {
    		printf("Test 1: card %d ...FAILED\n", i);
    		failed++;
    	}
    }

    if(failed == 0) {
    	printf("\nAll Tests Passed\n");
    }
	return 0;
}
