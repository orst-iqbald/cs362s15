/* -----------------------------------------------------------------------
 * Testing: whosTurn()
 *
 * cardtest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
	
	printf ("Starting test of: whosTurn(): \n");
	// Clear
    memset(&G, 23, sizeof(struct gameState));
    // Initialize
    r = initializeGame(2, cards, 1111, &G);
    
    // Check player 1
    printf ("Checking player 1: \n");
    assert(whoseTurn(&game) == 0);
    // Check player 2
    printf ("Checking player 2: \n");
    game.whoseTurn++;
    assert(whoseTurn(&game) == 1);
    printf ("whosTurn() Successful \n");
    return 0;
}
