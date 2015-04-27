/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: cardtest4.c
* Description: A unit test of the Village card in dominion.c.
* Compile instruction:
* cardtest1: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    //setting up gamestate
	int hCount;
	int aCount;
	int pass = 0;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING Village Card:\n");

    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//put the Village card into the hand
	G->hand[whoseTurn(G)][0] = village;
	//put the number of cards in the hand into hCount
	hCount = G->handCount[whoseTurn(G)];
	//put number of actions into aCount
	aCount = G->numActions;
	
	//play the Village card
	cardVillage(G, whoseTurn(G), 0);
	
	//check for correct number of cards in hand
	if(G->handCount[whoseTurn(G)] != hCount){
		printf("Incorrect number of cards in the hand, Test FAILED.\n");
		pass++;
	}
	
	//check that proper number of actions were added
	if(G->numActions != (aCount + 1)){
		printf("Incorrect number of actions added, Test FAILED.\n");
		pass++;
	}
	
	if(pass == 0){
		printf("All tests PASSED.\n");
	}
	
	return 0;
}