//tests update coins

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>

int checkUpdateCoin(int p, struct gameState *post, int bonus)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	int r;
	int i;
	r = updateCoins(p, post, bonus);
	
	for (i = 0; i < (prePtr->handCount)[p]; i++)
    {
		if (prePtr->hand[p][i] == copper)
		{
			prePtr->coins += 1;
		}
		else if (prePtr->hand[p][i] == silver)
		{
			prePtr->coins += 2;
		}
		else if (prePtr->hand[p][i] == gold)
		{
			prePtr->coins += 3;
		}	
    }	

	//add bonus
	prePtr->coins += bonus;

	if (r != 0)
	{
		return -1;
	}
	else if (memcmp(prePtr, post, sizeof(struct gameState)) == 0)
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
	int i, r, n, p, bonus, breakLoop;
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
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		
		bonus = floor(Random() * 10);
		
		r = checkUpdateCoin(p, &G, bonus);
		if(r == -1)
		{
			printf("updateCoin failed with function error\n");
			breakLoop = 1;
			break;
		}
		else if(r == 0)
		{
			printf("updateCoin failed with mismatched structures\n");
			breakLoop = 1;
			break;
		}
	}
	if(!breakLoop)
	{
		printf ("UpdateCoin TESTS OK\n");
	}
	return 0;
}