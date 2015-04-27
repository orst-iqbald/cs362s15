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
		1. test that two treasure cards are drawn OK
    2. test that additional cards that may have been drawn have been discarded OK
    3. test that handcount is updated with new cards OK
    4. test card is discarded after use OK
	*/

  //add adventurer to hand at next available slot
  s.hand[player][s.handCount[player]] = adventurer;
  int adventurerPos = s.handCount[player];
  s.handCount[player]++;

  //create gamestate backup
  struct gameState s2 = s;

  int returns = playAdventurer(&s, player);
  assert(returns == 0);
  //assert last two positions in hand are treasure, use adventurerpos and adventurerpos+1
  //both asserts below this fail due to bug I put in and bug that it doesn't discard adventurer
  //assert(s.hand[player][adventurerPos] == copper || s.hand[player][adventurerPos] == silver || s.hand[player][adventurerPos] == gold); 
  //assert(s.hand[player][adventurerPos+1] == copper || s.hand[player][adventurerPos+1] == silver || s.hand[player][adventurerPos+1] == gold);
  if (s.hand[player][adventurerPos] != copper && s.hand[player][adventurerPos] != silver && s.hand[player][adventurerPos] != gold) {
    printf("playAdventurer draws 2 treasure cards: FAILURE\n");
  }
  if (s.hand[player][adventurerPos+1] != copper && s.hand[player][adventurerPos+1] != silver && s.hand[player][adventurerPos+1] != gold) {
    printf("playAdventurer draws 2 treasure cards: FAILURE\n");
  }
  if (s.hand[player][adventurerPos] == adventurer)
    printf("playAdventurer discards adventurer after use: FAILURE\n");

  //test handCount updated
  //assert fails due to my bug
  //assert(s.handCount[player] == s2.handCount[player]+2);
  if (s.handCount[player] != s2.handCount[player]+2) {
    printf("handCount is updated to reflect new cards: FAILURE\n");
    printf("handCount is %d and should be %d\n", s.handCount[player], s2.handCount[player]+2);
  }

  //make sure all cards before adventurer in original deck were not altered
  int i;
  for (i = 0; i < adventurerPos; i++) {
    assert(s.hand[player][i] == s2.hand[player][i]);
  }

  if (EXTRA_INFO == 1)
    printf("playAdventurer does not alter cards in hand before adventurer: PASSED\n");

  //test additional cards drawn were discarded
  for (i = adventurerPos; i < s.handCount[player]; i++) {
    //assert fails due to my bug, need to use prints
    //assert(s.hand[player][i] == copper || s.hand[player][i] == silver || s.hand[player][i] == gold);
    if (s.hand[player][i] != copper && s.hand[player][i] != silver && s.hand[player][i] != gold) {
      printf("playAdventurer correctly discards additional cards other than treasure: FAILURE\n");
      printf("Failure at card position %d and card = %d\n", i, s.hand[player][i]);
    }
    else {
      if (EXTRA_INFO == 1)
        printf("Card at position %d is a treasure and should be there!\n", i);
    }
  }
}

 int main(int argc, char* argv[]) {

 	testAdventurer();

 	return 0;
 }