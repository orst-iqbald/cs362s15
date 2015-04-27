/* -----------------------------------------------------------------------
 * Testing: supplyCount()
 *
 * cardtest1: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
    

    //Check to see if game has 10 curse cards
    assert(supplyCount(0, &game) == 10);



    printf ("supplyCount() Successful \n");
	return 0;
}
