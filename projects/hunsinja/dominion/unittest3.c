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

int shuffleTest(int player, struct gameState *state)
{
	printf("Before shuffling: ");
	printDeck(player, state);
 
	shuffle(player, state);	//SHUFFLE SHUFFLE SHUFFLE		
 
	printf("After shuffling: "); 	
	printDeck(player, state);

	return 0;
}

int main () 
{
	int i, play;
	int seed = 415789;
  	int k[10] = {baron, adventurer, council_room, gardens, feast, mine, great_hall, village, remodel, smithy};

	struct gameState game;
  	play = initializeGame(MAX_PLAYERS, k, seed, &game);
 
  	printf("Begin testing\n\n");  
	for(i = 0; i < MAX_PLAYERS; i++) 	
		shuffleTest(i, &game);	
 	printf("\nEnd testing\n");           

  	return 0;
}