/* -----------------------------------------------------------------------
 * Unit test for smithy
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
	int counter;
	int coinCount;
	
	
	printf("\n\nTest 1: Drawing 3 cards, all combinations\n");
	errors = 0;
	
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			for(m = 0; m < 25; m++)
			{
				memset(&G, 23, sizeof(struct gameState));   // clear the game state
				initializeGame(numPlayer, k, seed, &G);
				coinCount = 0;
				
				G.deckCount[player] = 50;
				G.handCount[player] = 5;
				for(n = 0; n < 5; n++)
				{
					G.hand[player][n] = copper;
				}
				
				G.hand[player][0] = smithy;
				
				G.deck[player][0] = i;
				G.deck[player][1] = j;
				G.deck[player][2] = m;
				
				playCard(0, -1, -1, -1, &G);
				
				for(n = 0; n < G.handCount[player]; n++)
				{
					if(G.hand[player][n] == 4)
					{
						coinCount += 1;
					}
					if(G.hand[player][n] == 5)
					{
						coinCount += 2;
					}	
					if(G.hand[player][n] == 6)
					{
						coinCount += 3;
					}					
				}
				
				if(G.handCount[player] != 7)
				{
					printf("ERROR: Incorrect number of cards in hand.\n");
					errors++;
				}
				if(G.coins != coinCount)
				{
					printf("ERROR: Coins miscalculated.\n");
					printf("Correct result: %d\n", coinCount);
					printf("Calculated result: %d\n", G.coins);
					errors++;
				}
			}
		}		
	}
		
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 2: Only 2 cards in deck, all combinations\n");
	errors = 0;
	
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 25; j++)
		{
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G);
			coinCount = 0;
			
			G.deckCount[player] = 2;
			G.handCount[player] = 5;
			for(n = 0; n < 5; n++)
			{
				G.hand[player][n] = copper;
			}
			
			G.hand[player][0] = smithy;
			
			G.deck[player][0] = i;
			G.deck[player][1] = j;
			
			playCard(0, -1, -1, -1, &G);
			
			for(n = 0; n < G.handCount[player]; n++)
			{
				if(G.hand[player][n] == 4)
				{
					coinCount += 1;
				}
				if(G.hand[player][n] == 5)
				{
					coinCount += 2;
				}	
				if(G.hand[player][n] == 6)
				{
					coinCount += 3;
				}					
			}
			
			if(G.handCount[player] != 6)
			{
				printf("ERROR: Incorrect number of cards in hand.\n");
				errors++;
			}
			if(G.coins != coinCount)
			{
				printf("ERROR: Coins miscalculated.\n");
				printf("Correct result: %d\n", coinCount);
				printf("Calculated result: %d\n", G.coins);
				errors++;
			}
		}		
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);


	printf("Test 3: Only 1 cards in deck, all possible cards\n");
	errors = 0;
	
	for(i = 0; i < 25; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		coinCount = 0;
		
		G.deckCount[player] = 1;
		G.handCount[player] = 5;
		for(n = 0; n < 5; n++)
		{
			G.hand[player][n] = copper;
		}
		
		G.hand[player][0] = smithy;
		
		G.deck[player][0] = i;
		
		playCard(0, -1, -1, -1, &G);
		
		for(n = 0; n < G.handCount[player]; n++)
		{
			if(G.hand[player][n] == 4)
			{
				coinCount += 1;
			}
			if(G.hand[player][n] == 5)
			{
				coinCount += 2;
			}	
			if(G.hand[player][n] == 6)
			{
				coinCount += 3;
			}					
		}
		
		if(G.handCount[player] != 5)
		{
			printf("ERROR: Incorrect number of cards in hand.\n");
			errors++;
		}
		if(G.coins != coinCount)
		{
			printf("ERROR: Coins miscalculated.\n");
			printf("Correct result: %d\n", coinCount);
			printf("Calculated result: %d\n", G.coins);
			errors++;
		}		
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);

	
	printf("Test 4: No cards in deck or discard\n");
	errors = 0;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	coinCount = 0;
	
	G.deckCount[player] = 1;
	G.handCount[player] = 5;
	for(n = 0; n < 5; n++)
	{
		G.hand[player][n] = copper;
	}
	
	G.hand[player][0] = smithy;
	
	G.deck[player][0] = i;
	
	playCard(0, -1, -1, -1, &G);
	
	for(n = 0; n < G.handCount[player]; n++)
	{
		if(G.hand[player][n] == 4)
		{
			coinCount += 1;
		}
		if(G.hand[player][n] == 5)
		{
			coinCount += 2;
		}	
		if(G.hand[player][n] == 6)
		{
			coinCount += 3;
		}					
	}
	
	if(G.handCount[player] != 5)
	{
		printf("ERROR: Incorrect number of cards in hand.\n");
		errors++;
	}
	if(G.coins != coinCount)
	{
		printf("ERROR: Coins miscalculated.\n");
		printf("Correct result: %d\n", coinCount);
		printf("Calculated result: %d\n", G.coins);
		errors++;
	}		

	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);

	
    return 0;
}
