/* -----------------------------------------------------------------------
	Random tester for the function: 
	int newAdventurer(int currentPlayer, struct gameState *state);
	
	Description:
	This file tests the Adventurer card
	
	Include the following lines in your makefile:
	
	Compile instruction: add the lines below to the makefile
	randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
		gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

int main(){
	int r = 1;
	int iteration_count = 10;
	int seed, init_var, numPlayer, iteration;
	struct gameState *G = NULL;

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	
	if (NOISY_TEST) printf("*** %s Start \n", __FILE__);
	printf("=== Testing %s ===\n", __FILE__);
	printf ("Random Testing ADVENTURER Card \n");
	
	srand(time(NULL));
	for (iteration = 0; iteration < iteration_count; iteration++) {
		if (NOISY_TEST) printf("= Iteration: %d\n", iteration);
		
		/* Initialize data */
		G = NULL;
		int prevTreasureCards = 0;
		int postTreasureCards = 0;
		
		/* Generate Random Input */
		seed = randIntBetween(1000, 2000);
		init_var = randIntBetween(1, 9);
		numPlayer = randIntBetween(2, 5);
		if (NOISY_TEST) printf("= Random Input Values are: seed: %d, player: %d\n", seed, numPlayer);
		
		//initialize game with random input data, code taken from example
		G = newGame();
		memset(G, init_var, sizeof(struct gameState)); //clears the game state
		r = initializeGame(numPlayer, k, seed, G); //initialize a new game
		assert(r == 0); //this checks that initializeGame() ran and returned 0

		int currentPlayer = whoseTurn(G);
		
		//assign Adventurer card to player's hand position 0
		G->hand[currentPlayer][0] = adventurer;
		
		//cards in hand before Adventurer is played
		int handCount = G->handCount[currentPlayer];
		
		/*there should be two more Treasure cards in hand after Adventurer is played*/
		
		//for loop to check number of Treasure cards before Adventurer is played
		int i;
		int currentCard;
		for (i = 0; i < handCount; i++){
			currentCard = G->hand[currentPlayer][i];
			if(currentCard == copper || currentCard == silver || currentCard == gold){
				prevTreasureCards++;
			}
		}
		
		//play Adventurer card
		newAdventurer(currentPlayer, G);
		
		//for loop to check number of Treasure cards after Adventurer is played
		handCount = G->handCount[currentPlayer];
		for (i = 0; i < handCount; i++){
			currentCard = G->hand[currentPlayer][i];
			if(currentCard == copper || currentCard == silver || currentCard == gold){
				postTreasureCards++;
			}
		}
		
		//Debugging purposes
		printf ("previous Treasure Cards: %d \n", prevTreasureCards);
		printf ("post-action Treasure Cards: %d \n", postTreasureCards);
		
		if (postTreasureCards != (prevTreasureCards + 2)){
			printf ("Player does not have correct amount of cards in hand after playing ADVENTURER card. Test FAILED. \n");
		}
		
		if(postTreasureCards == (prevTreasureCards + 2)){
			printf("All Tests PASSED \n");
		}
		free(G);
	}
	if (NOISY_TEST) printf("*** %s Complete \n", __FILE__);
	return 0;
}