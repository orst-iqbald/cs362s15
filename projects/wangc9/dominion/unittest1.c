#define TESTFUNCTION "buyCard()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
	
int main() {
    int seedRandom = 1000;
    int numPlayers = 2;
	int quantBuys;
	int cardsInStack;
	int numCoins;
	int supplyPos;
	int numberBuys;
	int numberStackCards;
	int numberCoins;
	struct gameState G;
	int success;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	char* cardName[] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse", "sea_hag", "tribute", "smithy", "council_room"};
	
	initializeGame(numPlayers, k, seedRandom, &G);

	printf("-------------------- Test: %s --------------------\n", TESTFUNCTION);

	for (quantBuys = 0; quantBuys < 2; quantBuys++) // test number of buys 0-1
	{
		G.numBuys = numberBuys = quantBuys;
		for (cardsInStack = 0; cardsInStack < 2; cardsInStack++) // test available cards 0-1
		{
			for (numCoins = 3; numCoins <= 6; numCoins++) // test available coins 3-6
			{
				G.coins = numberCoins = numCoins;
				for (supplyPos = 0; supplyPos <= 9; supplyPos += 4) // test buy 3 cards
				{
					G.supplyCount[supplyPos+7] = numberStackCards = cardsInStack;
					printf("Attempt to buy %*s with %*d coins, %d left buys, and %*d left in stack\n", 10, cardName[supplyPos], 2, G.coins, G.numBuys, 2, G.supplyCount[supplyPos+7]);
					if (buyCard(supplyPos+7, &G) == -1)
					{
						success = 0;
						printf("buyCard() failed, ");
					}
					else
					{
						assert (numberBuys == G.numBuys + 1);
						assert (numberStackCards == G.supplyCount[supplyPos+7] + 1);
						assert (numberCoins == getCost(supplyPos+7) + G.coins);
						G.numBuys++;
						G.coins += getCost(supplyPos+7);
						G.supplyCount[supplyPos+7]++;
						success = 1;
						printf("buyCard() succeeded, ");
					}
					if (((getCost(supplyPos+7) > numCoins) || (cardsInStack < 1) || (quantBuys == 0)) && success == 0)
						printf("which is expected.\n");
					else if (((getCost(supplyPos+7) > numCoins) || (cardsInStack < 1) || (quantBuys == 0)) && success == 1)
						printf("which is NOT expected.\n");
					else if (((getCost(supplyPos+7) <= numCoins) || (cardsInStack >= 1) || (quantBuys > 0)) && success == 1)
						printf("which is expected.\n");
					else if (((getCost(supplyPos+7) <= numCoins) || (cardsInStack >= 1) || (quantBuys > 0)) && success == 0)
						printf("which is NOT expected.\n");

				}
			}
		}
	}

    printf("-------------------- Test: %s completed --------------------\n\n", TESTFUNCTION);

    return 0;
}
