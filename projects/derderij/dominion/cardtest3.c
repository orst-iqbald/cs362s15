/* ONID ID: derderij
* Class: CS 362
* Assignment: Assignment 3
* Filename: cardtest3.c
* Description: A unit test of the Cutpurse card in dominion.c.
* Compile instruction:
* cardtest1: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	//count loop
	int i, j;
    //setting up gamestate
	int pass = 0;
    int seed = 1000;
    int numPlayer = 3;
    struct gameState *G = malloc(sizeof(struct gameState));
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy,
			village, baron, great_hall};
	int coins;
	int copperCount[numPlayer];
	int copperCount2[numPlayer];
	
	printf ("TESTING Cutpurse Card:\n");

    // initialize game, as seen in example
    memset(G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, G); // initialize a new game
	assert(r == 0);
	
	//put cutpurse into players hand
	G->hand[whoseTurn(G)][0] = cutpurse;
	//store initial amount of coins
	coins = G->coins;
	
	//count how many copper each player has
	for(i = 0; i < numPlayer; i++) {
		for(j = 0; j < G->handCount[i]; j++) {
			if(G->hand[i][j] == copper) {
				copperCount[i]++;
			}
		}
	}
	
	//play cutpurse card
	cardCutpurse(G, whoseTurn(G), 0);
	
	//check if coins were add
	if(G->coins != (coins + 2)) {
		printf("Bonus coins not added, Test FAILED.\n");
		pass++;
	}
	//updating copper count in new array
	for(i = 0; i < numPlayer; i++) {
		for(j = 0; j < G->handCount[i]; j++) {
			if(G->hand[i][j] == copper) {
				copperCount2[i]++;
			}
		}
	}
	//checking to see if 
	for(i = 0; i < numPlayer; i++) {
		if(i != whoseTurn(G) && copperCount[i] > 0){
				if(copperCount[i] != (copperCount2[i] - 1)){
					printf("Incorrect amount of copper discarded, test FAILED.\n");
					pass++;
				}
			}
	}
	
	if(pass == 0){
		printf("All tests PASSED.\n");
	}
	
	return 0;
}