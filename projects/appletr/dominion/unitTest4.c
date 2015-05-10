#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>

int checkScoreFor(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	int r;
	
	r = scoreFor(p, post);
	
	int i;
	int score = 0;
	//score from hand
	for (i = 0; i < prePtr->handCount[p]; i++)
	{
		if (prePtr->hand[p][i] == curse) { score = score - 1; };
		if (prePtr->hand[p][i] == estate) { score = score + 1; };
		if (prePtr->hand[p][i] == duchy) { score = score + 3; };
		if (prePtr->hand[p][i] == province) { score = score + 6; };
		if (prePtr->hand[p][i] == great_hall) { score = score + 1; };
		if (prePtr->hand[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, prePtr) / 10 ); };
	}

	//score from discard
	for (i = 0; i < prePtr->discardCount[p]; i++)
	{
		if (prePtr->discard[p][i] == curse) { score = score - 1; };
		if (prePtr->discard[p][i] == estate) { score = score + 1; };
		if (prePtr->discard[p][i] == duchy) { score = score + 3; };
		if (prePtr->discard[p][i] == province) { score = score + 6; };
		if (prePtr->discard[p][i] == great_hall) { score = score + 1; };
		if (prePtr->discard[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, prePtr) / 10 ); };
	}

	//score from deck
	for (i = 0; i < prePtr->discardCount[p]; i++)
	{
		if (prePtr->deck[p][i] == curse) { score = score - 1; };
		if (prePtr->deck[p][i] == estate) { score = score + 1; };
		if (prePtr->deck[p][i] == duchy) { score = score + 3; };
		if (prePtr->deck[p][i] == province) { score = score + 6; };
		if (prePtr->deck[p][i] == great_hall) { score = score + 1; };
		if (prePtr->deck[p][i] == gardens) { score = score + ( fullDeckCount(p, 0, prePtr) / 10 ); };
	}
	
	if(r == score)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int i, n, p, r, breakLoop;
	breakLoop = 0;
	struct gameState G;

	printf ("Testing updateCoins.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 2000; n++) 
	{
		for (i = 0; i < sizeof(struct gameState); i++) 
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * MAX_PLAYERS);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.deck[p][i] = floor(Random() * 26);
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		r = checkScoreFor(p, &G);
		
		if(r == 0)
		{
			printf("Test failed\n");
			breakLoop = 1;
			break;
		}
	}

	if(!breakLoop)
	{
		printf ("checkScore TESTS OK\n");
	}

	return 0;
}