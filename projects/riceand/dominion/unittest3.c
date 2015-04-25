/* -------------------------------------------
 * Unit Tests to cover playCard() function
---------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testPlayCard(){
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
		How to test playCard:
			1. make sure it returns 0
      2. test with phase != 0: return -1
      3. test with numActions < 1: return -1
      4. test with non action card: return -1
      5. find out what choice1, choice2, choice3 should be and test with bad values: -1
      6. test that the numActions is reduced by 1 after call
      7. test if coins are updated? different number? not sure...
  	*/

}

 int main(int argc, char* argv[]) {

 	testPlayCard();

 	return 0;
 }