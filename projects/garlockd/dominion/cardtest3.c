/* -----------------------------------------------------------------------
 * Testing: Great Hall
 *
 *
 * cardtest1: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	
	printf ("Starting test of: Great Hall Card:\n");
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G); 
    // Place Great Hall card in hand
    G.hand[whoseTurn(&G)][0] = great_hall;
    
    handSize = G.handCount[whoseTurn(&G)];
    startActions = state->numActions;
    
    cardGreat_Hall(&G, whoseTurn(&G), 0);
    
    endHandSize = G.handCount[whoseTurn(&G)];
    endActions = state->numActions;
    
    actionChange = (endActions -startActions);
    cardChange = (endHandSize - handSize);
    
	if(actionChange == 1 && cardChange == 0) {
		printf("Great Hall Test Successful \n");
	}
	else {
		printf("Great Hall test Failed \n");
	}
	return 0;
    
    
    
}
