#define TESTFUNCTION "shuffle()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
	
int main() {
    int i, j;
	int seedRandom = 1000;
    int numPlayers = 2;
	int cardsMoved = 0;
	
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seedRandom, &G);
	
	G.handCount[0] = 0;
	G.deckCount[0] = 12;
	G.deckCount[1] = 12;
	G.discardCount[0] = 0;

	printf("-------------------- Test: %s --------------------\n", TESTFUNCTION);

	printf("Initial 12 cards: ");
	for (j = 0; j < 12; j++)
	{
		G.deck[0][j] = j; // set initial deck to each of the 12 cards
		printf("%d ", j);
	}
	
	printf("Start shuffle:\n");
	for (i = 0; i < 50; i++) // do 50 iterations of shuffle
	{
		for (j = 0; j < 12; j++)
			G.deck[1][j] = G.deck[0][j];

		shuffle(0, &G);
		
		for (j = 0; j < 12; j++)
		{
			printf("%d ", G.deck[0][j]);
		}
		printf(" ");
		
		cardsMoved = 0;

		for (j = 0; j < 12; j++)
		{
			assert (G.deck[1][j] >= 0 && G.deck[1][j] <= 11);
			assert (G.deck[0][j] >= 0 && G.deck[0][j] <= 11);
			if (G.deck[1][j] != G.deck[0][j])
				cardsMoved++;
		}
		assert (G.handCount[0] == 0);
		assert (G.deckCount[0] == 12);

		printf("Number of cards moved: %d ", cardsMoved);
		if (cardsMoved == 0)
			printf("NO CARDS MOVED!\n");
		else
			printf("\n");
	}
	
    printf("\n-------------------- Test: %s completed --------------------\n\n", TESTFUNCTION);

    return 0;
}
