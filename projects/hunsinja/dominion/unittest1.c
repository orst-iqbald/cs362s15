//normal includes
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//dominion includes
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"

int gameOverTest(struct gameState *state)
{
	int test = isGameOver(state);	
	assert (test == 0); 
	printf ("Everything initiated correctly\n");

     state->supplyCount[province] = 0;	    
     test = isGameOver(state);
     assert (test == 1); 						
	printf ("Game ended on 0 provinces\n");
   
     state->supplyCount[province] = 1;		
  	test = isGameOver(state);
     assert (test == 0);						
	printf ("Game is on again with 1 province\n");

	state->supplyCount[4] = 0;			
     state->supplyCount[6] = 0;
     state->supplyCount[8] = 0;    
     test = isGameOver(state);
     assert(test == 1); 							
	printf ("Game is over with all supply counts at 0\n");
		
	state->supplyCount[6] = 1;
     test = isGameOver(state);
     assert (test == 0);						
	printf ("Game is on again with one pile restored\n");
	return 0;
}

int main () 
{
	int i;
	int seed = 1298347;
	int k[10] = {baron, adventurer, council_room, gardens, feast, mine, great_hall, village, remodel, smithy};
	struct gameState game;
	printf("Begin testing\n\n");
	for(i = 2; i <= MAX_PLAYERS; i++)
	{
		initializeGame(i, k, seed, &game);
		gameOverTest(&game);
	}
	printf("\nEnd testing\n");
	return 0;
}