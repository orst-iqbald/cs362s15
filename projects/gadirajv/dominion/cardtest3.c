/* -----------------------------------------------------------------------
	Unit test for the function: 
	int newVillage (int currentPlayer, struct gameState *state, int handPos);
	
	Description:
	This file tests the Village card to see if the +3 cards action is performed
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	cardtest3: cardtest3.c dominion.o rngs.o
		gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
 * ----------------------------------------------------------------------- 
 */

#include <stdio.h>
#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main (){
	int seed = 1000;
	int numPlayer = 2;
	int r = 1;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState *G = malloc(sizeof(struct gameState));
	int handCount = 0;
	
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	
	printf ("Testing VILLAGE Card \n");
	
	//initialize game, code taken from example
	memset(G, 11, sizeof(struct gameState)); //clears the game state
	r = initializeGame(numPlayer, k, seed, G); //initialize a new game
	assert(r == 0); //this checks that initializeGame() ran and returned 0
	
	int currentPlayer = whoseTurn(G);
	
	//assign village card to player's hand position 0
	G->hand[currentPlayer][0] = village;
	
	//cards in hand before Village is played 
	handCount = G->handCount[currentPlayer];
	
	//store numActions
	int numActions = G->numActions;
	
	//play Village card
	newVillage(currentPlayer, G, 0);
	
	//Debugging purposes
	printf ("previous handcount is: %d \n", handCount);
	printf ("current handcount is: %d \n", G->handCount[currentPlayer]);
	
	// Check if numActions has been properly incremented
	if (G->numActions != numActions + 2) {
		printf("numActions has not been properly incremented. Test FAILED\n");
	} else {
		if (G->handCount[currentPlayer] == handCount && G->playedCards[G->playedCardCount - 1] == village) {
			printf("All Tests Passed. Test PASSED\n");
		} else {
			printf("Village card was not correctly played. Test FAILED\n");
		}		
	}

	free(G);
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	return 0;
}