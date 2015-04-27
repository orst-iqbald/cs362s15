/* -----------------------------------------------------------------------
 * TESTING: supplyCount
 *
 * unittest3: unittest3.c dominion.o rngs.o
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

	// Setup game variables
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);

    // an interator
    int i = 0;

    // start the unit tests
    printf ("TESTING supplyCount:\n");

    // This is difficult to test in that it is such a simple function. I
    // think that the best way to do it is to simply call a known working
    // version of the function on some values. Right now this is pretty 
    // useless, but if a change is made accidentally or in error, this
    // will pick it up.
    //
    // int supplyCount(int card, struct gameState *state) {
    //   return state->supplyCount[card];
    // }

    for (i = 0; i < 27; i++) {
        if (supplyCount(i, G) == G->supplyCount[i])
        {
            printf("supplyCount() passed for card %d\n", i);
        }
        else
        {
            printf("supplyCount() failed for card %d\n", i);
        }
    }

    return 0;
}
