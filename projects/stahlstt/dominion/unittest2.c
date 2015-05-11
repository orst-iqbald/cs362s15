/* ***************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four functions (not card implementations or cardEffect) 
in dominion.c. 
Check these tests in as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. 

 Unit test for shuffle(). Because initializing the game sets player 0's hand,
    player 0 starts with a 5 card deck. Also, I am expecting that initialize
		game is working correctly.
*************************************************************************** */   


#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int testShuffle(int player, struct gameState *state)
{
	printf("Before shuffle() on ");
	printDeck(player, state);
 
	shuffle(player, state);			// deck should be noticeably different now
 
	printf("Deck is different after shuffle() on "); 	
	printDeck(player, state);

	return 0;
}

int main () 
{
	int i, play;
	int seed = 415789;
  	int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};

	struct gameState game;
  	play = initializeGame(MAX_PLAYERS, k, seed, &game);
  	assert (play == 0);
 
  	printf("Testing shuffle()...\n");           

	for(i = 0; i < MAX_PLAYERS; i++) 
	{
		testShuffle(i, &game);
	}
	
 	printf("End testing shuffle()...\n");           

  	return 0;
}