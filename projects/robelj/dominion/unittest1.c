//************************************
//Tests for whoseTurn() function
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

	printf ("TESTING whoseTurn()...\n");
	
	initializeGame(2, k, seed, &game);
	printf("game initialized properly\n");
	
	printf("confirm player 1 turn...\n");	
	assert(whoseTurn(&game) == 0);
  
  printf("confirm player 2 turn...\n");
	game.whoseTurn++;
  assert(whoseTurn(&game) == 1);

  printf("confirm player 1 turn...\n");
 	game.whoseTurn--;
  assert(whoseTurn(&game) == 0);


  printf ("ALL TESTS OK\n");

  return 0;
}