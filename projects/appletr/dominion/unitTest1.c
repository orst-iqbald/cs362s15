//tests update coins

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int checkUpdateCoin(int p, struct gameState *post, int bonus)
{
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	int r;
	int i;
	r = updateCoins(p, post, bonus);
	
	for (i = 0; i < pre->handCount[p]; i++)
    {
		if ([pre->hand[p][i] == copper)
		{
			pre->coins += 1;
		}
		else if (pre->hand[p][i] == silver)
		{
			pre->coins += 2;
		}
		else if (pre->hand[p][i] == gold)
		{
			pre->coins += 3;
		}	
    }	

	//add bonus
	pre->coins += bonus;

	assert (r == 0);
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);	
	
	return 0;
}

int main()
{
	int i, n, r, p, deckCount, discardCount, handCount, bonus;

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
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		
		bonus = floor(Random() * 10);
		
		checkUpdateCoin(p, &G, bonus);
	}

	printf ("ALL TESTS OK\n");

	exit(0);
}