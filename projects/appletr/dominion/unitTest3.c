#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>

int checkShuffle(int p, struct gameState *post)
{
	int r;
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	r = shuffle(p, post); 
	if (r != 0)
	{
		return -1;
	}
	else if(post->deckCount[p] == prePtr->deckCount[p])
	{
		return 1; //check that they contain the same number of cards
	}
	else
	{
		return 0;
	}
}

int main()
{
	int i, n, p, r, breakLoop;

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
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.discard[p][i] = floor(Random() * 26);
		}
		G.handCount[p] = floor(Random() * MAX_HAND);
		
		r = checkShuffle(p, &G);
		if(r == -1)
		{
			printf("drawCard failed with function error\n");
			breakLoop = 1;
			break;
		}
		else if(r == 0)
		{
			printf("updateCoin failed with number of cards in hand\n");
			breakLoop = 1;
			break;
		}
	}

	if(!breakLoop)
	{
		printf ("Shuffle TESTS OK\n");
	}
	return 0;
}