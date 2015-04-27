/* -----------------------------------------------------------------------
 * Testing: Village
 *
 *
 * cardtest1: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	int handSize;
	int endHandSize;
	int i;
	int startActions;
	int endActions;
	int actionChange;
	int cardChange;
	int r;
	
	printf ("Starting test of: Village Card:\n");
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G); 
    // Place Village card in hand
    G.hand[whoseTurn(&G)][0] = great_hall;
    
    handSize = G.handCount[whoseTurn(&G)];
    startActions = state->numActions;
    
    cardVillage(&G, whoseTurn(&G), 0);
    
    endHandSize = G.handCount[whoseTurn(&G)];
    endActions = state->numActions;
    
    actionChange = (endActions -startActions);
    cardChange = (endHandSize - handSize);
    
	if(actionChange == 2 && cardChange == 0) {
		printf("Village Test Successful \n");
	}
	else {
		printf("Village test Failed \n");
	}
	return 0;
    
    
    
}
