/* -----------------------------------------------------------------------
 * TESTING: actionSmithy
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

    // set a card in the player's hand to smithy
    G->hand[0][0] = smithy;

    // some variables to work with
    int hand = 0;

    // start the unit tests
    printf ("TESTING Smithy:\n");

    // The effects of this card should be as follows:
    // - hand size increases by 3 - 1 for discard

    // store the size of original hand and deck
    hand = G->handCount[0];

    // run the function
    actionSmithy(0, 0, G);

    // Check size of hand
    if (G->handCount[0] == hand + 2) // + 3 - 1 for discard
    {
        printf("Smithy(): passed for hand count\n");
    }
    else
    {
        printf("Smithy(): failed for hand count\n");
    }

    return 0;
}
