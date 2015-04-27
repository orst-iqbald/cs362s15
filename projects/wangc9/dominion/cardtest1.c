#define TESTCARD "bug_smithycardplay()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int i;
    int handpos = 0;
    int seedRandom = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	struct gameState preSmithy, postSmithy;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seedRandom, &preSmithy);
	memcpy(&postSmithy, &preSmithy, sizeof(struct gameState));

	bug_smithycardplay(0, currentPlayer, handpos, &postSmithy);

	printf("-------------------- Test Card Function: %s --------------------\n", TESTCARD);

	printf("Test if card quantity is correct:\n");
	printf("Cards in hand: %d, ", postSmithy.handCount[0]);
	if (postSmithy.handCount[0] == preSmithy.handCount[0] + 2)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	printf("Cards in deck: %d, ", postSmithy.deckCount[0]);
	if (postSmithy.deckCount[0] == preSmithy.deckCount[0] - 3)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	printf("Cards in discard: %d, ", postSmithy.playedCardCount);
	if (postSmithy.playedCardCount == preSmithy.playedCardCount + 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	//assert (postSmithy.handCount[0] == preSmithy.handCount[0] + 2);
	//assert (postSmithy.deckCount[0] == preSmithy.deckCount[0] - 3);
	//assert (postSmithy.playedCardCount == preSmithy.playedCardCount + 1);
	
	memcpy(&postSmithy, &preSmithy, sizeof(struct gameState));

	for (i = 0; i < 5; i++)
	{
		postSmithy.discard[0][i] = postSmithy.deck[0][i];
		postSmithy.deck[0][i] = -1;
		postSmithy.deckCount[0]--;
		postSmithy.discardCount[0]++;
	}

	printf("\n-------------------- Test Complete: %s --------------------\n\n", TESTCARD);

	return 0;
}
