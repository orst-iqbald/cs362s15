/***********************
* Author: Jon Derderian
* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: unittest1.c
* Description: A unit test of the shuffle() function in dominion.c.
* Compile instruction:
* unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {
	int n, r;
    //setting up gamestate
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};

    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//setting player 2's deck equal to player 1
	n = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
	while(n != 0) { //recopy decks
        memcpy(G->deck[0], G->deck[1], sizeof(G->deck[0])); //Copy the contents of first deck into second deck
        n = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
	}
	printf("Decks are now the same.\n");
    // begin test
    printf ("TESTING shuffle():\n");

    //shuffling first deck
	shuffle(0, G);
	//check to see if the decks are different
	n = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
    if(n == 0) {
        printf("Shuffle Test of Deck 1 has FAILED\n");
    }
	else{
		printf("Shuffle Test of Deck 1 has PASSED\n");
	}
	assert(n != 0);
	
	//shuffle first deck
	shuffle(1, G);
	//compare the decks to see if they are different
    n = memcmp(G->deck[0], G->deck[1], sizeof(G->deck[0]));
    if(n == 0) {
        printf("Shuffle Test of Deck 2 has FAILED\n");
    }
	else{
		printf("Shuffle Test of Deck 2 has PASSED\n");
	}
	assert(n != 0);
	
	printf("All tests passed!\n");
    return 0;
}
