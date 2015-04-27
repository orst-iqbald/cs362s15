/*
 * Michael Sigel
 * CS 362
 * Assignment 3
 * April 22nd 2015
 *
 * Card Test 4:
 * cutpurse
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int error = 0;
	/* initialize game variables */
	int numPlayer = 4;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, cutpurse, great_hall};
	int seed = 12345;
	int coins;
	int copperArr[numPlayer];
	int i, j;

	/* build gamestate to test */
	struct gameState *state = malloc(sizeof(struct gameState));

	/* initialize the gamestate */
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("cutpurseTest(): Game initialization failed.\n");
		error = -1;
	}

	/* swap Cutpurse card into players hand */
	state->hand[whoseTurn(state)][0] = cutpurse;

	/* track coin count */
	coins = state->coins;

	/* initialize copper count array to 0 */
	for(i = 0; i < numPlayer; ++i)
	{
		copperArr[i] = 0;
	}

	/* track number of copper coins each player has */
	for(i = 0; i < numPlayer; ++i)
	{
		for(j = 0; j < state->handCount[i]; ++j)
		{
			if(state->hand[i][j] == copper)
			{
				++copperArr[i];
			}
		}
	}

	/* call the effectCutpurse function */
	effectCutpurse(state, 0);

	/* check that Cutpurse is in the discard pile */
	if(state->playedCards[state->playedCardCount - 1] != cutpurse)
	{
		printf("cutpurseTest(): Cutpurse was not discarded properly\n");
		error = -1;
	}

	/* check that bonus coins were added */
	if(state->coins != (coins + 2))
	{
		printf("cutpurseTest(): Bonus coins were not added properly\n");
		error = -1;
	}

	/* check that other players with copper cards had one removed */
	for(i = 0; i < numPlayer; ++i)
	{
		if(i != whoseTurn(state) && copperArr[i] > 0)
		{
			for(j = 0; j < state->handCount[i]; ++j)
			{
				if(state->hand[i][j] == copper)
				{
					--copperArr[i];
				}
			}
			if(copperArr[i] == 0)
			{
				printf("cutpurseTest(): Copper coins were not removed properly\n");
				error = -1;
			}
		}
	}

	if(error != -1)
	{
		printf("cutpurseTest(): All tests passed.\n");
	}

	free(state);
	return 0;
}