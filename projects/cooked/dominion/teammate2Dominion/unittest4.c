/* ---------------------------------------------------------------------------------
 * Unit test for testing the endTurn() function
 * unittest4: unittest4.c dominion.o rngs.o
 * 		gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 * ---------------------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main() {
	int error = 0;
	//Initialize game variables
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int handCount, discardCount, i, coins = 0;

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("endTurn(): Game initialization failed.\n");
		error = -1;
	}

	handCount = state->handCount[whoseTurn(state)];
	discardCount = state->discardCount[whoseTurn(state)];

	endTurn(state);

	//Check that the previous players handCount was set to 0
	if(state->handCount[whoseTurn(state) - 1] != 0)
	{
		printf("endTurn(): Failed to set previous players handcount to 0.\n");
		error = -1;
	}

	//Check that the previous players discard pile was incremented by handCount
	if(state->discardCount[whoseTurn(state) - 1] != (handCount + discardCount))
	{
		printf("endTurn(): Failed to increment the previous players discardCount appropriately\n");
		error = -1;
	}

	//Check that all previous hand cards have been set to -1
	for(i = 0; i < handCount; ++i)
	{
		if(state->hand[whoseTurn(state) - 1][i] != -1)
		{
			printf("Failed to set the previous players hand to -1\n");
			error = -1;
		}
	}

	//Check that the state variables have been reset to their defaults, except coins and handCount
	//Which will be incremented my drawCard(..) and updateCoins(..) at the end of the function
	if(state->outpostPlayed != 0 ||
		state->phase != 0 ||
		state->numActions != 1 ||
		state->numBuys != 1 ||
		state->playedCardCount != 0)
	{
		printf("endTurn(): Failed to reset the state local variables\n");
		error = -1;
	}

	//Check that the current player has an appropriate handCount and coins has been incremented if necessary
	for(i = 0; i < 5; ++i)
	{
		if(state->hand[whoseTurn(state)][i] == copper) { coins++; }
		if(state->hand[whoseTurn(state)][i] == silver) { coins += 2; }
		if(state->hand[whoseTurn(state)][i] == gold) { coins += 3; }
	}

	if(state->handCount[whoseTurn(state)] != 5)
	{
		printf("endTurn(): Failed to increment handCount for new player\n");
		error = -1;
	}

	if(state->coins != coins)
	{
		printf("endTurn(): Incorrectly incremented the coins local variable in state\n");
		error = -1;
	}

	endTurn(state);

	//Check that the whoseTurn variable properly looped back upon getting to the last player
	if(whoseTurn(state) != 0)
	{
		printf("endTurn(): Failed to loop back to first player after last players turn\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("endTurn(): All tests passed.\n");
	}

	free(state);
	return 0;
}