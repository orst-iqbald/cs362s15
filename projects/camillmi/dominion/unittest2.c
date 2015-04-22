/* -----------------------------------------------------------------------
 * TESTING: isGameOver
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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

    // start the unit tests
    printf ("TESTING isGameOver:\n");

    // upon initialization game isn't over
    if (isGameOver(G) != 0)
    {
        printf("isGameOver() improperly fails immediately after game initialization\n");
    }
    else
    {
        printf("isGameOver() passed after initialization test\n");
    }

    // if supply of province cards is zero game should be over
    G->supplyCount[province] = 0;
    if (isGameOver(G) != 1)
    {
        printf("isGameOver() doesn't properly fail when supply of provinces is 0\n");
    }
    else
    {
        printf("isGameOver() passed supply of provinces is 0 test\n");
    }
    G->supplyCount[province] = 1;

    // if three supply piles are zero game should be over
    G->supplyCount[0] = 0;
    G->supplyCount[1] = 0;
    G->supplyCount[2] = 0;
    if (isGameOver(G) != 1)
    {
        printf("isGameOver() doesn't properly fail when supply of three piles is 0\n");
    }
    else
    {
        printf("isGameOver() passed three supply piles = 0 test\n");
    }

    return 0;
}
