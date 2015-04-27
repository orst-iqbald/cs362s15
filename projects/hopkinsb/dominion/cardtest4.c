//Brittany Hopkins
//cardtest4.c
//great_hall card

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
	int failed = 0;

	//printing the message for what is being tested
    printf ("Testing great_hall card...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//first I'm going to set the hand so only the great_hall card is in it.
	//by doing this i know that only the great_hall card is being tested
	//This should also let me test that the resulting hand has only 1 card
	//I'm also going to set numActions to 0 so I know that the resulting actions should be 1
	state.handCount[1] = 1;
	state.hand[1][0] = great_hall;
	state.numActions = 0;
	
	//Now i'm going to run the playCard function with handPos = 0
	playCard(0, 0, 0, 0, &state);
	
	//Now the player should have 1 action
	if (state.numActions != 1) {
		printf("FAILED: great_hall should have produced 1 action\n");
		printf("card produced %d action(s)\n", state.numActions);
		failed++;
	}
	
	//The hand should also still have 1 card in it
	if(state.handCount[1] != 1) {
		printf("FAILED: great_hall should have produced 1 card\n");
		printf("card produced %d card(s)\n", state.handCount[1]);
		failed++;
	}
	
	//if all tests passed, say so. If not, say how many failed.
	if(failed == 0) {
		printf("PASSED: great_hall passed 2 of 2 tests\n");
	}
	else { 
		printf("FAILED: great_hall failed %d of 2 tests\n", failed);
	}
	
return 0;
}
