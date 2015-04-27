//Brittany Hopkins
//cardtest3.c
//village card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NOISY_TEST 1

int main() {
	//I'm going to set all the variables that I need to stated a new Dominion game
    int seed = 1000;
    int numPlayer = 1;
    int k[10] = {adventurer, council_room, feast, gardens, mine
              , remodel, smithy, village, baron, great_hall};
    struct gameState state;

	//printing the message for what is being tested
    printf ("Testing village card...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//first I'm going to set the hand so only the village card is in it.
	//by doing this i know that only the village card is being tested
	//I'm also going to set numActions to 0 so I know that the resulting actions should be 2
	state.handCount[0] = 1;
	state.hand[0][0] = village;
	state.numActions = 0;
	
	//Now i'm going to run the playCard function with handPos = 0
	playCard(0, 0, 0, 0, &state);
	
	//Now the player should have 2 actions
	//if all the test passed, tell them so. If not, say why it failed.
	if (state.numActions == 2) {
		printf("PASSED: village card works properly\n");
	}
	else {
		printf("FAILED: village card should have provided 2 actions\n");
		printf("card produced %d actions\n", state.numActions);
	}
	
return 0;
}
