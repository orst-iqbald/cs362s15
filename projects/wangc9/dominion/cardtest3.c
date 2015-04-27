#define TESTCARD "bug_remodelCardPlay()"

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
	int handPos = 1;
	int choiceCardCopper = 4;
	int choiceCardSilver = 5;
	struct gameState preRemodel, postRemodel;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seedRandom, &preRemodel);
	preRemodel.supplyCount[5] = 10;
	
	printf("-------------------- Test Card Function: %s --------------------\n", TESTCARD);

	memcpy(&postRemodel, &preRemodel, sizeof(struct gameState));
	
	postRemodel.hand[currentPlayer][0] = 5; //set first card in hand to silver

	bug_remodelCardPlay(5, currentPlayer, handPos, &postRemodel, 0, choiceCardCopper);

	printf("Test if function works with enough coins:\n");
	if (postRemodel.discard[currentPlayer][0] == 0) {
		printf("Silver card is now: %d, ", postRemodel.hand[currentPlayer][0]);
		if (postRemodel.hand[currentPlayer][0] == choiceCardCopper)
			printf("which is expected.\n");
		else
			printf("which is NOT expected.\n");
	}
	else {
		printf("Silver card is now: %d, ", postRemodel.discard[currentPlayer][0]);
		if (postRemodel.discard[currentPlayer][0] == choiceCardCopper)
			printf("which is expected.\n");
		else
			printf("which is NOT expected.\n");
	}
	
	printf("Cards in hand: %d, ", postRemodel.handCount[currentPlayer]);
	if (postRemodel.handCount[currentPlayer] == preRemodel.handCount[currentPlayer] - 2)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
		
	printf("Cards played: %d, ", postRemodel.playedCardCount);
	if (postRemodel.playedCardCount == preRemodel.playedCardCount + 2)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	//assert (postRemodel.handCount[currentPlayer] == preRemodel.handCount[currentPlayer] - 2);
	//assert (postRemodel.deckCount[currentPlayer] == preRemodel.deckCount[currentPlayer]);
	
	printf("\nTest if function works with inadequate coins:\n");	
	memcpy(&postRemodel, &preRemodel, sizeof(struct gameState)); 
	
	
	postRemodel.hand[currentPlayer][0] = 4; //set first card in hand to copper
	
	bug_remodelCardPlay(4, currentPlayer, handPos, &postRemodel, postRemodel.hand[currentPlayer][0], choiceCardSilver);
	
	printf("Copper card is now: %d, ", postRemodel.hand[currentPlayer][0]);
	if (postRemodel.hand[currentPlayer][0] == choiceCardCopper)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
	
	printf("Cards in hand: %d, ", postRemodel.handCount[currentPlayer]);
	if (postRemodel.handCount[currentPlayer] == preRemodel.handCount[currentPlayer])
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
		
	printf("Cards played: %d, ", postRemodel.playedCardCount);
	if (postRemodel.playedCardCount == preRemodel.playedCardCount)
		printf("which is expected.\n");
	else
		printf("which is NOT expected.\n");
		
	//assert (postRemodel.handCount[currentPlayer] == preRemodel.handCount[currentPlayer]);
	//assert (postRemodel.deckCount[currentPlayer] == preRemodel.deckCount[currentPlayer]);

	printf("\n-------------------- Test Complete: %s --------------------\n\n", TESTCARD);

	return 0;
}
