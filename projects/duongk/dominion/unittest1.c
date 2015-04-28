#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

#define TESTFUNC "updateCoins()"

int main() {
    
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int currPlayer = 0;
    //int numCardTypes = 10, minCards = 0, maxCards = 12;
	
		struct gameState state;
	    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	    
	    char* cardName[] = {"adventurer", "embargo", "village", "minion", "mine", "cutpurse", "sea_hag", "tribute", "smithy", "council_room"};

	    //Set game state to prepare for testing.
	    initializeGame(numPlayers, k, seed, &state);

	    printf("Asserting coin values are calculated properly.\n");

	    //Set hand to all copper.
	    for (i = 0; i < state.handCount[currPlayer]; i++) {
	            state.hand[currPlayer][i] = copper;
	    }
	    updateCoins(currPlayer, &state, 0);
	    printf("Asserting copper card holds value of 1\n");
	    assert(state.coins == state.handCount[currPlayer] * 1);

	    //Set hand to all silver.
	    for (i = 0; i < state.handCount[currPlayer]; i++) {
	            state.hand[currPlayer][i] = silver;
	    }
	    updateCoins(currPlayer, &state, 0);
	    printf("Asserting silver card holds value of 2\n");
	    assert(state.coins == state.handCount[currPlayer] * 2);
	    
	    //Set hand to all gold.
	    for (i = 0; i < state.handCount[currPlayer]; i++) {
	            state.hand[currPlayer][i] = gold;
	    }
	    updateCoins(currPlayer, &state, 0);
	    printf("Asserting gold card holds value of 3\n");
	    assert(state.coins == state.handCount[currPlayer] * 3);

    printf("All coin tests passed.\n");

    return 0;
}