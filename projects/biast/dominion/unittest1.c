/* -----------------------------------------------------------------------
 * Unit test for discardCard
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
    int i;
    int seed = 50;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int startingHandSize = 5;
	int player = 0;
	int bonus = 0;
	int coppers[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
    }
	
	printf("Demonstration of discard pile by means of the endTurn function.\n\n");
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numPlayer, k, seed, &G);
	memcpy(G.hand[player], coppers, (sizeof(int) * startingHandSize));
	printf("Should be 0 cards in the discard pile before endTurn is called.\n");
	assert(G.discardCount[player] == 0);
	printf("%d cards in P1's discard pile.\n", G.discardCount[player]);
	endTurn(&G);
	assert(G.discardCount[player] == 5);
	printf("Should be 5 cards in the discard pile after endTurn is called.\n");
	printf("%d cards in P1's discard pile.\n\n", G.discardCount[player]);
	
	endTurn(&G);
	
	
	int trashFlag = 0;
	for (trashFlag = 0; trashFlag < 2; trashFlag++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		memcpy(G.hand[player], coppers, (sizeof(int) * startingHandSize));
		int discardPile = G.discardCount[player];
		printf("Starting value of discard pile is %d\n", discardPile);
		int discardCompare = discardPile;
		
		if (trashFlag == 0)
			printf("Testing with trash flag set to 0 (no trashing)\n");
		else
			printf("Testing with trash flag set to 1 (trashing)\n");
		for (i = startingHandSize; i > 0; i--)
		{
		
		printf("Cards in hand should be %d, is %d\n", i, G.handCount[player]);
		if(i != G.handCount[player])
		{
			errors++;
			printf("ERROR: Card not removed from hand successfully.\n\n");
		}
		
		printf("\nDiscarding card...\n");
		discardCard(0, player, &G, trashFlag);
		if(trashFlag == 0)
			{
				discardCompare++;
				printf("Discard card pile should have %d cards, has %d cards\n", discardCompare, G.discardCount[player]);
				if (discardCompare != G.discardCount[player])
				{
					errors++;
				}
				printf("Played card pile has %d cards.\n", G.playedCardCount);
			}
		else
			{
				printf("Discard pile should have 0 cards, has %d cards\n", G.discardCount[player]);
				printf("Played card pile should have 0 cards, has %d cards\n", G.discardCount[player]);
			}
		}
		printf("\nPlayed card count before ending the turn: %d\n", G.playedCardCount);
		printf("Ending the turn...\n");
		endTurn(&G);
		printf("Played card count after ending the turn: %d\n", G.playedCardCount);
		if (trashFlag == 0)
		{
			printf("Should be 5 cards in the discard pile after the turn ends\n");
			printf("Cards in discard pile for player: %d\n\n\n", G.discardCount[player]);
			if(G.discardCount[player] != 5)
			{
				errors++;
				printf("ERROR: Discard count value is incorrect.");
			}
		}
		else
		{
			printf("Should be 0 cards in the discard pile after the turn ends\n\n\n");
			if(G.discardCount[player] != 0)
				errors++;
		}
	}
	
	printf("%d errors detected\n\n", errors);
		

    return 0;
}
