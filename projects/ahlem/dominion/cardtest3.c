/*
 Matthew Ahle
 CS362 Assignment 3
 4/24/2015
 
 Council room card test
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
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int handCount[numPlayer];
	int i, buyCount;

	/* build gamestate to test */
	struct gameState *state = malloc(sizeof(struct gameState));

	/* initialize gamestate */
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("councilroomTest(): Game initialization failed.\n");
		error = -1;
	}

	/* swap council room card into the players hand */
	state->hand[whoseTurn(state)][0] = council_room;

	/* track handCount for each player */
	for(i = 0; i < numPlayer; ++i)
	{
		handCount[i] = state->handCount[i];
	}

	/* track original number of buys */
	buyCount = state->numBuys;

	/* call effectCouncilRoom function */
	effectCouncilRoom(state, 0);

	/* check that Council Room is in the discard pile */
	if(state->playedCards[state->playedCardCount - 1] != council_room)
	{
		printf("councilroomTest(): Council room was not discarded properly\n");
		error = -1;
	}

	/* handcount for the current player should be incremented by 3 and each other players handcount should be incremented by 1 */
	for(i = 0; i < numPlayer; ++i)
	{
		if(i == whoseTurn(state))
		{
			if(state->handCount[i] != (handCount[i] + 3))
			{
				printf("councilroomTest(): Error in incrementing the current players handCount\n");
				error = -1;
			}
		}
		else
		{
			if(state->handCount[i] != (handCount[i] + 1))
			{
				printf("councilroomTest(): Error in incrementing the other players handCounts\n");
				error = -1;
			}
		}
	}

	/* check that current players number of buys is incremented */
	if(state->numBuys != (buyCount + 1))
	{
		printf("councilroomTest(): Error incrementing the number of buys\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("councilroomTest(): All tests passed.\n");
	}

	free(state);
	return 0;
}