/* -----------------------------------------------------------------------
 * Test for village card implementation.
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
    int preActions = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));

    printf ("TESTING playVillage():\n");
    for (p = 0; p < numPlayer; p++) {  
        for (handCount = 1; handCount <= maxHandCount; handCount++) {
#if (NOISY_TEST == 1)
            printf("Test player %d with village card and with %d card(s).\n", p, handCount);
#endif        
            initializeGame(numPlayer, k, seed, G); //initialize a new game
            G->hand[p][0] = village; //sets the first card in the players hand to village
            G->handCount[p] = handCount; //sets handCount to the current number of cards in the players hand
            preActions = G->numActions; //stores initial number of actions before card is played 
            playVillage(p, G, 0); //plays the village card for testing
#if (NOISY_TEST == 1)
            printf("Hand count = %d, expected = %d\n", G->handCount[p], handCount);
            printf("Action count = %d, expected = %d\n", G->numActions, preActions + 2);
#endif
        }
    }

    printf("Testing Complete!\n");

    return 0;
}