//testing isGameOver()
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <rngs.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main()
{
	int i, test;
	int seed = 9999;
	srand(time(NULL));
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, smithy, remodel, great_hall, seahag, minion, baron, feast, gardens, salvager};
	struct gameState G;
	initializeGame( numPlayers, kingdomCards, seed, &G);

	//Testing when SupplyCount[province] = 0 
	for ( i =0; i < 10; i++)
	{
		int randomNum = rand() % 2;
		G.supplyCount[province] == randonNum;
		test = isGameOver(&G);
		if ( G.supplyCount[province] == 0 && test == 1)
		{
			printf("Passed isGameOver() : changed province\n");
		}
		else if(G.supplyCount[province] != 0 && test == 0)
		{
			printf("Passed isGameOver() : changed province\n");
		}
		else
		{
			printf("***** FAILED ****** isGameOver() : changed province\n");
		}
	}
	//testing when 3 stacks of supply count are 0
	for ( i =0; i < 10; i++)
	{
		int rand1, rand2, rand3;
		do{
			rand1 = rand() % 25;
			rand2 = rand() % 25;
			rand3 = rand() % 25;
		}while (rand1 != rand2 && rand1 != rand3 && rand2 != rand3)
		G.supplyCount[rand1] = 0;
		G.supplyCount[rand2] = 0;
		G.supplyCount[rand3] = 0;
		test = isGameOver(&G);
		if(test != 1)
		{
			printf("***** FAILED isGameover(): changed 3 stacks to 0\n");
		}
		else
		{
			printf("Passed isGameOver: changed 3 stacks to 0\n");
		}
	}

	return 0;

}

