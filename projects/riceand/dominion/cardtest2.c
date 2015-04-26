/* -------------------------------------------
 * Unit Tests to cover the adventurer card 
---------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testAdventurer() {

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
	Adventurer testing:
		1. test that two treasure cards are drawn
    2. test that additional cards that may have been drawn have been discarded
    3. test that handcount is updated with new cards
    4. test card is discarded after use
    Notes: Use random value loop to run test multiple times
          save deck before call then after test against deck to make sure it is the same (minus adventurer)
              **account for treasure cards added** (so save size of deck before call too)
	*/
}

 int main(int argc, char* argv[]) {

 	testAdventurer();

 	return 0;
 }