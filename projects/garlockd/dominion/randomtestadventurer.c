/* -----------------------------------------------------------------------
 *  Random Testing: Adventurer Card
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
	int startTreasure = 0;
	int endTreasure = 0;
	int change;
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
	
	printf ("Starting random test of: Adventurer Card:\n");
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

    // Place Adventerer card in hand
    G.hand[whoseTurn(&G)][0] = adventurer;

    // Count treasure cards in hand

        for(i = 0; i < state->handSize[p]; i++) {
                checkCard = state->hand[p][i];
                if(checkCard == copper || card == silver || card == gold) {
                        startTreasure++;
                } 
    
    // Use Adventurer card
    cardAdventurer(&G, whoseTurn(&G), 0);
    
    // count treasure cards in hand after use
    for(i = 0; i < state->handSize[p]; i++) {
            checkCard = state->hand[p][i];
            if(checkCard == copper || card == silver || card == gold) {
                    endTreasure++;
            }


    // Check end stats
    handSizeAfter = G.handCount[whoseTurn(&G)];
    endActions = state->numActions;
    endBuys = state->numBuys;
    
    change = (endTreasure - startTreasure);
    handChange = (handSizeAfter - handSize);
    buyChange = (startBuys - endBuys);
    actionChange = (startActions - endActions);
    //See if end hand has 2 more treasures than original hand.
	if(change == 2) {
		printf("Test %d passed", k);
	}
	else {
		loopFails++;
		printf("Test %d failed, wrong amount of treasures in hand\n", k);
	}

	//See if end hand has correct number of hands
	if(handChange == 1) {
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
	int startTreasure = 0;
	int endTreasure = 0;
	int change = 0;
	int loopFails = 0;
	}

    printf("Testing Complete\n", k);
    printf("Adventurer card failed %d of 100 tests \n", testFails);

	return 0;
    
}

