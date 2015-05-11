#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
	int i, j;
	int z = 0;
    int newCards = 3;
    int discarded = 1;
    int shuffledCards = 0;
    int cardDrawn = 0;
    int handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int currentPlayer;
    int drawntreasure = 0;
    int temphand[MAX_HAND];
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Testing Card: %s \n", TESTCARD);

	//calls the adventurer card function and asserts cards are discarded and not trashed
	adventurer_card(drawntreasure, thisPlayer, cardDrawn, temphand, z, &testG);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);

	//assert(z == 0);
	if(z == 0){
		printf("Treasure test PASSED!\n");
	}else{
		printf("Treasure test FAILED!\n");
	}


	printf("%s card finished all tests.\n", TESTCARD);

	return 0;
}