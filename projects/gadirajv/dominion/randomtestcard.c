/* -----------------------------------------------------------------------
	Random Tester for the function: 
	int newSteward(int choice1, int choice2, int choice3, int currentPlayer, struct gameState *state, int handPos);
	
	Description:
	This file tests the Steward card to see if the +3 cards action is performed
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	randomtestcard: randomtestcard.c dominion.o rngs.o
		gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)
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

int randIntBetween(int a, int b) {
	assert(b > a);
	return rand()%(b - a) + a;
}

int main (){
	int r = 1;
	int iteration_count = 10;
	int seed, init_var, numPlayer, currentPlayer, iteration;
	struct gameState *G = NULL;
	int handCount = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	printf ("Testing STEWARD Card \n");
	printf ("=== Playing Steward for 2 draws === \n");
	for (iteration = 0; iteration < iteration_count; iteration++) {
		if (NOISY_TEST) printf("= Iteration: %d\n", iteration);
		
		/* Initialize data */
		G = NULL;
		
		/* Generate Random Input */
		seed = randIntBetween(1000, 2000);
		init_var = randIntBetween(1, 10);
		numPlayer = randIntBetween(2, 5);
		if (NOISY_TEST) printf("= Random Input Values are: Seed: %d, Player: %d\n", seed, numPlayer);
		
		//initialize game, code taken from example
		G = newGame();
		memset(G, init_var, sizeof(struct gameState)); //clears the game state
		r = initializeGame(numPlayer, k, seed, G); //initialize a new game
		assert(r == 0); //this checks that initializeGame() ran and returned 0
		
		currentPlayer = whoseTurn(G);
		
		//assign steward card to player's hand position 0
		G->hand[currentPlayer][0] = steward;
		
		//cards in hand before Steward is played 
		handCount = G->handCount[currentPlayer];
		
		//play Steward card for 2 draws
		newSteward(1, 0, 0, currentPlayer, G, 0);
		
		//Check if 2 draws happened correctly
		if (G->handCount[currentPlayer] == handCount+1 && G->playedCards[G->playedCardCount - 1] == steward) {
			printf("Steward 2 Draws passed. Test PASSED\n");
		} else {
			printf("Steward 2 Draws failed. Test FAILED\n");
		}
		
		free(G);
	}
	
	printf ("\n=== Playing Steward for 2 coins === \n");
	for (iteration = 0; iteration < iteration_count; iteration++) {
		if (NOISY_TEST) printf("= Iteration: %d\n", iteration);
		
		/* Initialize data */
		G = NULL;
		
		/* Generate Random Input */
		seed = randIntBetween(1000, 2000);
		init_var = randIntBetween(1, 10);
		numPlayer = randIntBetween(2, 5);
		if (NOISY_TEST) printf("= Random Input Values are: Seed: %d, Player: %d\n", seed, numPlayer);
		
		//initialize game, code taken from example
		G = newGame();	
		/* Redo test for coins now */
		G = malloc(sizeof(struct gameState));
		//initialize game, code taken from example
		memset(G, init_var, sizeof(struct gameState)); //clears the game state
		r = initializeGame(numPlayer, k, seed, G); //initialize a new game
		assert(r == 0); //this checks that initializeGame() ran and returned 0
		
		currentPlayer = whoseTurn(G);
		
		//assign steward card to player's hand position 0
		G->hand[currentPlayer][0] = steward;
		
		//cards in hand before Steward is played 
		handCount = G->handCount[currentPlayer];
		
		//store coins
		int coins = G->coins;
		
		//play Steward card for 2 coins
		newSteward(2, 0, 0, currentPlayer, G, 0);
		
		//Debugging purposes
		printf ("previous handcount is: %d \n", handCount);
		printf ("current handcount is: %d \n", G->handCount[currentPlayer]);
		
		// Check if coins has been properly incremented
		if (G->coins != coins + 2) {
			printf("coins has not been properly incremented. Test FAILED\n");
		} else {
			if (G->handCount[currentPlayer] == handCount-1 && G->playedCards[G->playedCardCount - 1] == steward) {
				printf("All Tests Passed. Test PASSED\n");
			} else {
				printf("Steward card was not correctly played. Test FAILED\n");
			}		
		}

		free(G);
	}

	printf ("\n=== Playing Steward for 2 discards === \n");
	for (iteration = 0; iteration < iteration_count; iteration++) {
		if (NOISY_TEST) printf("= Iteration: %d\n", iteration);
		
		/* Initialize data */
		G = NULL;
		
		/* Generate Random Input */
		seed = randIntBetween(1000, 2000);
		init_var = randIntBetween(1, 10);
		numPlayer = randIntBetween(2, 5);
		if (NOISY_TEST) printf("= Random Input Values are: Seed: %d, Player: %d\n", seed, numPlayer);
		
		//initialize game, code taken from example
		G = newGame();	

		//initialize game, code taken from example
		memset(G, init_var, sizeof(struct gameState)); //clears the game state
		r = initializeGame(numPlayer, k, seed, G); //initialize a new game
		assert(r == 0); //this checks that initializeGame() ran and returned 0
		
		currentPlayer = whoseTurn(G);
		
		//assign steward card to player's hand position 0
		G->hand[currentPlayer][0] = steward;
		
		//cards in hand before Steward is played 
		handCount = G->handCount[currentPlayer];
		
		//play Steward card for 2 discards
		newSteward(3, 0, 0, currentPlayer, G, 0);
		
		//Debugging purposes
		printf ("previous handcount is: %d \n", handCount);
		printf ("current handcount is: %d \n", G->handCount[currentPlayer]);
		
		//Check if 2 discards happened correctly
		if (G->handCount[currentPlayer] == handCount - 3) {
			printf("Steward Discards passed. Test PASSED\n");
		} else {
			printf("Steward Discards failed. Test FAILED\n");
		}

		free(G);
	}
	
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	return 0;
}