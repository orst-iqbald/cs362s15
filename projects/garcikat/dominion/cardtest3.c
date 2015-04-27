//testing seahag card
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <rngs.h>

int checkSeahag(int player, struct gameState *post)
{
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	int r = seahag(player, post);
	
	//what seahag is supposed to do
	int k;
	for ( k = 0; k < pre.numPlayers; k++)
	{
		if (k != player)
		{
			if (pre.deckCount[k] < 1)
			{
				shuffle(k, &pre);
			}
			pre.discard[k][pre.discardCount[k]] = pre.deck[k][pre.deckCount[k]-1];
			pre.discardCount[k]++;
			pre.deck[player][pre.deckCount[k]-1] = curse;
		}
	}
	//now check if they are the same
	for (k = 0; k < pre.numPlayers; k++)
	{
		if ( k != player)
		{
			if (post->deck[k][post->deckCount[k]-1] != curse && pre.discard[k][pre.discardCount[k]-1] != post->discard[k][post->discardCount[k]-1])
			{
				return -1;
			}
		}
		if ( pre.deckCount[k] != post->deckCount[k] || pre.discardCount[k] == post->discardCount[k] )
		{
			return -1;
		}
	}
	return 0;
}

int main()
{
	//set up game
	struct gameState G;
	int seed = 9999;
	int numPlayers = 2;
	int i;
	//kingdomCards[10] = {adventurer, smithy, remodel, seahag, baron, minion,
	//		mine, gardens, feast, council_room};
	//intializeGame(numPlayers, kingdomCards, seed, &G);
	SelectStream(2);
	PutSeed(seed);

	for (j = 0; j < 100; j++)
	{
		for ( i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.numPlayers = numPlayers;
		for (i = 0; i < numPlayers; i++)
		{
			G.deckCount[i] = floor(Random() * MAX_DECK);
			G.discardCount[i] = floor(Random() * MAX_DECK);
			G.handCount[i] = floor(Random() * MAX_HAND);
		}
		player = floor(Random() * numPlayers);
		int test = checkSeahag(player, &G);
		if (test != 0)
		{
			printf("***** FAILED *****  checkSeahag()\n");
		}
		else
		{
			printf("PASSED checkSeahag()\n");
		}

	return 0;
}
