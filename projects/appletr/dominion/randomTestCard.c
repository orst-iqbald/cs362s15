#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>
#include <stdlib.h> 

int checkSmithy(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	int card, choice1, choice2, choice3, handPos;
	card = smithy;
	choice1 = 1;
	choice2 = 2;
	choice3 = 3;
	handPos = 0;
	int* bonus = (int*) malloc(sizeof(int));
	*bonus = 0;
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);

	free(bonus);
	
	//check that hand has increased by 3
	if (post->handCount[p] == (prePtr->handCount[p] + 3))
	{
		//check that the deck has decreased by 3
		if(post->deckCount[p] == (prePtr->deckCount[p] - 3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int main()
{
	int i, n, p, r, breakLoop;
	int* k;
	breakLoop = 0;
	
	struct gameState G;

	printf("Testing checkSmithy.\n");

	printf("RANDOM TESTS.\n");

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
			G.discard[p][i] = floor(Random() * 26); //fill discard with random cards
		}
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			//drawCard(p, &G);
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		r = checkSmithy(p, &G);

		if(r == 0)
		{
			printf("Test failed\n");
			breakLoop = 1;
			break;
		}
	}
	
	if(!breakLoop)
	{
		printf ("Smithy TESTS OK\n");
	}

	return 0;
}