/* -----------------------------------------------------------------------
 * TESTING: buyCard
 *
 * unittest1: unittest1.c dominion.o rngs.o
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

	// Setup game variables
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, G);
    G->numBuys = 100;
    G->coins = 100;
    G->supplyCount[adventurer] = 10;
    G->whoseTurn = 0;
    G->discardCount[0] = 10;

    // start the unit tests
    printf ("TESTING buyCard():\n");

    // buy card should fail if no buys left
    G->numBuys = 0;
    if (buyCard(k[0], G) != -1)
    {
        printf("buyCard() doesnn't fail properly when no buys left\n");
    }
    else
    {
        printf("buyCard() passed number of buys test\n");
    }
    G->numBuys = 100;

    // buy card should fail if no card of type left
    G->supplyCount[adventurer] = 0;
    if(buyCard(k[0], G) != -1)
    {
        printf("buyCard() doesnn't fail properly when none of card left\n");
    }
    else
    {
        printf("buyCard() passed number of card left test\n");
    }
    G->supplyCount[adventurer] = 10;

    // buy card should fail if not enough coins
    G->coins = 0;
    if (buyCard(k[0], G) != -1)
    {
        printf("buyCard() doesnn't fail properly when no coins left\n");
    }
    else
    {
        printf("buyCard() passed number of coins test\n");
    }
    G->coins = 100;

    // check number of buys and number of coins after buyCard()
    buyCard(k[0], G);

    if (G->numBuys != 99)
    {
        printf("buyCard() doesn't decrement numBuys properly\n");
    }
    else
    {
        printf("buyCard() passed numBuys decrement test\n");
    }

    if (G->coins != 99)
    {
        printf("buyCard() doesn't decrement coins properly\n");
    }
    else
    {
        printf("buyCard() passed coins decrement test\n");
    }

    return 0;
}
