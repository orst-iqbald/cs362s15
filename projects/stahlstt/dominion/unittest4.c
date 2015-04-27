/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four functions (not card implementations or cardEffect) in dominion.c. 
Check these tests in as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. 

Unit test for endTurn();
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void testEndTurn(int players, struct gameState *state)
{
	int i, x;
	for(i = 0; i < players; i++) 
	{
		x = i + 1; 			// keeping track of whose turn it is

		printf("Ending Player %d's turn\n", state->whoseTurn + 1);
		endTurn(state);
		
		if (x % players == 0)
			x = 1;
		else
			x++;

		printf("It is Player %d's turn; expecting Player %d's turn\n", state->whoseTurn + 1, x);
		assert(state->whoseTurn + 1 == x);
	}
}

int main(int argc, char **argv)
{
	struct gameState game;
	int play, i;
	int seed = 9784562;
	
    int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
	printf("Testing endTurn()...\n");           

    for(i = 2; i <= MAX_PLAYERS; i++)
    {
    	play = initializeGame(i, k, seed, &game);
    	assert(play==0);
    	printf("\n-------- %d player game ----------\n", i);
    	testEndTurn(i, &game);
    }
   	printf("End test endTurn()...\n");           

	return 0;
}