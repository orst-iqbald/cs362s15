/* -----------------------------------------------------------------------
 *  Random Testing: Smithy Card
 *
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestacard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	struct gameState G;
	int r;
	int handSize;
	int handSizeAfter;
	int i;
	int k;
	int checkCard;
	int handChange;
	int gameSeed = 0;
	int testFails = 0;
	int numPlayers = 0;
	int loopFails = 0;
	int startActions;
	int endActions;
	int actionChange;
	int startActions;
	int endActions;
	int actionChange;
	int startBuys;
	int endBuys;
	int buyChange;
	
	printf ("Starting random test of: Smithy Card:\n");
	for (k = 0; k < 100; k++)
	{
	printf ("Starting test %d:\n", k);
	
	//randomize initializing details
	gameSeed = (rand() % 50000);
	numPlayers = (rand() % 4) + 2;
	
	// Clear game
    memset(&G, 23, sizeof(struct gameState));

    // Initialize game
    r = initializeGame(numPlayers, cards, gameSeed, &G);

    //Get starting details
    handSize = G.handCount[whoseTurn(&G)];
    startActions = state->numActions;
    startBuys = state->numBuys;

    // Place Smithy card in hand
    G.hand[whoseTurn(&G)][0] = smithy;
    
    // Use Smithy card
    cardSmithy(&G, whoseTurn(&G), 0);



    // Check end stats
    handSizeAfter = G.handCount[whoseTurn(&G)];
    endActions = state->numActions;
    endBuys = state->numBuys;
    
    handChange = (handSizeAfter - handSize);
    buyChange = (startBuys - endBuys);
    actionChange = (startActions - endActions);

	//See if end hand has correct number of hands
	if(handChange == 2) {
		printf("Test %d passed", k);
	}
	else {
		loopFails++;
		printf("Test %d failed, wrong amount of cards in hand\n", k);
	}

	//Check amount of buys
	if(buyChange == 0) {
		printf("Test %d passed", k);
	}
	else {
		loopFails++;
		printf("Test %d failed, wrong amount of buys left\n", k);
	}

	//Check amount of actions
	if(actionChange == 1) {
		printf("Test %d passed", k);
	}
	else {
		loopFails++;
		printf("Test %d failed, wrong amount of actions left\n", k);
	}

	if(loopFails > 0) {
		testFails++;
	}
	//reset variables
	int change = 0;
	int loopFails = 0;
	}

    printf("Testing Complete\n", k);
    printf("Smithy card failed %d of 100 tests \n", testFails);

	return 0;
    
}

