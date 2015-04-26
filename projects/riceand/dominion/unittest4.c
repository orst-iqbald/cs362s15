/* -------------------------------------------
 * Unit Tests to cover buyCard() function
---------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testBuyCard(){
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
		How to test buyCard:
			1. test numBuys < 1 returns -1
      2. test supplyCount < 1 returns - 1
      3. test if coins < getCost returns -1
      4. test if phase is set to 1
      5. testif card is in discard
      6. test if coins are updated
      7. test if numBuys decreased by 1
  	*/

}

 int main(int argc, char* argv[]) {

 	testBuyCard();

 	return 0;
 }