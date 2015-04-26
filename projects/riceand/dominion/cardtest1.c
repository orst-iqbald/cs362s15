/* -------------------------------------------
 * Unit Tests to cover the smithy card 
---------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testSmithy() {

	//set up gamestate
	int player = 0;
  int p = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
  	srand(time(0));
  	int randSeed = (rand() % 10000) + 1;
  	if (EXTRA_INFO == 1)
  		printf("randSeed = %d\n", randSeed);
  	
  	struct gameState s;

  	int r = initializeGame(p, k, randSeed, &s);
  	if (EXTRA_INFO == 1)
  		printf("r after init call = %d\n", r);

  	assert(r == 0); //else rest will fail
  	
  	//end gamestate set up

	/*
	Smithy testing:
		1. test that 3 cards are drawn
		2. test card is discarded after use
	*/


	//add smithy to hand at next available slot
	s.hand[player][s.handCount[player]] = smithy;
	int smithyPos = s.handCount[player];
	s.handCount[player]++;

	//create gamestate backup
	struct gameState s2 = s;

	int current_handCount = s.handCount[player];

	int returns = playSmithy(player, smithyPos, &s);
	assert(returns == 0); //this should pass here
	
	if (EXTRA_INFO == 1)
		printf("s.handCount = %d and current_handCount + 2 = %d\n", s.handCount[player], current_handCount+2);
	//comment out this assert since it is failing due to bug added from assignment 2
	//assert(s.handCount[player] == current_handCount + 2); //+2 since it discards smithy
	if (s.handCount[player] != current_handCount+2) {
		printf("smithy add 3 cards to the player's hand: FAILED\n");
		printf("s.handCount = %d and current_handCount + 2 = %d\n", s.handCount[player], current_handCount+2);
		printf("The above values should be equal for test to pass.\n");
	}
	else
		if (EXTRA_INFO == 1)
			printf("smithy add 3 cards to the player's hand: PASSED\n");

	
	//use backup gamestate for discard test

	//add dummy copper in case another smithy is drawn for discard test
	s2.hand[player][s2.handCount[player]] = copper;
	s2.handCount[player]++;

	returns = playSmithy(player, smithyPos, &s2);
	assert(returns == 0);
	assert(s2.hand[player][smithyPos] != smithy);

	if (EXTRA_INFO == 1)
		printf("playSmithy correctly discards smithy after use: PASSED\n");

}

 int main(int argc, char* argv[]) {

 	testSmithy();

 	return 0;
 }