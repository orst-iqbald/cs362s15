/* -----------------------------------------------------------------------
 * Testing the isGameOver() function in dominion.
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- */

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
    int failed = 0;
    int seed = 1000;
    int numPlayer = 2;
    //int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    //Taken from the example:
    printf ("TESTING isGameOver():\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    //Check if the game is over straight off the bat.
    printf("\nTest 1: Checking game over status directly after initializing game.\n");
    if(isGameOver(&G) == 1) {
        printf("Test 1: FAILED\n");
        failed++;
    }
    else {
        printf("Test 1: PASSED\n");
    }

    //Check gameover based on province count
    printf("\nTest 2: Checking game over based on current province count, and every province count until 0\n");
    int i;
    for(i = G.supplyCount[province]; i > 0; i--) {
        G.supplyCount[province] = i;
        if(isGameOver(&G) == 0) {
            printf("Test 2: Number of Provinces - %d | PASSED\n", G.supplyCount[province]);
        }
        else {
            printf("Test 2: Number of Provinces - %d | FAILED\n", G.supplyCount[province]);
            failed++;
        }
    }
    G.supplyCount[province] = 0;
    if(isGameOver(&G) == 1) {
        printf("Test 2: Number of Provinces - %d | PASSED\n", G.supplyCount[province]);
    }
    else {
        printf("Test 2: Number of Provinces - %d | FAILED\n", G.supplyCount[province]);
        failed++;
    }

    //Reset province count so that game is not over
    G.supplyCount[province] = 1;

    //Check supply piles, 3+ empty supply piles should end the game
    printf("\nTest 3: Checking game over based on supply piles, 3+ should end the game;\n");
    if(isGameOver(&G) == 0) { //Game shouldn't be over yet
        printf("Test 3: Number of Empty supplies: 0 | PASSED\n");
    }
    else {
        printf("Test 3: Number of Empty supplies: 0 | FAILED\n");
        failed++;
    }
    for(i = 0; i < 25; i++) {
        G.supplyCount[i] = 0;
        if(i < 2) { //Game shouldn't be over yet
            if(isGameOver(&G) == 0) {
                printf("Test 3: Number of Empty supplies: %d | PASSED\n", i+1);
            }
            else {
                printf("Test 3: Number of Empty supplies: %d | FAILED\n", i+1);
                failed++;
            }
        }
        else { //Game should be over at 3+
            if(isGameOver(&G) == 1) {
                printf("Test 3: Number of Empty supplies: %d | PASSED\n", i+1);
            }
            else {
                printf("Test 3: Number of Empty supplies: %d | FAILED\n", i+1);
                failed++;
            }
        }
    }

    if(failed == 0) {
        printf("\nAll Tests Passed\n");
    }
    else {
        printf("\nNot All Tests Passed\n");
    }

    return 0;
}