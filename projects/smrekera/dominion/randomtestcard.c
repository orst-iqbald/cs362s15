/*------------------------------------------------------------------
 * Random Test: smithy card
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard randomtestcard.c -g dominion.o rngs.o $(CFLAGS)
 *------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int main()
{
	struct gameState state;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	SelectStream(1);
	PutSeed((long)seed);
	int i, j, curPos, numPlayer, preT, postT, preHcount, postHcount;
	int error = 1;
	printf("Starting Smithy Random Tests\n");
	for(i = 0; i < 200; i++)
	{
		numPlayer = ((rand()% 3) + 2);
		int rPlayer = (rand() % numPlayer);
		curPos = 0;
		initializeGame(numPlayer, kCards, seed, &state);
		preHcount = 0;
		preT = 0;
		postHcount = 0;
		postT = 0;
		
		for(j = 0; j < state.handCount[rPlayer]; j++)
		{
			if(state.hand[rPlayer][j] == copper || state.hand[rPlayer][j] == silver || state.hand[rPlayer][j] == gold)
				preT++;
			else
				curPos = j;
			preHcount = j +1;
		}
		smithyCard(&state, curPos, rPlayer);
		
		for(j = 0; j < state.handCount[rPlayer]; j++)
		{
			if(state.hand[rPlayer][j] == copper || state.hand[rPlayer][j] == silver || state.hand[rPlayer][j] == gold)
			{
				postT++;
				postHcount = j +1;
			}
		}
		if(preT > postT)
		{
			printf("Error: Treasure card count is incorrect\n");
			error = -1;
		}
		
		if((preHcount + 3) != postHcount)
		{
			printf("Error: Hand card counts are incorrect\n");
			error = -1;
		}
		
		if(error > 0)
			printf("All test passed");
		
		printf("End of Smithy Random Test\n");
		return 0;
	}
	return 0;
}