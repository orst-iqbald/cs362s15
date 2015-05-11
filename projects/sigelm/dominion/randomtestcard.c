/* 
 * Michael Sigel
 * CS 362 Assignment 4
 * Randomtestcard.c
 * Random test for testing the effectCouncilRoom() function
 *
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main()
{
	/* integer we use plus the 10 cards */
	int i;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	remodel, smithy, village, baron, great_hall};

	/* running 100 tests to gather good amount of data */
	int testCount = 100;
	/* start our testing and display */
	printf("\nRandom Testing For Council Room Card\n\n");

	/* random number generator */
	int seed = 12125;
	SelectStream(1);
	PutSeed((long)seed);

	for(i = 0; i < testCount; ++i)
	{
		int j, pos, err = 0;
		/* need to build a gamestate to test */
		struct gameState *state = malloc(sizeof(struct gameState));
		struct gameState *prev = malloc(sizeof(struct gameState));
		seed = floor((Random() * 12125) + 1);

		/* int of the player */
		int numPlayer = floor((Random() * 3) + 2);
		initializeGame(numPlayer, cards, seed, state);

		/* these are what 'states' we are looking for data on */
		state->whoseTurn = floor(Random() * numPlayer);
		state->handCount[state->whoseTurn] = floor(Random() * (MAX_HAND / 3));
		state->deckCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->discardCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->playedCardCount = floor(Random() * 5);
		state->numBuys = floor((Random() * 4) + 1);

		/* fill hand with random cards 0 - 17 */
		for(j = 0; j < state->handCount[state->whoseTurn]; ++j)
		{
			state->hand[state->whoseTurn][j] = floor(Random() * 17);
		}

		/* fill deck with random cards 0 - 17 */
		for(j = 0; j < state->deckCount[state->whoseTurn]; ++j)
		{
			state->deck[state->whoseTurn][j] = floor(Random() * 17);
		}

		/* fill discard pile with random cards 0 - 17 */
		for(j = 0; j < state->discardCount[state->whoseTurn]; ++j)
		{
			state->discard[state->whoseTurn][j] = floor(Random() * 17);
		}

		/* randomly select position, set card to councilroom */
		pos = floor(Random() * state->handCount[state->whoseTurn]);
		state->hand[state->whoseTurn][pos] = council_room;

		/* display for our current state */
		printf("\nOur state:\nhandCount: %i\ndeckCount: %i\ndiscardCount: %i\n",
			state->handCount[state->whoseTurn],
			state->deckCount[state->whoseTurn],
			state->discardCount[state->whoseTurn]);

		/* print our cardpos */
		printf("Cardpos: %i\nPlayer: %i\nplayedCardCount: %i\nnumBuys: %i\n",
		  pos,
		  state->whoseTurn,
		  state->playedCardCount,
		  state->numBuys);

		/* copy our current gamestate */
		memcpy(prev, state, sizeof(struct gameState));

		/* call councilroom card */
		effectCouncilRoom(state, pos);

		/* check that each player had their handCount incremented by +1 */
		for(j = 0; j < state->numPlayers; ++j)
		{
			if(j == state->whoseTurn)
			{
				if(state->handCount[j] != (prev->handCount[j] + 3))
				{
					/* if we fail the test we need to show */
					printf("FAIL: current players hand was incorrectly incremented.\n");
						printf("Prev: %i, Post: %i, Seed: %i\n",
						prev->handCount[j],
						state->handCount[j],
						seed);
					err = 1;
				}
			}
			else if(state->handCount[j] != (prev->handCount[j] + 1))
			{
				/* if we fail the test we need to show */
				printf("FAIL: other players hands were incorrectly incremented.\n");
				printf("Prev: %i, Post: %i, Seed: %i\n",
					prev->handCount[j],
					state->handCount[j],
					seed);
					err = 2;
			}
		}

		/* check that player had number of buys incremented */
		if(state->numBuys != (prev->numBuys + 1))
		{
			/* if we fail the test we need to show */
			printf("FAIL: number of buys was not properly incremented.\n");
			printf("Prev: %i, Post: %i, Seed: %i\n",
					prev->numBuys,
					state->numBuys,
					seed);
			err = 3;
		}

		if(err == 0)
		{
			/* if the test passed then say so */
			printf("PASSED.\n");
		}
	}

	/* display that our test is over and this is the end of this specific file */
	printf("\nCouncil Room Card Random Testing Has Ended\n\n");
	return 0;
}