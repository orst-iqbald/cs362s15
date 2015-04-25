/* -------------------------------------------
 * Unit Tests to cover shuffle() function
---------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testShuffle(){
	//set up gamestate
	int player = 1;
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
		How to test shuffle:
			1. copy player deck to array
			2. run shuffle on player deck
			3. make sure shuffle returns -1 if deckCount < 1 else 0
			4. check new deck against player deck
			    a. make sure at least 1 card has changed positions
			5. repeat this random number of times for up to 10 runs
  	*/

}

 int main(int argc, char* argv[]) {

 	testShuffle();

 	return 0;
 }