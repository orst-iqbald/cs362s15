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
      5. test if coins are updated
      6. test if numBuys decreased by 1
  	*/
      
      //backup and test numBuys
      int saved_numBuys = s.numBuys;
      s.numBuys = 0;
      int returns = buyCard(copper, &s);
      assert(returns == -1);
      
      if (EXTRA_INFO == 1)
        printf("buyCard returns -1 when numBuys < 1: PASSED\n");

      s.numBuys = 2;
      returns = buyCard(copper, &s);
      assert(returns == 0);
      assert(s.numBuys == 1);
      s.numBuys = saved_numBuys;
      if (EXTRA_INFO == 1)
        printf("buyCard subtracts 1 from numBuys after successful run: PASSED\n");

      if (EXTRA_INFO == 1)
        printf("buyCard puts ")

      //save and test if card to buy is out of stock
      int saved_copper_count = s.supplyCount[copper];
      s.supplyCount[copper] = 0;
      returns = buyCard(copper, &s);
      assert(returns == -1);
      s.supplyCount[copper] = saved_copper_count;

      if (EXTRA_INFO == 1)
        printf("buyCard returns -1 when card to buy does not have supply left: PASSED\n");

      int saved_coins = s.coins;
      s.coins = 0;
      returns = buyCard(silver, &s);  //silver is cost 3
      assert(returns == -1);
      s.coins = saved_coins;

      if (EXTRA_INFO == 1)
        printf("buyCard returns -1 when player has insufficient coins to buy it: PASSED\n");

      //silver is 3 and current will be 5 here
      returns = buyCard(silver, &s);
      assert(returns == 0);
      assert(s.coins == saved_coins - getCost(silver));

      if (EXTRA_INFO == 1)
        printf("buyCard correctly subtracts cost of card bought: PASSED\n");
}

 int main(int argc, char* argv[]) {

 	testBuyCard();

 	return 0;
 }