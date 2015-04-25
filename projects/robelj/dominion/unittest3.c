//************************************
//Tests for supplyCount() function
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

  initializeGame(2, k, seed, &game);
  assert(game.supplyCount[curse] == 10);

	printf ("TESTING supplyCount()...\n");

  assert(supplyCount(0, &game) == 10);

  printf ("ALL TESTS OK\n");

  return 0;
}