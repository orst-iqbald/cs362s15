//Brittany Hopkins
//cardtest2.c
//smithy card

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
    printf ("Testing smithy card...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//first I'm going to set the hand so only the smithy card is in it.
	//by doing this i know that only the smithy card is being tested and that 
	//the resulting card count should be 3.
	state.handCount[0] = 1;
	state.hand[0][0] = smithy;
	
	//Now i'm going to run the playCard function with handPos = 0
	playCard(0, 0, 0, 0, &state);
	
	//Now the hand should contain 3 cards.
	//if all the test passed, tell them so. If not, say why it failed.
	if (state.handCount[0] == 3) {
		printf("PASSED: smithy card works properly\n");
	}
	else {
		printf("FAILED: smithy card should have drawn 3 cards\n");
		printf("card produced %d cards\n", state.handCount[0]);
	}
	
return 0;
}
