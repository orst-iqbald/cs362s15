//testing updateCoin()
#include "dominion.h"
#include "dominion_helpers.h"
#include <strings.h>
#include <rngs.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int testCoin, totalCoin, i, j;
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, smithy, feast, baron, seahag, minion, remodel, great_hall, gardens, salvager};
	int gameCoins = {copper, silver, gold};
	int seed = 9999;
	srand(time(NULL));
	struct gameState G;
	initializeGame(numPlayer, kingdomCards, seed, &G);
	for (i =0; i < 20; i++)
	{
		int p = rand() % numPlayers;
		G.handCount[p] = MAX_HAND;
		for (j =0; j < MAX_HAND; j++)
		{
			totalCoin = 0;
			testCoin = gameCoins[rand() % 3];
			G.hand[p][j] = testCoin;
			if ( testCoin == copper)
			{
				totalCoin = totalCoin + 1;
			}
			else if (testCoin == silver )
			{
				totalCoin = totalCoin + 2;
			}
			else if ( testCoin == gold )
			{
				totalCoin = totalCoin + 3;
			}		

		}
		int coinTest = updateCoins(p, &G, 0);
		if(coinTest != totalCoin)
		{
			printf("***** FAILED updateCoins()\n");
		}
		else
		{
			printf("PASSED updateCoins()\n");
		}
	}
	return 0;
}
