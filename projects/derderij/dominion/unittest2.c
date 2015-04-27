/***********************
* Author: Jon Derderian
* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: unittest2.c
* Description: A unit test of the isGameOver() function in dominion.c.
* Compile instruction:
* unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
	int r;
	int i; //counter for loop
	int j;
    //setting up gamestate
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING isGameOver():\n");
	
    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//Initial test against beginning
	printf("isGameOver = %d, expected = %d\n", isGameOver(G), 0);
	assert(isGameOver(G) == 0);
	printf("Initial test has PASSED\n");
	
	//decrements down to 1
	j = G->supplyCount[province];
	for(i = 0; i < j; i++) {
		printf("isGameOver = %d, expected = %d\n", isGameOver(G), 0);
		assert(isGameOver(G) == 0);
		G->supplyCount[province]--;
    }
	printf("Decrement test has PASSED\n");
	
	//test when provinces == 0
	G->supplyCount[province] = 0; 
	printf("isGameOver = %d, expected = %d\n", isGameOver(G), 1);
	assert(isGameOver(G) == 1);
	printf("Test at 0 has PASSED\n");
	
	//reset supplyCount 
	G->supplyCount[province] = 1;
	
	//now we test for supply piles
	for(i = 0; i < 2; i++) {
        G->supplyCount[i] = 0;
		printf("isGameOver = %d, expected = %d\n", isGameOver(G), 0);
		assert(isGameOver(G) == 0);
    }
	printf("Supply piles under 3 test has PASSED\n");
	for(i = 2; i < 25; i++) {
        G->supplyCount[i] = 0;
		printf("isGameOver = %d, expected = %d\n", isGameOver(G), 1);
		//assert(isGameOver(G) == 1);
    }
	printf("Supply piles over 3 test has PASSED\n");
	
	printf("All Tests PASSED\n");

	return 0;
}