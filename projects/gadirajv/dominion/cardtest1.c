/* -----------------------------------------------------------------------
	Unit test for the function: 
	int newSmithy(int currentPlayer, struct gameState *state, int handPos);
	
	Description:
	This file tests the Smithy card to see if the +3 cards action is performed
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	cardtest1: cardtest1.c dominion.o rngs.o
		gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
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
	
	printf ("Testing SMITHY Card \n");
	
	//initialize game, code taken from example
	memset(G, 23, sizeof(struct gameState)); //clears the game state
	r = initializeGame(numPlayer, k, seed, G); //initialize a new game
	assert(r == 0); //this checks that initializeGame() ran and returned 0
	
	int currentPlayer = whoseTurn(G);
	
	//assign smithy card to player's hand position 0
	G->hand[currentPlayer][0] = smithy;
	
	//cards in hand before Smithy is played 
	handCount = G->handCount[currentPlayer];
	
	//play Smithy card
	newSmithy(currentPlayer, G, 0);
	
	//Debugging purposes
	printf ("previous count is: %d \n", handCount);
	printf ("current handcount is: %d \n", G->handCount[currentPlayer]);
	
	//check if player has two additional cards in hand - three additional cards, and Smithy card discarded from hand
 	if (G->handCount[currentPlayer] != (handCount + 2)){
		printf ("Player does not have correct amount of cards in hand after playing smithy card. FAILED. \n");
		//check to see if error was due to incorrect number of cards added or if Smithy card not discarded
		//check playedCards array for smithy card
		if(G->playedCards[G->playedCardCount - 1] != smithy){
			printf("Test FAILED because Smithy card not discarded. \n");
		}else{
			printf("Test FAILED because three additional cards were not added after Smithy Card was played.\n");
		}
	}else{
		//make sure this condition is met before indicating tests passed
		assert (G->handCount[currentPlayer] == (handCount + 2));
		printf ("Tests PASSED.\n");
	}
	
	free(G);
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	return 0;
}