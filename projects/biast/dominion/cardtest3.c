/* -----------------------------------------------------------------------
 * Unit test for great hall
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
	
	
	printf("\n\nTest 1: Playing the great hall\n");
	errors = 0;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	coinCount = 0;
	
	G.deckCount[player] = 5;
	G.handCount[player] = 5;
	for(i = 0; i < 5; i++)
	{
		G.hand[player][i] = copper;
	}
	
	G.hand[player][0] = great_hall;
	
	for(i = 0; i < 5; i++)
	{
		G.deck[player][i] = copper;
	}
	
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
