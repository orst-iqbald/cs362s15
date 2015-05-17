#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#include <math.h>
#include <time.h>


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
	//SelectStream(2);
	//PutSeed(3);

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Testing Card: %s \n", TESTCARD);

	for (int thisisUnique = 0; thisisUnique < 9; thisisUnique++) {

		//printf("Test# %d\n", thisisUnique);
		//printf("Unique Address %d\n", &thisisUnique);
        int numberOfPlayers = floor(Random() * MAX_PLAYERS);
        thisPlayer = floor(Random() * numberOfPlayers);

        testG.handCount[thisPlayer] = floor(Random() * MAX_HAND);
        testG.deckCount[thisPlayer] = floor(Random() * MAX_DECK);

        testG.numActions = 0;
        testG.whoseTurn = thisPlayer;
        testG.numPlayers = numberOfPlayers;

		//calls the adventurer card function and asserts 2 treasure cards were drawn
		adventurer_card(drawntreasure, thisPlayer, cardDrawn, temphand, z, &testG);
		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);

		if(drawntreasure == 2){
			printf("Treasure test PASSED!\n");
		}else{
			printf("Treasure test FAILED!\n");
		}
		//assert(drawntreasure == 2);
	}
	
	printf("%s card finished all tests.\n", TESTCARD);

	return 0;
}