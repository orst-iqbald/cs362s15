/* -----------------------------------------------------------------------
 * Unit test for fullDeckCount
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
	int estateCount = 0;
	int copperCount = 0;
	int counter;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	
	assert(G.handCount[player] == 5);
	assert(G.deckCount[player] == 5);
	
	printf("\nNew game initialized. 5 in hand, 5 in deck.\n");
	
	printf("\nCards in hand:\n");
	for(i = 0; i < G.handCount[player]; i++)
	{
		if(G.hand[player][i] == 1)
		{
			printf("Estate\n");
			estateCount++;
		}
		else if(G.hand[player][i] == 4)
		{
			printf("Copper\n");
			copperCount++;
		}
	}
	printf("\nCards in deck:\n");
	for(i = 0; i < G.deckCount[player]; i++)
	{
		if(G.deck[player][i] == 1)
		{
			printf("Estate\n");
			estateCount++;
		}
		else if(G.deck[player][i] == 4)
		{
			printf("Copper\n");
			copperCount++;
		}
	}

	assert(copperCount == 7);
	assert(estateCount == 3);

	printf("\nAsserts passed.\n");
	printf("Number of COPPERS: %d\n", copperCount);
	printf("Number of ESTATES: %d\n", estateCount);
	

	
	printf("\nTest 1: New game.\n");
	if(fullDeckCount(player, 4, &G) != 7)
	{
		printf("ERROR: Failed to detect 7 copper.\n");
		printf("Detected %d instead.\n", fullDeckCount(player, 4, &G));
		errors++;
	}
	if(fullDeckCount(player, 1, &G) != 3)
	{
		printf("ERROR: Failed to detect 3 estates.\n");
		printf("Detected %d instead.\n", fullDeckCount(player, 1, &G));
		errors++;
	}
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	
	printf("Test 2: Counting cards in discard pile.\n");
	errors = 0;
	
	for(i = 0; i < 10; i++)
	{
		G.discard[player][i] = copper;
		G.discardCount[player]++;
	}
	
	counter = 0;
	for(i = 0; i < 10; i++)
	{
		if(G.discard[player][i] == 4)
			counter++;
	}
	for(i = 0; i < 5; i++)
	{
		if(G.deck[player][i] == 4)
			counter++;
		if(G.hand[player][i] == 4)
			counter++;
	}
	assert(counter == 17);
	printf("Assert passed: 17 coppers now in deck.\n");
	
	if(fullDeckCount(player, copper, &G) != 17)
	{
		printf("ERROR: %d coppers detected in deck.\n", fullDeckCount(player, copper, &G));
		errors++;
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 3: 0 count for all other cards.\n");
	
	counter = 0;
	for(i = 0; i < 25; i++)
	{
		if((i != 1) && (i != 4))
		{
			for(j = 0; j < 5; j++)
			{
				if(G.deck[player][j] == i)
					counter++;
				else if(G.hand[player][j] == i)
					counter++;
				assert(counter == 0);
			}
		}
	}
	printf("Asserts passed: 0 of every card other than copper and estate in deck.\n");
	
	errors = 0;
	for(i = 0; i < 25; i++)
	{
		if((i != 1) && (i != 4))
		{
			if(fullDeckCount(player, i, &G) != 0)
			{
				printf("ERROR: Card #%d falsely detected.\n", i);
				errors++;
			}
		}
	}
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	
	printf("Test 4: Counting all types of cards\n");
	errors = 0;
	
	for(i = 0; i < 25; i++)
	{
		for(j = 0; j < 5; j++)
		{
			G.deck[player][j] = i;
			G.hand[player][j] = i;
		}
		for(j = 0; j < 10; j++)
		{
			G.discard[player][j] = i;
		}
		
		// Counter to prepare assert statement
		counter = 0;
		for(j = 0; j < 10; j++)
		{
			if(G.discard[player][j] == i)
				counter++;
		}
		for(j = 0; j < 5; j++)
		{
			if(G.deck[player][j] == i)
				counter++;
			if(G.hand[player][j] == i)
				counter++;
		}
		assert(counter == 20);
		
		if(fullDeckCount(player, i, &G) != 20)
		{
			printf("ERROR: Miscount on card type %d\n", i);
			errors++;
		}
	}
	
	printf("All asserts passed.\n\n");
	
	printf("Test complete.\n");
	if(errors == 0)
		printf("No errors.\n\n");
	else
		printf("%d errors detected.\n\n", errors);
	

    return 0;
}
