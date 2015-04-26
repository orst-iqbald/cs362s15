/* -----------------------------------------------------------------------
 * Unit test for isGameOver
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int errors = 0;
    int i, j, m, n;
    int seed = 50;
    int numPlayer = 2;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int player = 0;
	
	
	printf("\nTest 1: Depleting 1 non-province pile.\n");
	
	errors = 0;
	for(i = 0; i < 25; i++) // 25 to loop over all possible cards,
							// including those not in the game which are set to -1
	{
		if(i != province)
		{
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G);
			G.supplyCount[i] = 0;
			if(isGameOver(&G) == 1)
			{
				printf("i = %d\n", i);
				printf("ERROR: Game considered to be over.\n");
				errors++;
			}
		}
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 2: Depleting 2 non-province piles.\n");
	
	errors = 0;
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			if(i != j)
			{
				if((i != province) && (j != province))
				{
					memset(&G, 23, sizeof(struct gameState));   // clear the game state
					initializeGame(numPlayer, k, seed, &G);
					G.supplyCount[i] = 0;
					G.supplyCount[j] = 0;
					if(isGameOver(&G) == 1)
					{
						printf("i = %d, j = %d\n", i, j);
						printf("ERROR: Game considered to be over\n");
						errors++;
					}
				}
			}
		}
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 3: Depleting 3 non-province piles.\n");
	
	errors = 0;
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			for(m = 0; m < 25; m++)
			{
				if((i != j) && (i != m) && (j != m))
				{
					if((i != province) && (j != province) && (m != province))
					{
						memset(&G, 23, sizeof(struct gameState));   // clear the game state
						initializeGame(numPlayer, k, seed, &G);
						G.supplyCount[i] = 0;
						G.supplyCount[j] = 0;
						G.supplyCount[m] = 0;
						if(isGameOver(&G) != 1)
						{
							printf("i = %d, j = %d, m = %d\n", i, j, m);
							printf("ERROR: Game not considered to be over\n");
							errors++;
						}
					}
				}
			}
		}
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);

	printf("Test 4: Depleting 4 non-province piles.\n");
	
	errors = 0;
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			for(m = 0; m < 25; m++)
			{
				for(n = 0; n < 25; n++)
				{
					if((i != j) && (i != m) && (i != n) && (j != m) && (j != n) && (m != n))
					{
						if((i != province) && (j != province) && (m != province) && (n != province))
						{
							memset(&G, 23, sizeof(struct gameState));   // clear the game state
							initializeGame(numPlayer, k, seed, &G);
							G.supplyCount[i] = 0;
							G.supplyCount[j] = 0;
							G.supplyCount[m] = 0;
							if(isGameOver(&G) != 1)
							{
								printf("i = %d, j = %d, m = %d\n, n = %d", i, j, m, n);
								printf("ERROR: Game not considered to be over\n");
								errors++;
							}
						}
					}
				}
			}
		}
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 5: Depleting the province pile.\n");
	
	errors = 0;
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	G.supplyCount[province] = 0;
	if(isGameOver(&G) != 1)
	{
		printf("ERROR: Game not considered to be over.\n");
		errors++;
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	printf("Test 6: Depleting all piles.\n");
	errors = 0;
	for(i = 0; i < 25; i++)
	{
		G.supplyCount[i] = 0;
	}
	if(isGameOver(&G) != 1)
	{
		printf("ERROR: Game not considered to be over.\n");
		errors++;
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);

    return 0;
}
