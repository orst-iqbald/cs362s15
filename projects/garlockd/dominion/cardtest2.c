/* -----------------------------------------------------------------------
 * Testing: Adventurer Card
 *
 * cardtest1: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	int i;
	int checkCard;
	int startTreasure = 0;
	int endTreasure = 0;
	int change;
	
	
	
	printf ("Starting test of: Adventurer Card:\n");
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G); 
    // Place Adventerer card in hand
    G.hand[whoseTurn(&G)][0] = adventurer;
    handSize = G.handCount[whoseTurn(&G)];
    
	// Count treasure cards in hand
        for(i = 0; i < state->handSize[p]; i++) {
                checkCard = state->hand[p][i];
                if(checkCard == copper || card == silver || card == gold) {
                        startTreasure++;
                } 
    
    // Use Adventurer card
    cardAdventurer(&G, whoseTurn(&G), 0);
    
    
    for(i = 0; i < state->handSize[p]; i++) {
            checkCard = state->hand[p][i];
            if(checkCard == copper || card == silver || card == gold) {
                    endTreasure++;
            }
    change = (endTreasure - startTreasure);
    
    //See if end hand has 2 more treasures than original hand.
	if(change == 2) {
		printf("Adventurer Test Successful \n");
	}
	else {
		printf("Adventurer Test Failed, Wrong amount of treasure in hand \n");
	}
	return 0;
    
}
