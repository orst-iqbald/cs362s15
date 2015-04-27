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
		How to test playCard:
			1. make sure it returns 0
      2. test with phase != 0: return -1
      3. test with numActions < 1: return -1
      4. test with non action card: return -1
      5. look in to choice1, choice2, choice3
          a. they are always -1 when called from playdom.c
      6. test that the numActions is reduced by 1 after call
  	*/

      //add in a card to call playCard with
      int pos = 0;
      s.hand[player][pos] = adventurer;
      s.handCount[player]++;

      //call playCard and make sure it returns 0
      int returns = playCard(pos,-1,-1,-1,&s);
      assert(returns == 0);

      if (EXTRA_INFO == 1)
        printf("playCard returned 0 correctly: PASSED\n");

      int phase_backup = s.phase;
      s.phase = 0;
      returns = playCard(pos, -1, -1, -1, &s);
      assert(returns == -1);
      s.phase = phase_backup;
      if (EXTRA_INFO == 1)
        printf("playCard returned -1 when given phase = 0: PASSED\n");

      //add in non-action card to hand
      s.hand[player][pos+1] = copper;
      s.handCount[player]++;

      //save numActions
      int actions_value = s.numActions;
      //see if it returns -1 as it should
      returns = playCard(pos+1, -1, -1, -1, &s);
      assert(returns == -1);

      if (EXTRA_INFO == 1)
        printf("playCard returns -1 when given a non-action card: PASSED\n");

      //make sure it didn't decrease numActions for a non-action card
      assert(actions_value == s.numActions);

      if (EXTRA_INFO == 1)
        printf("playCard does not decrease numActions when it doesn't execute a card: PASSED\n");

      //test numActions decreases correctly
      actions_value = 5;
      s.numActions = actions_value;
      returns = playCard(pos, -1, -1, -1, &s);
      assert(returns == 0); //make sure function call worked
      assert(s.numActions == actions_value-1);

      if (EXTRA_INFO == 1)
        printf("playCard correctly decreases numAction: PASSED\n");

}

 int main(int argc, char* argv[]) {

 	testPlayCard();

 	return 0;
 }