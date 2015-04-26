/*------------------------------------------------------------------
 * Card test #3: great_hallCard() card function
 * cardtest3: cardtest3.c dominion.o rngs.o
 *		gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	
	printf("great_hallCard(): Test Begins");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("great_hallCard(): Game initialization failed.\n");
		error = -1;
	}
	
	state->hand[whoseTurn(state)][0] = great_hall;
	
	actions = state->numActions;
	
	great_hallCard(state, 0, 0);
	
	if(state->numActions != actions + 1)
	{
		printf("great_hallCard(): Failed to add correct number of actions");
		error = -1;
	}
	
	if(error != -1)
	{
		printf("great_hallCard(): Tests are finished. All tests passed.\n");
	}
	
	free(state);
	return 0;
}