/*------------------------------------------------------------------
 * Random Test: adventurer card
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *		 gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int main ()
{
	int kCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int i;
	int seed = 1000;
	SelectStream(1);
	PutSeed((long)seed);
	
	int test = 50;
	for(i = 0; i < test; i++)
	{
		int j, curPos, numPlayer;
		int preT = 0;
		int postT = 0;
		int error = 1;
		struct gameState *state = malloc(sizeof(struct gameState));
		struct gameState *pre = malloc(sizeof(struct gameState));
		seed  = floor((Random() * 1000 + 1));
		numPlayer = floor((Random() * 3) + 2);
		initializeGame(numPlayer, kCards, seed, state);
		
		state->whoseTurn = floor(Random() * numPlayer);
		state->handCount[state->whoseTurn] = floor(Random() * (MAX_HAND / 3));
		state->deckCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->discardCount[state->whoseTurn] = floor(Random() * (MAX_DECK / 3));
		state->playedCardCount = floor(Random() * 5);
		
		for(j = 0; j < state->handCount[state->whoseTurn]; j++)
		{
			state->hand[state->whoseTurn][j] = floor(Random() * 17);
		}
		
		for(j = 0; j < state->deckCount[state->whoseTurn]; j++)
		{
			state->deck[state->whoseTurn][j] = floor(Random() * 17);
		}
		
		for(j = 0; j < state->discardCount[state->whoseTurn]; j++)
		{
			state->discard[state->whoseTurn][j] = floor(Random() * 17);
		}
		
		curPos = floor(Random() * state->handCount[state->whoseTurn]);
		state->hand[state->whoseTurn][curPos] = adventurer;
		
		memcpy(pre, state, sizeof(struct gameState));
		adventurerCard(state, 0, curPos);
		
		for(j = 0; j < pre->handCount[pre->whoseTurn]; j++)
		{
			if(pre->hand[pre->whoseTurn][j] == copper || pre->hand[pre->whoseTurn][j] == silver || pre->hand[pre->whoseTurn][j] == gold)
			{
				preT++;
			}
		}
		
		for(j = 0; j < state->handCount[state->whoseTurn]; j++)
		{
			if(state->hand[state->whoseTurn][j] == copper || state->hand[state->whoseTurn][j] == silver || state->hand[state->whoseTurn][j] == gold)
			{
				postT++;
			}
		}
		
		if((pre->deckCount[pre->whoseTurn] + pre->discardCount[pre->whoseTurn]) - 2 != (state->deckCount[state->whoseTurn] + state->discardCount[state->whoseTurn]))
		{
			printf("Error: Deck and discard totals are incorrect\n");
			error = -1;
		}
		
		if((pre->playedCardCount + 1) != state->playedCardCount)
		{
			printf("Error: Card increment is incorrect\n");
			error = -1;
		}
		
		if((preT + 2) != postT)
		{
			printf("Error: Treasure card count is incorrect\n");
			error = -1;
		}
		if(error > 0)
		{
			printf("Passed Test\n");
		}
	}
	printf("End of Random Testing");
	return 0;
}