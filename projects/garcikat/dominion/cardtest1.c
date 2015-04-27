//testing smihty card effect
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <rngs.h>
//dont forget to add to dominion.h ->functions i made last week!
//give credit to betterTestDrawCard.c
int checkSmithy(int player, struct gameState *post, int handpos)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	//testing smithy fucntion
	int r = smithy(player, post, handpos);
	
	//What smithy function is supposed to do.
	int k;
	for( k = 0; k < 3; k++)
	{
		drawCard(player,&pre);
	}
	discardCard(handpos, player, &pre, 0)

	//Check if the two gameStates are the same
	if(pre.discardCount[player] == post->discardCount[p])
	{
		if(pre.handCount[player] == post->handCOunt[player])
		{
			return 0;
		}
	}
	return -1;

}


int main()
{
	//Set up game
	int i, j;
	int seed = 9999;
	//int numPlayer = 2;
	//kingdomCards[10] = {adventurer, council_room, feast, 
	//gardens, mine, remodel, smithy, minion, seahag, baron};
	struct gameState G;
	//intializeGame(numPlayer, kingdomCards, seed, &G);
	SelectStream(2);	
	PutSeed(seed);

	for (j = 0; j < 100; j++)
	{
		//Randomize gameState
		for ( i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		//random player and player's hand, deck and discard pile
		G.numPlayers = 2;
		p = floor(Random() * 2)
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		
		//since I am testing the Smithy card I am inserting it into the 
		// 0 hand postion
		G.hand[p][0] = smithy;
		int test = checkSmithy(p, &G, 0);
		if (test != 0 )
		{
			printf("checkSmithy() FAILED\n");
		}
		else{printf("checkSmithy() PASSED\n");}
	}
	return 0;
}
