#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <string.h>
#include <math.h>
#include <stdlib.h> 

int checkCouncilRoom(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	
	int card, choice1, choice2, choice3, handPos;
	card = council_room;
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 0;
	int* bonus = (int*) malloc(sizeof(int));
	*bonus = 0;
	cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	free(bonus);
	if (post->handCount[p] != (prePtr->handCount[p] + 4))
	{
		return 0; //verify we have 4 more cards in the hand
	}
	//printf("Player has 4 more cards in hand");
	int i; //verify that everyone else drew a card
	for(i = 0; i < post->numPlayers; i++)
	{
		if(i != p)
		{
			if(post->handCount[i] != (prePtr->handCount[i] + 1))
			{
				return 0;
			}
		}
	}
	//printf("Everyone else drew one card");
	
	//verify that the player has one more buy
	if(post->numBuys != (prePtr->numBuys + 1))
	{
		return 0; //verify we have 4 more cards in the hand
	}
	//printf("Player has one more buy");
	
	return 1;
}

int main()
{
	int i, j, n, p, r, breakLoop;
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
		G.numPlayers = floor(Random() * 4);
		p = floor(Random() * G.numPlayers);
		G.numActions = 1;
		G.numBuys = 1;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		for(j = 0; j < G.numPlayers; j++)
		{
			for(i = 0; i < G.deckCount[j]; i++)
			{
				G.deck[j][i] = floor(Random() * 26); //fill deck with random cards
			}
		}
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.discard[p][i] = floor(Random() * 26);
		}
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(j = 0; j < G.numPlayers; j++)
		{
			for(i = 0; i < G.handCount[j]; i++)
			{
				G.hand[j][i] = floor(Random() * 26); //fill hand with random cards
			}
		}
		r = checkCouncilRoom(p, &G);
		if (r == 0)
		{
			printf("Test failed\n");
			breakLoop = 1;
			break;
		}
	}
	
	if(!breakLoop)
	{
		printf ("CouncilRoom Tests OK\n");
	}
	
	return 0;
}

