/* -----------------------------------------------------------------------
 * Unit test for getWinners
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
    int numPlayer = 4;
    int maxBonus = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int estateCount = 0;
	int copperCount = 0;
	int counter;
	int players[MAX_PLAYERS];
	int temp;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	
	printf("\n\nTest 1: Player 1 wins.\n");
	for(i = 0; i < 5; i++)
	{
		G.hand[0][i] = province;
		G.deck[0][i] = copper;
	}
	counter = 0;
	for(i = 0; i < 5; i++)
	{
		if(G.hand[0][i] == province)
			counter++;
		assert(G.deck[0][i] == copper);
	}
	assert(counter == 5);
	for(i = 1; i < 4; i++)
	{
		counter = 0;
		for(j = 0; j < 10; j++)
		{
			if(G.deck[i][j] == estate)
				counter++;
		}
		assert(counter == 3);
	}
	printf("\nAsserts passed.\n");
	printf("Player 1 has 5 provinces and 5 coppers.\n");
	printf("All others have 3 estates.\n");
	
	getWinners(players, &G);
	if(players[0] != 1)
	{
		printf("ERROR: Player 1 not recognized as winner.\n");
		errors++;
	}
	for(i = 1; i < 4; i++)
	{
		if(players[i] != 0)
		{
			printf("ERROR: Player %d recognized as winner.\n", i);
			errors++;
		}
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);

	printf("Test 2: Each player can win with Province in deck.\n");
	errors = 0;
	for(i = 0; i < 4; i++)
	{
		temp = G.deck[i][0];
		G.deck[i][0] = province;
		assert(G.deck[i][0] == province);
		getWinners(players, &G);
		if(players[i] != 1)
		{
			printf("ERROR: Player %d not recognized as winner.\n", i);
			errors++;
		}
		for(j = 0; j < 4; j++)
		{
			if(j != i)
			{
				if(players[j] == 1)
				{
					printf("ERROR: Player %d incorrectly recognized as winner.\n", j);
					errors++;
				}
			}
				
		}
		G.deck[i][0] = temp;
		assert(G.deck[i][0] == temp);
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);

	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);

	printf("Test 3: Each player can win with Province in hand.\n");
	errors = 0;
	for(i = 0; i < 4; i++)
	{
		G.hand[i][0] = province;
		assert(G.hand[i][0] == province);
		G.handCount[i]++;
		getWinners(players, &G);
		if(players[i] != 1)
		{
			printf("ERROR: Player %d not recognized as winner.\n", i);
			errors++;
		}
		for(j = 0; j < 4; j++)
		{
			if(j != i)
			{
				if(players[j] == 1)
				{
					printf("ERROR: Player %d incorrectly recognized as winner.\n", j);
					errors++;
				}
			}
				
		}
		G.hand[i][0] = copper;
		assert(G.hand[i][0] == copper);
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);

	printf("Test 4: Each player can win with Province in discard.\n");
	errors = 0;
	for(i = 0; i < 4; i++)
	{
		G.discard[i][0] = province;
		assert(G.discard[i][0] == province);
		G.discardCount[i]++;
		getWinners(players, &G);
		if(players[i] != 1)
		{
			printf("ERROR: Player %d not recognized as winner.\n", i);
			errors++;
		}
		for(j = 0; j < 4; j++)
		{
			if(j != i)
			{
				if(players[j] == 1)
				{
					printf("ERROR: Player %d incorrectly recognized as winner.\n", j);
					errors++;
				}
			}
				
		}
		G.discard[i][0] = copper;
		assert(G.discard[i][0] == copper);
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);

	printf("Test 5: Tie-breaking.\n");
	errors = 0;
	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < G.deckCount[i]; j++)
		{
			G.deck[i][j] = copper;
		}
		for(j = 0; j < G.handCount[i]; j++)
		{
			G.hand[i][j] = copper;
		}
		for(j = 0; j < G.discardCount[i]; j++)
		{
			G.discard[i][j] = copper;
		}
	}
	
	for(i = 0; i < 4; i++)
	{
		G.handCount[i] = 5;
		for(j = 0; j < G.handCount[i]; j++)
		{
			G.hand[i][j] = province;
		}
	}
	
	
	for(i = 0; i < 4; i++)
	{
		G.whoseTurn = i;
		getWinners(players, &G);
		if((i <= G.whoseTurn) && (i != 3))
		{
			if(players[i] == 1)
			{
				printf("%d turn", G.whoseTurn);
				printf("ERROR: Player %d incorrectly recognized as winner.\n", i);
				errors++;
			}
		}
		else
		{
			if((i != 3) && (players[i] == 0))
			{
				printf("%d turn", G.whoseTurn);
				printf("ERROR: Player %d not recognized as winner.\n", i);
				errors++;
			}
			else if((i == 3) && (players[i] != 1))
			{
				printf("%d turn", G.whoseTurn);
				printf("ERROR: Player %d incorrectly recognized as winner.\n", i);
				errors++;
			}
		}
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
    return 0;
}
