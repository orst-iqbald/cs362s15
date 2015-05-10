//testing fullDeckCount
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <rngs.h>

int main()
{
	int i, j, rand1, rand2, rand3, testTotal, testDeck;
	srand(time(NULL));
	int numPlayers = 0;
	int seed = 9999;
	int kingdomCards = {adventurer, smithy, feast, baron, seahag, minion, remodel, great_hall, gardens, salvager};
	struct gameState G;
	initializeGame(numPlayers, kingdomCards, seed, &G);
	
	for ( i =0; i < numPlayers; i++)
	{
		testTotal = 0;
		rand1 = rand() % MAX_DECK;
		rand2 = rand() % MAX_DECK;
		rand3 = rand % MAX_HAND;
		G.deckCount[i] = rand1;
		G.discardCount[i] = rand2;
		G.handCount[i] - rand3;

		testTotal = rand1 + rand2 + rand3;
		testDeck = fullDeckCount(i, 0, &G);
		if ( testDeck != testTotal )
		{
			printf("***** FAILED ***** fullDeckCount()\n");
		}
		else
		{
			printf("PASSED fullDeckCount()\n");
		}
	}
	return 0;

}
