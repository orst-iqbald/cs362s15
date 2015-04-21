/* -----------------------------------------------------------------------
 * TESTING: actionAdventurer
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

	// Setup game variables
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);

    // set a card in the player's hand to adventurer
    G->hand[0][0] = adventurer;

    // some variables to work with
    int i = 0;
    int treasures = 0;
    int hand = 0;
    int temp = 0;

    // start the unit tests
    printf ("TESTING actionAdventurer:\n");

    // The effects of this card should be as follows:
    // - draws cards until two treasure cards are drawn
    // - drawn treasure cards added to hand
    // - other drawn cards discarded

    // store the number of treasures originally in hand
    for (i = 0; i < G->handCount[0]; i++)
    {
        if ( G->hand[0][i] == gold || G->hand[0][i] == silver || G->hand[0][i] == copper )
        {
            treasures++;
        }
    }

    // store the size of original hand
    hand = G->handCount[0];

    // run the function
    actionAdventurer(0, 0, G);

    // Check number of treasures in hand
    for (i = 0; i < G->handCount[0]; i++)
    {
        if ( G->hand[0][i] == gold || G->hand[0][i] == silver || G->hand[0][i] == copper )
        {
            temp++;
        }
    }
    if (temp == treasures + 2)
    {
        printf("actionAdventurer(): passed for treasure count\n");
    }
    else
    {
        printf("actionAdventurer(): failed for treasure count\n");
    }

    // Check size of hand
    if (G->handCount[0] == hand + 1) // + 2 - 1 for the discard
    {
        printf("actionAdventurer(): passed for hand count\n");
    }
    else
    {
        printf("actionAdventurer(): failed for hand count\n");
    }

    return 0;
}
