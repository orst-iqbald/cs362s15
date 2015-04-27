/* -----------------------------------------------------------------------
 * TESTING: actionVillage
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
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

    // Setup game variables
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);

    // set a card in the player's hand to smithy
    G->hand[0][0] = village;

    // some variables to work with
    int hand = 0;
    int actions = 0;

    // start the unit tests
    printf ("TESTING Village:\n");

    // The effects of this card should be as follows:
    // - hand size increases by 1 - 1 for discard
    // - number of actions increases by 2

    // store the size of original hand and deck
    hand = G->handCount[0];
    actions = G->numActions;

    // run the function
    actionVillage(0, 0, G);

    // Check size of hand
    if (G->handCount[0] == hand)
    {
        printf("Village(): passed for hand count\n");
    }
    else
    {
        printf("Village(): failed for hand count\n");
    }

    // Check number of actions
    if (G->numActions == actions + 2)
    {
        printf("Village(): passed for actions count\n");
    }
    else
    {
        printf("Village(): failed for actions count\n");
    }

    return 0;
}
