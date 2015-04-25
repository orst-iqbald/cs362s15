/* -----------------------------------------------------------------------
 * Test for adventurer card implementation.
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
    int i, initCoins, newCoins;
    int seed = 1000;
    int numPlayer = 2;
    int p, handCount;
    int maxHandCount = 5;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *G = malloc(sizeof(struct gameState));

    printf ("TESTING playAdventurer():\n");
    for (p = 0; p < numPlayer; p++) {
        for (handCount = 1; handCount <= maxHandCount; handCount++) {
            initCoins = 0; //initializes starting treasure cards for each hand
            newCoins = 0;
#if (NOISY_TEST == 1)
            printf("Test player %d with adventurer card and with %d card(s).\n", p, handCount);
#endif        
            initializeGame(numPlayer, k, seed, G); //initialize a new game
            G->handCount[p] = handCount; //sets handCount to the current number of cards in the players hand
            G->hand[p][0] = adventurer; //sets the first card in the players hand to adventurer
            for (i = 0; i < G->handCount[p]; ++i) {
                if ( G->hand[p][i] == gold || G->hand[p][i] == silver || G->hand[p][i] == copper ) {
                    initCoins++;
                }
            }
            playAdventurer(p, G); //plays the adventurer card for testing
            for (i = 0; i < G->handCount[p]; ++i) {
                if ( G->hand[p][i] == gold || G->hand[p][i] == silver || G->hand[p][i] == copper ) {
                    newCoins++;
                }
            }
#if (NOISY_TEST == 1)
            printf("Test player %d with %d treasure cards in hand and at least 2 in deck... ", p, initCoins);
            if (newCoins == initCoins + 2) {
                printf("Test Passed! New total = %d, expected = %d\n", newCoins, initCoins + 2);
            }
            else {
                printf("Test Failed. New total = %d, expected = %d\n", newCoins, initCoins + 2);
            }
#endif
        }
    }

    printf("Testing Complete!\n");

    return 0;
}