/* *****************************************************************************
Tina Stahlstedt
stahlstt@onid.oregonstate.edu
CS362 - 400 Spring 2015
Assignment 3

Write unit tests for four functions (not card implementations or cardEffect) in dominion.c. 
Check these tests in as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. 

Unit test for isGameOver();
***************************************************************************** */

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.c"
#include "rngs.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int testIsGameOver(struct gameState *state)
{
	int test = isGameOver(state);			// the game should not be over yet

    printf ("Taking Province deck to 0 ends the game?  ");
    state->supplyCount[province] = 0;		// 0 provinces should end the game
    
    test = isGameOver(state);
    assert (test == 1); 						// the game should be over now
		printf ("Yep, game over, no provinces.\n");
   
    state->supplyCount[province] = 1;		// putting the provinces back
    printf("Putting Province back makes game on again?  "); 
  
  	test = isGameOver(state);
    assert (test == 0);						// the game should not be over yet
		printf ("Game on again....\n");

  	printf("Taking three supply counts to 0 ends the game?  ");
		state->supplyCount[4] = 0;			// 3 empty piles should end the game
    state->supplyCount[6] = 0;
    state->supplyCount[8] = 0;
    
    test = isGameOver(state);
    assert(test == 1); 							// the game should be over now
		printf ("Yep, game over!\n");
		
		printf("Restoring 1 of the piles makes game on again?  ");
		state->supplyCount[6] = 1;

    test = isGameOver(state);
    assert (test == 0);						// the game should not be over
		printf ("YES!!!\n");
    return 0;
}

int main () 
{
    int play, i;
    int seed = 1298347;
    int k[10] = {adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
    struct gameState game;
    printf("Testing isGameOver()....\n");
    for(i = 2; i <= MAX_PLAYERS; i++)
    {
    	play = initializeGame(i, k, seed, &game);
    	assert(play==0);
    	printf("\n-------- %d player game ----------\n", i);
    	testIsGameOver(&game);
    }
    printf("\nEnd isGameOver() test.\n");
	return 0;
}