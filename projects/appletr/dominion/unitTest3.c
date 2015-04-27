#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#DEBUG 0

int checkShuffle(int p, struct gameState *post)
{
	int r;
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	r = shuffle(p, post); 
	assert (r == 0);
	
	assert(post->deckCount[p] == pre->deckCount[p]); //check that they contain the same number of cards
}

int main()
{
	int i, n, r, p, deckCount, discardCount, handCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
		   remodel, smithy, village, baron, great_hall};

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

	exit(0);
}