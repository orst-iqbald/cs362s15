/*------------------------------------------------------------------
 * Card test #4: villageCard() card function
 * cardtest4: cardtest4.c dominion.o rngs.o
 *		gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
 *------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main () {
	int error = 0;
	struct gameState * state = malloc(sizeof(struct gameState));
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	int actions;
	
	printf("villageCard(): Test Begins");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("villageCard(): Game initialization failed.\n");
		error = -1;
	}
	
	state->hand[whoseTurn(state)][0] = village;
	
	actions = state->numActions;
	
	villageCard(state, 0, 0);
	
	if(state->numActions != actions + 2)
	{
		printf("villageCard(): Failed to add correct number of actions\n");
		error = -1;
	}
	
	if(error != -1)
	{
		printf("villageCard(): Tests are finished. All tests passed.\n");
	}
	
	free(state);
	return 0;
}