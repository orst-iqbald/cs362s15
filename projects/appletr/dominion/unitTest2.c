#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#DEBUG 0

int checkDrawCard(int p, struct gameState *post)
{
	struct gameState pre;
	struct gameState* prePtr = &pre;
	memcpy (prePtr, post, sizeof(struct gameState));
	int r;
	r = drawCard(p, post);

	int count;
	int deckCounter;
	if (prePtr->deckCount[p] <= 0)
	{
		//Deck is empty

		//Step 1 Shuffle the discard pile back into a deck
		int i;
		//Move discard to deck
		for (i = 0; i < prePtr->discardCount[p];i++)
		{
			prePtr->deck[p][i] = prePtr->discard[p][i];
			prePtr->discard[p][i] = -1;
		}

		prePtr->deckCount[p] = prePtr->discardCount[p];
		prePtr->discardCount[p] = 0;//Reset discard

		//Shufffle the deck
		shuffle(p, prePtr);//Shuffle the deck up and make it so that we can draw

		if (DEBUG)
		{//Debug statements
			printf("Deck count now: %d\n", prePtr->deckCount[p]);
		}

		prePtr->discardCount[p] = 0;

		//Step 2 Draw Card
		count = prePtr->handCount[p];//Get current player's hand count

		if (DEBUG)
		{//Debug statements
			printf("Current hand count: %d\n", count);
		}

		deckCounter = prePtr->deckCount[p];//Create a holder for the deck count

		prePtr->hand[p][count] = prePtr->deck[p][deckCounter - 1];//Add card to hand
		prePtr->deckCount[p]--;
		prePtr->handCount[p]++;//Increment hand count
	}

	else
	{
		int count = prePtr->handCount[p];//Get current hand count for player
		int deckCounter;
		if (DEBUG)
		{//Debug statements
			printf("Current hand count: %d\n", count);
		}

		deckCounter = prePtr->deckCount[p];//Create holder for the deck count
		prePtr->hand[p][count] = prePtr->deck[p][deckCounter - 1];//Add card to the hand
		prePtr->deckCount[p]--;
		prePtr->handCount[p]++;//Increment hand count
	}
	
	assert (r == 0);
	assert(memcmp(prePtr, post, sizeof(struct gameState)) == 0);
}

int main()
{
	int i, n, r, p, deckCount, discardCount, handCount;

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
		//fill deck with random cards
		for(i = 0; i < G.deckCount[p]; i++)
		{
			G.deck[p][i] = floor(Random() * 26);
		}
		
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		// draw a random number of cards
		for(i = 0; i < G.handCount[p]; i++)
		{
			checkDrawCard(p, &G);
		}
	}

	printf ("ALL TESTS OK\n");

	exit(0);
}