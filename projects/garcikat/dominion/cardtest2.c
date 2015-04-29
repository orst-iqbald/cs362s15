//testing adventure card
#include "dominion.c"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>

int checkAdventurer(int player, struct gameState *post)
{	
	int [] temphand;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r = adventurer(player, *post, temphand);
	//what adventurer is supposed to do
	int drawnCard;
	int coinCard = 0;

	while (coinCard < 2)
	{
		if (pre->deckCount[player]< 1)
		{
			shuffle(player, &pre);
		}
		pre.hand[player][pre.handCount[player]] = pre.deck[player][pre.deckCount[player]-1];
		pre.handCount[player]++;
		pre.deckCount[player]--;
		drawnCard = pre.hand[player][pre.handCount[player]-1];
		if ( drawnCard == copper || drawnCard == silver || drawnCard || gold)
		{
			coinCard++;
		}
		else
		{
			pre.discard[player][pre.discardCount[player]]= drawnCard;
			pre.discardCount[player]++;
			pre.handCount[player]--;
		}
	}
	//now check if post and pre have the same results
	//1: same hand count
	if(pre.handCount[player] == post->handCount[player])
	{
		//2: same discard pile count
		if(pre.discardCount[player] == post->discardCount[player])
		{
			//same deck count
			if(pre.deckCount[player] == post->deckCount[player])
			{
				//4: last two cards in hand are the same
				if(pre.hand[player][pre.handCount[player]-1] == post->hand[player][post->handCount[player]-1] &&  pre.hand[player][pre.handCount[player]-2] == post->hand[player][post->handCount[player]-2])
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
	int i, j;
	int seed 9999;
	//kingdomcards[10] = {adventurer, council_room, feast, gardens, 
	//mine, remodel, smithy, minion, baron, seahag};
	struct game G;
	SelectStream(2);
	PutSeed(seed);

	for( j = 0; j < 100; j++)
	{
		//Randomize gameState
		for( i =0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.numPlayers = 2;
		p = floor(Random() * G.numPlayers);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.coins = 0;
		//inserting adventurer card into first hand slot
		G.hand[p][0] = adventurer;
		int test = checkAdventurer(player, &G);
		if( test != 0)
		{
			printf("***** FAILED ***** checkAdventurer()\n");
		}
		else
		{
			printf("PASSED checkAdventurer()\n");
		}
	}
	return 0;

}
