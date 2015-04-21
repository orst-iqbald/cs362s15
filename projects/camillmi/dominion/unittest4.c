/* -----------------------------------------------------------------------
 * TESTING: fullDeckCount
 *
 * unittest4: unittest4.c dominion.o rngs.o
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

	// Setup game variables
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);

    // an interator and temp variable
    int i = 0;
    int j = 0;
    int temp = 0;

    // start the unit tests
    printf ("TESTING fullDeckCount:\n");

    // This funtion is similar to unittest3, described below, except that
    // there is some addition necessary.
    //
    // This is difficult to test in that it is such a simple function. I
    // think that the best way to do it is to simply call a known working
    // version of the function on some values. Right now this is pretty 
    // useless, but if a change is made accidentally or in error, this
    // will pick it up.
    //
    // int supplyCount(int card, struct gameState *state) {
    //   return state->supplyCount[card];
    // }

    for (j = 0; j < 27; j++) {

        temp = 0;
        
        for (i = 0; i < G->deckCount[0]; i++)
        {
            if (G->deck[0][i] == j) temp++;
        }
        for (i = 0; i < G->handCount[0]; i++)
        {
            if (G->hand[0][i] == j) temp++;
        }
        for (i = 0; i < G->discardCount[0]; i++)
        {
            if (G->discard[0][i] == j) temp++;
        }

        if (temp == fullDeckCount(0, j, G))
        {
            printf("fullDeckCount() passed for card %d\n", j);
        }
        else
        {
            printf("fullDeckCount() failed for card %d\n", j);
        }

    }

    return 0;
}
