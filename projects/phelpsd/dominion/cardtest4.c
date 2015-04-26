/* -----------------------------------------------------------------------
 * Test for cutpurse card implementation.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 4;
    int preCoins = 0;
    int k[10] = {adventurer, council_room, cutpurse, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));

    printf ("TESTING playCutpurse():\n");  
#if (NOISY_TEST == 1)
            printf("Test player 1 with cutpurse card and all except last player with 1 copper.\n");
#endif
    initializeGame(numPlayer, k, seed, G); //initialize a new game
    for (i = 0; i < numPlayer; ++i) {
        G->handCount[i] = 5;
    }
    G->hand[0][0] = cutpurse;
    G->hand[1][0] = copper;
    G->hand[2][0] = copper;
  
    preCoins = G->coins; //stores initial number of coins before card is played 
    playCutpurse(0, G, 0); //plays the village card for testing
#if (NOISY_TEST == 1)
    printf("Coin count = %d, expected = %d\n", G->coins, preCoins + 2);
    for (i = 0; i < numPlayer; ++i) {
        printf("Hand count for player %d after cutpurse is played.\n", i);
        if (i == 3) {
            printf("No copper found. Expected: %d, Actual: %d\n", 5, G->handCount[i]);
        }
        else {
            printf("Copper found. Expected: %d, Actual: %d\n", 4, G->handCount[i]);
        }
    }
#endif

    printf("Testing Complete!\n");

    return 0;
}