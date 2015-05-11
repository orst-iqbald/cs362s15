//Brittany Hopkins
//cardtest1.c
//adventurer card

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
	int i;
	int treasure = 0;

	//printing the message for what is being tested
    printf ("Testing adventurer card...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//first I'm going to set the hand so only the adventurer card is in it.
	//by doing this i know that only the adventurer card is being tested and that 
	//the resulting treasure card count should be 2.
	state.handCount[0] = 1;
	state.hand[0][0] = adventurer;
	
	//Now i'm going to run the playCard function with handPos = 0
	playCard(0, 0, 0, 0, &state);
	
	//Now the hand should contain 2 cards, both of which should be treasure.
	if(state.handCount[0] <= 2 || state.handCount[0] >= 2) {
		printf("FAILED: handCount after adventurer should be 2\n");
		printf("handCount = %d\n", state.handCount[0]);
	}
	
	for(i = 0; i < 2; i++) {
		if(state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] == gold) {
			treasure++;
		}
	}
	
		
	//if all the test passed, tell them so. If not, say why it failed.
	if (treasure == 2) {
		printf("PASSED: adventurer card works properly\n");
	}
	else {
		printf("FAILED: adventurer card should have drawn 2 treasure cards\n");
		printf("card produced %d treasure cards\n", treasure);
	}
	
return 0;
}
