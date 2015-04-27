#define TESTFUNCTION "updateCoins()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
	
int main() {
    int i, j, m;
	int seedRandom = 1000;
    int numPlayers = 2;
	int quantCopper;
	int quantSilver;
	int quantGold;
	int bonusCoins;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seedRandom, &G);

	printf("-------------------- Test: %s --------------------\n", TESTFUNCTION);

	G.coins = 0;
	
	for (quantCopper = 0; quantCopper < 3; quantCopper++) // give 0-2 copper
	{
		for (i = 0; i < 3; i++)
		{
			if (i < quantCopper)
				G.hand[0][i] = 4;
			else
				G.hand[0][i] = 0;
		}
		
		for (quantSilver = 0; quantSilver < 3; quantSilver++) // give 0-2 silver
		{
			for (j = 0; j < 3; j++)
			{
				if (j < quantSilver)
					G.hand[0][j+3] = 5;
				else
					G.hand[0][j+3] = 0;
			}
			
			for (quantGold = 0; quantGold < 2; quantGold++) // give 0-1 gold
			{
				for (m = 0; m < 3; m++)
				{
					if (m < quantGold)
						G.hand[0][m+6] = 6;
					else
						G.hand[0][m+6] = 0;
				}
				
				for (bonusCoins = 0; bonusCoins < 3; bonusCoins++) // give 0-2 bonus coins
				{
						G.handCount[0] = 8;
						updateCoins(0, &G, bonusCoins);
						//assert (G.coins >= 0 && G.coins <= 11);
						//assert (G.handCount[0] == 8);
						//assert (G.coins == quantCopper + (quantSilver * 2) + (quantGold * 3) + bonusCoins);
						printf("Copper %d + Silver %d + Gold %d + Bonus %d = Total %d, ", 
								quantCopper,quantSilver,quantGold,bonusCoins,G.coins);
						if (G.coins == quantCopper + (quantSilver * 2) + (quantGold * 3) + bonusCoins)
							printf("which is expected.\n");
						else
							printf("which is NOT expected.\n");
				}
			}
		}
	}
	
    printf("-------------------- Test: %s completed --------------------\n\n", TESTFUNCTION);

    return 0;
}