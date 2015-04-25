//************************************
//Tests for numHandCards() function
//************************************
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

int main () {

  struct gameState game;
  int seed = 1000;


  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};

	printf ("TESTING numHandCards()...\n");
	
	initializeGame(2, k, seed, &game);
  
  int structCountp1 = 0;
  
  //ensure our init game has the required 5 cards for both players
  assert((structCountp1 = game.handCount[0]) == 5);
  
  //assert numHandsCards returns 5 for player1
  int functionCountp1 = numHandCards(&game);
  assert(structCountp1 == functionCountp1);
  
  printf ("ALL TESTS OK\n");

  return 0;
}