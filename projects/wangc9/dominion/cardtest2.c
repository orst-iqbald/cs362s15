#define TESTCARD "bug_adventurercardplay()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int i;
    int treasureGained = 2;
    int seedRandom = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int drawntreasure = 0;
	int cardDrawn = 0;
	int tempHandCounter = 0;
	int temphand[MAX_HAND];
	struct gameState preAdventure, postAdventure;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seedRandom, &preAdventure);
	
	for (i = 0; i < 5; i++) //set all to copper
	{
		preAdventure.hand[0][i] = 4;
		preAdventure.deck[0][i] = 4;
	}
	updateCoins(currentPlayer, &preAdventure, 0);
	memcpy(&postAdventure, &preAdventure, sizeof(struct gameState));

	bug_adventurercardplay(drawntreasure, currentPlayer, cardDrawn, temphand, tempHandCounter, &postAdventure);
	updateCoins(currentPlayer, &postAdventure, 0);
	postAdventure.handCount[currentPlayer]--;
	
	printf("-------------------- Test Card Function: %s --------------------\n", TESTCARD);

	printf("Test if two new cards in hand are treasures:\n");
	printf("Total number of cards drawn: %d, ", preAdventure.deckCount[currentPlayer] - postAdventure.deckCount[currentPlayer]);
	if (preAdventure.deckCount[currentPlayer] - postAdventure.deckCount[currentPlayer] == 2)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
		
	printf("First new card: %d, ", postAdventure.hand[currentPlayer][5]);
	if (postAdventure.hand[currentPlayer][5] == 4)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	printf("Second new card: %d, ", postAdventure.hand[currentPlayer][6]);
	if (postAdventure.hand[currentPlayer][6] == 4)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	printf("Cards in discard: %d, ", postAdventure.playedCardCount);
	if (postAdventure.playedCardCount == 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	printf("Coins after buying: %d, ", (int)postAdventure.coins);
	if ((int)postAdventure.coins == (int)preAdventure.coins + 2)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");

	printf("\n-------------------- Test Complete: %s --------------------\n\n", TESTCARD);

	return 0;
}
