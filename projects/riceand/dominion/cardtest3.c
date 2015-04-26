/* -------------------------------------------
 * Unit Tests to cover the outpost card 
---------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testOutpost() {

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
	Outpost testing:
		1. test outpost flag is set
    2. test card was discarded
	*/

  //add outpost to hand at next available slot
  s.hand[player][s.handCount[player]] = outpost;
  int outpostPos = s.handCount[player];
  s.handCount[player]++;

  //create gamestate backup
  struct gameState s2 = s;

  int returns = playOutpost(&s, player, outpostPos);
  assert(returns == 0);

  //test outpost flag set
  assert(s.outpostPlayed == s2.outpostPlayed+1);

  if (EXTRA_INFO == 1)
    printf("playOutpost correctly sets outpost flag: PASSED\n");

  //make sure it was discarded
  assert(s.hand[player][outpostPos] != outpost);

  if (EXTRA_INFO == 1)
    printf("playOutpost correctly discards used outpost card: PASSED\n");
}

 int main(int argc, char* argv[]) {

 	testOutpost();

 	return 0;
 }