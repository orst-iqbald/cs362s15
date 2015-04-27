/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: cardtest1.c
* Description: A unit test of the Smithy card in dominion.c.
* Compile instruction:
* cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
	int pass = 0;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING Smithy Card:\n");

    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//give player smithy card
	G->hand[whoseTurn(G)][0] = smithy;
	printf("Player currently has %d card(s) in hand\n", hCount);
	
	//setting the hand count variable
	hCount = G->handCount[whoseTurn(G)];
	
	//running the smithy card
	cardSmithy(G, whoseTurn(G), 0);
	
	//see if smithy returned correct number of cards
	if(G->handCount[whoseTurn(G)] != (hCount+2)){ //add 3 cards, discard smithy card
        printf("Hand has incorrect number of cards, Test FAILED.\n");
		pass++;
    } 
	
	if(G->playedCards[G->playedCardCount - 1] != smithy){
		printf("Smithy was not discarded properly, Test FAILED.\n");
		pass++;
	}
	
	if(pass == 0){
		printf("All tests PASSED.\n");
	}

	return 0;
}