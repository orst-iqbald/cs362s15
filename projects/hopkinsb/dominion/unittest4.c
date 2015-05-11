//Brittany Hopkins
//unittest4.c
//isGameOver()

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() {
	//I'm going to set all the variables that I need to start a new Dominion game
    int seed = 1000;
    int numPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
              , remodel, smithy, village, baron, great_hall};
    struct gameState state;
	int failed = 0;
	int i;

	//printing the message for what is being tested
    printf ("Testing isGameOver()...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//Testing for game over when supplyCount[province] > 0
	//Game should not be over
	state.supplyCount[province] = 1;
	if(isGameOver(&state) != 0) { 
		printf("FAILED: game over when province cards are still available\n");
		failed++;
	}
	
	//Testing for game over when supplyCount[province] = 0
	//Game should be over
	state.supplyCount[province] = 0;
	if(isGameOver(&state) != 1) { 
		printf("FAILED: game NOT over when no province cards remain\n");
		failed++;
	}
	
	//Testing for game over when all supply piles > 0;
	//Game should not be over
	for(i = 0; i < 25; i++) {
		state.supplyCount[i] = 1;
	}
	if(isGameOver(&state) != 0) {
		printf("FAILED: game over when 3 supply piles are still > 0\n");
		failed++;
	}
	
	//Testing for game over when 2 supply piles = 0;
	//Game should not be over
	for(i = 0; i < 2; i++) {
		state.supplyCount[i] = 0;
	}
	if(isGameOver(&state) != 0) {
		printf("FAILED: game over when two supply piles = 0\n");
		failed++;
	}
	
	//Testing for game over when 3 supply piles = 0;
	//Game should be over
	for(i = 0; i < 3; i++) {
		state.supplyCount[i] = 0;
	}
	if(isGameOver(&state) != 1) {
		printf("FAILED: game NOT over when three supply piles = 0\n");
		failed++;
	}
	
	//if all tests passed, say so. Else tell them how many failed.
	if(failed == 0) {
		printf("isGameOver() passed 5 of 5 tests\n");
	}
	else {
		printf("isGameOver() failed %d of 5 tests\n", failed);
	}
	
return 0;
}
