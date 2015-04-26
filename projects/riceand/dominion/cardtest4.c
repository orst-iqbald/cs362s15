/* -------------------------------------------
 * Unit Tests to cover the Council Room card 
---------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

//set to 0 to turn OFF extra print statements
#define EXTRA_INFO 1

void testCouncilRoom() {

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
	Council Room testing:
		1. test 4 cards were drawn OK
    2. test numBuys +1
    3. test other players draw 1 card
    4. make sure council room was discarded OK
	*/

  //add Council Room to hand at next available slot
  s.hand[player][s.handCount[player]] = council_room;
  int councilRoomPos = s.handCount[player];
  s.handCount[player]++;

  //make gamestate backup
  struct gameState s2 = s;

  int returns = playCouncilRoom(&s, player, councilRoomPos);
  assert(returns == 0);

  //test discard
  assert(s.hand[player][councilRoomPos] != council_room);

  if (EXTRA_INFO == 1)
    printf("playCouncilRoom correctly discards Council Room after use: PASSED\n");

  //see if additional cards were drawn
  assert(s.handCount[player] == s2.handCount[player]+3); //+3 since council room was discarded

  int i;
  for (i = councilRoomPos; i < councilRoomPos+3; i++)
    assert(s.hand[player][i] >= curse && s.hand[player][i] <= treasure_map);

  if (EXTRA_INFO == 1)
    printf("playCouncilRoom correctly draws 4 cards: PASSED\n");

  //test numBuys
  //can't use this assert due to my bug
  //assert(s.numBuys == s2.numBuys+1);
  if (s.numBuys != s2.numBuys+1){
    printf("playCouncilRoom correctly updates numBuys by 1: FAILURE\n");
    printf("numBuys is %d and should be %d\n", s.numBuys, s2.numBuys+1);
  }

  //test other player draws a card
  assert(s.handCount[player+1] == s2.handCount[player+1]+1);
  //this assert looks at the position where the card would have been entered if drawn
  assert(s.hand[player+1][s2.handCount[player+1]] >= curse && s.hand[player+1][s2.handCount[player+1]] <= treasure_map);

  if (EXTRA_INFO == 1)
    printf("playCouncilRoom correctly draws a card for other player, as well: PASSED\n");
}

 int main(int argc, char* argv[]) {

 	testCouncilRoom();

 	return 0;
 }