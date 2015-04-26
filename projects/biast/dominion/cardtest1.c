/* -----------------------------------------------------------------------
 * Unit test for adventurer
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
	
	
	printf("\n\nTest 1: Drawing 2 treasures, all combinations\n");
	
	for(i = 4; i < 7; i++)
	{
		for(j = 4; j < 7; j++)
		{
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G);
			
			G.deckCount[player] = 2;
			G.handCount[player] = 5;
			for(m = 0; m < 5; m++)
			{
				G.hand[player][m] = estate;
			}
			
			G.hand[player][0] = adventurer;
			
			G.deck[player][0] = i;
			G.deck[player][1] = j;
			
			playCard(0, -1, -1, -1, &G);
			updateCoins(player, &G, 0);
			assert(G.coins == ((i + j) - 6));
		}		
	}
	
	printf("\nAll asserts passed, treasures successfully added to hand.\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	printf("\n\nTest 2: Drawing 2 treasures, all combinations, 100 non-treasure cards in front\n");
	
	for(i = 4; i < 7; i++)
	{
		for(j = 4; j < 7; j++)
		{
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G);
			
			G.deckCount[player] = 102;
			G.handCount[player] = 5;
			for(m = 0; m < 5; m++)
			{
				G.hand[player][m] = estate;
			}
			
			G.hand[player][0] = adventurer;
			
			for(m = 0; m < 100; m++)
			{
				G.deck[player][m] = estate;
			}
			
			G.deck[player][100] = i;
			G.deck[player][101] = j;
			
			playCard(0, -1, -1, -1, &G);
			updateCoins(player, &G, 0);
			assert(G.coins == ((i + j) - 6));
		}		
	}
	
	printf("\nAll asserts passed, treasures successfully added to hand.\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	

	printf("\n\nTest 3: Drawing 2 treasures, all combinations, 100 non-treasure cards in between\n");
	
	for(i = 4; i < 7; i++)
	{
		for(j = 4; j < 7; j++)
		{
			memset(&G, 23, sizeof(struct gameState));   // clear the game state
			initializeGame(numPlayer, k, seed, &G);
			
			G.deckCount[player] = 102;
			G.handCount[player] = 5;
			for(m = 0; m < 5; m++)
			{
				G.hand[player][m] = estate;
			}
			
			G.hand[player][0] = adventurer;
			
			for(m = 1; m < 101; m++)
			{
				G.deck[player][m] = estate;
			}
			
			G.deck[player][0] = i;
			G.deck[player][101] = j;
			
			playCard(0, -1, -1, -1, &G);
			updateCoins(player, &G, 0);
			assert(G.coins == ((i + j) - 6));
		}		
	}
	
	printf("\nAll asserts passed, treasures successfully added to hand.\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	printf("\n\nTest 4: Only 1 treasure in deck.\n");
	
	for(i = 4; i < 7; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		
		G.deckCount[player] = 50;
		G.handCount[player] = 5;
		for(m = 0; m < 5; m++)
		{
			G.hand[player][m] = estate;
		}
		
		G.hand[player][0] = adventurer;
		
		for(m = 0; m < 49; m++)
		{
			G.deck[player][m] = estate;
		}
		
		G.deck[player][49] = i;
		
		playCard(0, -1, -1, -1, &G);
		updateCoins(player, &G, 0);
		assert(G.coins == (i - 3));
	}
	
	printf("\nAll asserts passed, treasure successfully added to hand.\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	
	
	
	printf("\n\nTest 5: No treasures in deck.\n");
	

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	
	G.deckCount[player] = 50;
	G.handCount[player] = 5;
	for(m = 0; m < 5; m++)
	{
		G.hand[player][m] = estate;
	}
	
	G.hand[player][0] = adventurer;
	
	for(m = 0; m < 50; m++)
	{
		G.deck[player][m] = estate;
	}
			
	playCard(0, -1, -1, -1, &G);
	updateCoins(player, &G, 0);
	assert(G.coins ==  0);

	
	printf("\nAll asserts passed, no treasures found.\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
    return 0;
}
