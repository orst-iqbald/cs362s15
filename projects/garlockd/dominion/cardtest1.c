/* -----------------------------------------------------------------------
 * Testing: Smithy card
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int handSize;
	int r;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	
	printf ("Starting test of: Smithy Card:\n");
	
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G);
    //Put smithy card in hand
    G.hand[whoseTurn(&G)][0] = smithy;
    handSize = G.handCount[whoseTurn(&G)];
    
    cardSmithy(&G, whoseTurn(&G), 0);
    
    //See if hand has increased by 2. +3 for Smithy -1 for Discard
	if(G.handCount[whoseTurn(&G)] == handSize + 2) {
		printf("Smithy Test Successful \n");
	}
	else {
		printf("Smithy Test Failed, Wrong amount of cards in hand \n");
	}
	return 0;
    
}
