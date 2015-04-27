//Brittany Hopkins
//unittest2.c
//getCost()

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
    printf ("Testing getCost()...\n");
	//clearing current game state
    memset(&state, 23, sizeof(struct gameState));   
	//initializing new game
    initializeGame(numPlayer, k, seed, &state); 
	
	//setting up arrays to hold card names and the correct costs for each card to be looped through
	const char *cardArray[27] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	int cardCost[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
	
	//basically this loops and requests the value for each card from getCost() and then compares that
	//to the correct value in the cardCost array. If they aren't the same it prints an error.
	//I'm only printing messages for errors so i don't clog up the thing
	for(i = 0; i < 27; i++) {
		if (getCost(i) != cardCost[i]) {
			printf("FAILED: Cost of %s should be %d\n", cardArray[i], cardCost[i]);
			printf("getCost() returned cost of %d\n", getCost(i));
			failed++;
		}
	}
	
	//if all tests passed, say so. Else tell them how many failed.
	if(failed == 0) {
		printf("getCost() passed 27 of 27 tests\n");
	}
	else {
		printf("getCost() failed %d of 27 tests\n", failed);
	}
	
return 0;
}
