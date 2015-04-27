/* -----------------------------------------------------------------------
 * Testing: numHandCards()
 *
 * cardtest1: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
	

	printf ("Starting test of: getCost(): \n");
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G);
    

    //Check to see if cards in hand is 5
    assert(numHandCards(&game) == 5);



    printf ("numHandCards() Successful \n");
	return 0;
}
