/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: cardtest2.c
* Description: A unit test of the Adventurer card in dominion.c.
* Compile instruction:
* cardtest1: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	//loop count
	int i;
    //setting up gamestate
	int hCount;
	int treasureHand = 0;
	int treasureHand2 = 0;
	int card;
	int pass = 0;
    int seed = 1000;
    int numPlayer = 2;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	
	printf ("TESTING Adventurer Card:\n");
	
	// initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//putting the adventurer card in the hand
	G->hand[whoseTurn(G)][0] = adventurer;
	//storing amount of card in hCount
	hCount = G->handCount[whoseTurn(G)];
	
	//counting the treasure cards
	for(i = 0; i < G->handCount[whoseTurn(G)]; i++) {
		card = G->hand[whoseTurn(G)][i];
        if(card == copper || card == silver || card == gold) {
            treasureHand++;
        }
	}
	
	cardAdventurer(G, 1);
	
	//counting treasure cards after the draw
	for(i = 0; i < G->handCount[whoseTurn(G)]; i++) {
		card = G->hand[whoseTurn(G)][i];
        if(card == copper || card == silver || card == gold) {
            treasureHand2++;
        }
	}
	//check for correct number of treasure cards
	if(hCount != (treasureHand2 + 2)){
		printf("Incorrect number of treasure cards added to hand, test FAILED.\n");
		pass++;
	}
	
	if(G->handCount[whoseTurn(G)] != (hCount + 1)){
		printf("Incorrect number of cards added to hand, test FAILED.\n");
		pass++;
	}
	
	if(pass == 0){
		printf("All tests PASSED.\n");
	}
	
	return 0;
}