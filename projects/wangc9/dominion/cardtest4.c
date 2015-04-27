#define TESTCARD "bug_greathallCardPlay()"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
    int seedRandom = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
	int handPos = 0;
	struct gameState preGreat, postGreat;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seedRandom, &preGreat);
	preGreat.hand[currentPlayer][handPos] = 14;
	
	printf("-------------------- Test Card Function: %s --------------------\n", TESTCARD);
	memcpy(&postGreat, &preGreat, sizeof(struct gameState));

	playCard(handPos, 0, 0, 0, &postGreat); 
	bug_greathallCardPlay(currentPlayer, handPos, &postGreat);

	printf("Test if function works with enough actions:\n");
	printf("Total number of cards drawn: %d, ", preGreat.deckCount[currentPlayer] - postGreat.deckCount[currentPlayer]);	
	
	printf("Cards in hand: %d, ", postGreat.handCount[currentPlayer]);
	if (postGreat.handCount[currentPlayer] == preGreat.handCount[currentPlayer] + 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	if (preGreat.deckCount[currentPlayer] == postGreat.deckCount[currentPlayer] + 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	printf("Actions available: %d, ", postGreat.numActions);
	if (postGreat.numActions == preGreat.numActions + 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");

	printf("Cards played: %d, ", postGreat.playedCardCount);
	if (postGreat.playedCardCount == preGreat.playedCardCount + 1)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	//postGreat.handCount[currentPlayer]--;
	//assert (postGreat.handCount[currentPlayer] == preGreat.handCount[currentPlayer] + 1);
	//assert (postGreat.deckCount[currentPlayer] == preGreat.deckCount[currentPlayer] + 1);

	printf("\n-------------------- Test Complete: %s --------------------\n\n", TESTCARD);

	return 0;
}
