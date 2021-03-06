#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>
#include <stdlib.h> 

int checkAdventurer(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	int card, choice1, choice2, choice3, handPos;
	card = adventurer;
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	int* bonus = (int*) malloc(sizeof(int));
	*bonus = 0;
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	//count treasure cards prior to adventurer
	int i;
	int preTreasure = 0;
	for(i = 0; i < prePtr->handCount[p]; i++)
	{
		if (prePtr->hand[p][i] == copper || prePtr->hand[p][i] == silver || prePtr->hand[p][i] == gold)
		{
			preTreasure++;
		}
	}
	
	int postTreasure = 0;
	for(i = 0; i < post->handCount[p]; i++)
	{
		if (prePtr->hand[p][i] == copper || prePtr->hand[p][i] == silver || prePtr->hand[p][i] == gold)
		{
			postTreasure++;
		}
	}
	free(bonus);

	if((preTreasure + 2) == postTreasure) //make sure we have two new treasure cards
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
	breakLoop = 1;
	
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
		G.numActions = 1;
		G.numBuys = 1;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.deck[p][i] = floor(Random() * 26); //fill deck with random cards
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.discard[p][i] = floor(Random() * 26);
		}
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		r = checkAdventurer(p, &G);
		if(r == 0)
		{
			printf("Test failed\n");
			breakLoop = 1;
			break;
		}
	}
	if(!breakLoop)
	{
		printf ("Adventurer TESTS OK\n");
	}

	return 0;
}