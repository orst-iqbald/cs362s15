/* -----------------------------------------------------------------------
 * Test for smithy card implementation.
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
    int seed = 1000;
    int numPlayer = 2;
    int p, handCount;
    int maxHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));

    printf ("TESTING playSmithy():\n");
    for (p = 0; p < numPlayer; p++) {  
        for (handCount = 1; handCount <= maxHandCount; handCount++) {
#if (NOISY_TEST == 1)
            printf("Test player %d with smithy card and with %d card(s).\n", p, handCount);
#endif        
            initializeGame(numPlayer, k, seed, G); //initialize a new game
            G->hand[p][0] = smithy; //sets the first card in the players hand to smithy
            G->handCount[p] = handCount; //sets handCount to the current number of cards in the players hand
            playSmithy(p, G, 0); //plays the smithy card for testing
#if (NOISY_TEST == 1)
            printf("Hand count = %d, expected = %d\n", G->handCount[p], handCount + 2);
#endif
        }
    }

    printf("Testing Complete!\n");

    return 0;
}