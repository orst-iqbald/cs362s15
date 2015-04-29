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
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	int* bonus = (int*) malloc(sizeof(int));
	*bonus = 0;
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	//check that hand has increased by 3
	assert(post->handCount[p] == (prePtr->handCount[p] + 3));

	//check that the deck has decreased by 3
	assert(post->deckCount[p] == (prePtr->deckCount[p] - 3));
	free(bonus);
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
		G.numActions = 1;
		G.numBuys = 1;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.deck[p][i] = floor(Random() * 26); //fill deck with random cards
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * 26); //fill hand with random cards
		}
		checkSmithy(p, &G);
	}
	printf ("ALL TESTS OK\n");

	return 0;
}