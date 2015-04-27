//Brittany Hopkins
//unittest1.c
//updateCoins()

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
	int i;

	//printing the message for what is being tested
    printf ("Testing updateCoins()...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//Testing for hand of all coppers, no bonus applied
	//Total should equal handCount * 1
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = copper;
	}
	//calling the function
	updateCoins(0, &state, 0);
	//if the total coins aren't what we expect, print the error message
	if (state.coins != (state.handCount[0] * 1)) {
		printf ("FAILED: Test of all coppers (no bonus) should have produced %d coins.\n", state.handCount[0] * 1);
		printf ("Test produced %d coins\n", state.coins);
		failed++;
	}
	//Else print the pass message
	else {
		printf("PASSED: Test of all coppers (no bonus) produced correct results\n");
		
	}
	
	//Essentially repeat the same thing for all tests.....
	
	//Testing for hand of all silvers, no bonus applied
	//Total should equal handCount * 2
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = silver;
	}
	updateCoins(0, &state, 0);
	if (state.coins != (state.handCount[0] * 2)) {
		printf ("FAILED: Test of all silvers (no bonus) should have produced %d coins.\n", state.handCount[0] * 2);
		printf ("Test produced %d coins\n", state.coins);
		failed++;
	}
	else {
		printf("PASSED: Test of all silvers (no bonus) produced correct results\n");
		
	}
	
	//Testing for hand of all golds, no bonus applied
	//Total should equal handCount * 3
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = gold;
	}
	updateCoins(0, &state, 0);
	if (state.coins != (state.handCount[0] * 3)) {
		printf ("FAILED: Test of all golds (no bonus) should have produced %d coins.\n", state.handCount[0]* 3);
		printf ("Test produced %d coins\n", state.coins);
		failed++;
	}
	else {
		printf("PASSED: Test of all golds (no bonus) produced correct results\n");
		
	}
	
	//Testing for hand of all non-treasure cards, no bonus applied
	//Total should equal 0
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = feast;
	}
	updateCoins(0, &state, 0);
	if (state.coins != 0) {
		printf ("FAILED: Test of all non-treasure cards (no bonus) should have produced 0 coins.\n");
		printf ("Test produced %d coins\n", state.coins);
		failed++;
	}
	else {
		printf("PASSED: Test of all non-treasure cards (no bonus) produced correct results\n");
		
	}
	
	//Testing application of bonus by using all non-treasure cards
	//Bonus set to 4, total coins should equal 4
	for(i = 0; i < state.handCount[0]; i++) {
		state.hand[0][i] = feast;
	}
	updateCoins(0, &state, 4);
	if (state.coins != 4) {
		printf ("FAILED: Test of all non-treasure cards (with +4 bonus) should have produced 4 coins.\n");
		printf ("Test produced %d coins\n", state.coins);
		failed++;
	}
	else {
		printf("PASSED: Test of all non-treasure cards (with +4 bonus) produced correct results\n");
		
	}
	
	//if all the test passed, tell them so. If not, say how many failed.
	if (failed == 0) {
		printf("updateCoins() passed 5 of 5 tests\n");
	}
	else {
		printf("updateCoins() failed %d of 5 tests\n", failed);
	}
	
return 0;
}
