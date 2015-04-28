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
	assert (r == 0);
	
	assert(post->deckCount[p] == prePtr->deckCount[p]); //check that they contain the same number of cards
	return 0;
}

int main()
{
	int i, n, p;

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
		
		checkShuffle(p, &G);
	}

	printf ("ALL TESTS OK\n");

	return 0;
}