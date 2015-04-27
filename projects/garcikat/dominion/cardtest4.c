//testing great_hall card
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <rngs.h>

int checkGreatHall(int player, struct gameState *post)
{
	int old_numActions = post->numActions;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r = great_hall(player, post, 0);
	//what great_hall is supposed to do
	if(pre.deckCount[player] < 1)
	{
		shuffle( player, &pre);
	}
	pre.hand[player][pre.handCount[player]] = pre.deck[player][pre.deckCount[player]-1];
	pre.handCount[player]++;
	pre.deckCount[player]--;
	pre.numActions++:
	discard(0, player, &pre, 0);

	// check if post and pre are the same
	if( pre.deckCount[player] == post->deckCount[player])
	{
		if (pre.handCount[player] == post->handCount[player])
		{
			if(pre.dicardCount[player] == post->discardCount[player])
			{	if(pre.numActions == post->numActions)
				{
					return 0;
				}
			}
		}
	}
	return -1;
}

int main()
{
	//set up game
	int i, j, p;
	int seed = 9999;
	int numPlayers = 2;
	
	SelectStream(2);
	PutSeed(seed);
	for (j = 0; j < 100; j++)
	{
		for (i =0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.numPlayers = numPlayers;
		p = floor(Random() * numPlayers);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.numActions = floor(Random() * 3);
		G.hand[p][0] = great_hall;
		int test = checkGreat_Hall(p, &G);
		if ( test != 0 )
		{
			printf("***** FAILED ***** checkGreat_Hall()\n");
		}
		else
		{
			printf("PASSED checkGreat_Hall()\n");
		}
	}
	
	return 0;
}
