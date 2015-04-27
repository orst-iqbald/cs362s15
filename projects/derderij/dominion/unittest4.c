/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: unittest4.c
* Description: A unit test of the buyCard() function in dominion.c.
* Compile instruction:
* unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int n;
    //setting up gamestate
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING buyCard():\n");
	
    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//test if no buys left
	G->numBuys = 0;
	G->coins = 10;
	G->supplyCount[gardens] = 5;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, -1);
	assert(n == -1);
	printf("No Buys left Test has PASSED.\n");
	
	//test if no coins left
	G->numBuys = 1;
	G->coins = 0;
	G->supplyCount[gardens] = 5;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, -1);
	assert(n == -1);
	printf("No Coins left Test has PASSED.\n");
	
	//test if no card left
	G->numBuys = 1;
	G->coins = 10;
	G->supplyCount[gardens] = 0;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, -1);
	assert(n == -1);
	printf("No Buying Card left Test has PASSED.\n");
	
	//test if no buys or coins left
	G->numBuys = 0;
	G->coins = 0;
	G->supplyCount[gardens] = 5;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, -1);
	assert(n == -1);
	printf("No Buys or Coins Test has PASSED.\n");
	
	//test if no all 0
	G->numBuys = 0;
	G->coins = 0;
	G->supplyCount[gardens] = 0;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, -1);
	assert(n == -1);
	printf("No Buys, Coins, or Buying Card Test has PASSED.\n");
	
	//test if have a value over 0
	G->numBuys = 1;
	G->coins = 10;
	G->supplyCount[gardens] = 5;
	n = buyCard(gardens, G);
	printf("buyCard = %d, expected = %d\n", n, 0);
	assert(n == 0);
	printf("Buying Test has PASSED.\n");
	
	printf("All Tests have PASSED.\n");
	
	return 0;
}