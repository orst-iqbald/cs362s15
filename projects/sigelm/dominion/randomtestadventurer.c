/* 
 * Michael Sigel
 * CS 362 Assignment 4
 * Randomtestadventurer.c
 * Random test for testing the effectAdventurer() function
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

	/* we are going to run 100 tests to gather good amount of data */
	int testCount = 100;
	/* display that we are starting our test */
	printf("\nRandom Testing For Adventurer Card\n\n");

	/* set up random number generator */
	int seed = 12125;
	SelectStream(1);
	PutSeed((long)seed);

	for(i = 0; i < testCount; ++i)
	{
		int j, pos, preTreasure = 0, postTreasure = 0, err = 0;
		/* we need to build a gamestate that we can test with */
		struct gameState *state = malloc(sizeof(struct gameState));
		struct gameState *prev = malloc(sizeof(struct gameState));
		seed = floor((Random() * 12125) + 1);
		
		/* num of player */
		int numPlayer = floor((Random() * 3) + 2);
		initializeGame(numPlayer, cards, seed, state);

		/* what state are we in for our data to be displayed */
		state->whoseTurn = floor(Random() * numPlayer);
		state->handCount[state->whoseTurn] = floor(Random() * (MAX_HAND / 3));
		state->deckCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->discardCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->playedCardCount = floor(Random() * 5);

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

		/* randomly select a position, set card to adventurer */
		pos = floor(Random() * state->handCount[state->whoseTurn]);
		state->hand[state->whoseTurn][pos] = adventurer;

		/* start to print the information we care about, starting with state */
		printf("\nOur state:\nhandCount: %i\ndeckCount: %i\ndiscardCount: %i\n",
			state->handCount[state->whoseTurn],
			state->deckCount[state->whoseTurn],
			state->discardCount[state->whoseTurn]);

		/* print our cardpos */
		printf("Cardpos: %i\nPlayer: %i\nplayedCardCount: %i\n",
			pos,
			state->whoseTurn,
			state->playedCardCount);

		/* copy gamestate */
		memcpy(prev, state, sizeof(struct gameState));

		/* call adventurer card */
		effectAdventurer(state, pos);

		/* count up how many treasure cards in players hand before playing adventurer card */
		for(j = 0; j < prev->handCount[prev->whoseTurn]; ++j)
		{
			if(prev->hand[prev->whoseTurn][j] == copper ||
				prev->hand[prev->whoseTurn][j] == silver ||
				prev->hand[prev->whoseTurn][j] == gold)
				{
					++preTreasure;
				}
		}

		/* count up how many treasure cards in players hand after playing the adventurer card */
		for(j = 0; j < state->handCount[state->whoseTurn]; ++j)
		{
			if(state->hand[state->whoseTurn][j] == copper ||
				state->hand[state->whoseTurn][j] == silver ||
				state->hand[state->whoseTurn][j] == gold)
			{		
				++postTreasure;
			}
		}

		if((prev->deckCount[prev->whoseTurn] + prev->discardCount[prev->whoseTurn] - 2) !=
		(state->deckCount[state->whoseTurn] + state->discardCount[state->whoseTurn]))
		{
			/* if we fail to pass the test */
			printf("FAIL: total number of cards in the deck and discard are incorrect.\n");
			printf("Prev: %i, Post: %i, Seed: %i\n",
					prev->deckCount[prev->whoseTurn] + prev->discardCount[prev->whoseTurn],
					state->deckCount[state->whoseTurn] + state->discardCount[state->whoseTurn],
					seed);
			err = 1;
		}

		if((prev->playedCardCount + 1) != state->playedCardCount)
		{
			/* if we fail to pass the test */
			printf("FAIL: total number of played cards was not properly incremented.\n");
			printf("Prev: %i, Post: %i, Seed: %i\n",
					prev->playedCardCount,
					state->playedCardCount,
					seed);
			err = 2;
		}

		if((preTreasure + 2) != postTreasure)
		{
			/* if we fail to pass the test */
			printf("FAIL: number of treasure cards in the players hand is incorrect.\n");
			printf("Prev: %i, Post: %i, Seed: %i\n",
					preTreasure + 2,
					postTreasure,
					seed);
			err = 3;
		}

		if(prev->handCount[prev->whoseTurn] + 2 != state->handCount[state->whoseTurn])
		{
			/* if we fail to pass the test */
			printf("FAIL: handCount was not properly incremented.\n");
			printf("Prev: %i, Post: %i, Seed: %i\n",
					prev->handCount[prev->whoseTurn],
					state->handCount[state->whoseTurn],
					seed);
			err = 4;
		}

		if(err == 0)
		{
			/* if passed print so */
			printf("PASSED.\n");
		}
	}
	/* display that we are done with our random testing */
	printf("\nAdventurer Card Random Testing Has Ended\n\n");
	return 0;
}