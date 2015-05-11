/* -----------------------------------------------------------------------
 * TESTING: isGameOver (random)
 *
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int main() {

    // number of tests to run
    int NUM_TESTS = 100;

    // seed the random number generator
    srand(time(NULL));

    // Setup game variables
    int seed = 1000;
    int numPlayers;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    // build the game state
    struct gameState *G = malloc(sizeof(struct gameState));

    // some variables
    int i = 0;
    int j = 0;
    int temp = 0;


    // start the random tests
    printf ("TESTING isGameOver (random):\n");
    for (j = 0; j < NUM_TESTS; j++)
    {
        numPlayers = rand() % 3 + 2; // random number of players (2-4)

        initializeGame(numPlayers, k, seed, G);

        for(i = 0; i < 27; i++)
        {
            G->supplyCount[i] = rand() % 9; // low to ensure many 0 values
        }

        // if supply of province cards is zero game should be over
        if (G->supplyCount[province] == 0 && isGameOver(G) != 1)
        {
            printf("%d: isGameOver() doesn't properly fail when supply of provinces is 0\n", j);
        }
        else
        {
            printf("%d: isGameOver() passed supply of provinces = 0 test\n", j);
        }

        // if three supply piles are zero game should be over
        temp = 0;
        for(i = 0; i < 27; i++)
        {
            if (G->supplyCount[i] == 0)
                temp++;
        }
        if (temp >= 3 && isGameOver(G) != 1)
        {
            printf("%d: isGameOver() doesn't properly fail when supply of three piles is 0\n", j);
            printf("   Values: ");
            for(i = 0; i < 27; i++)
            {
                printf("%d ", G->supplyCount[i]);
            }
            printf(".\n");
        }
        else
        {
            printf("%d: isGameOver() passed three supply piles = 0 test\n", j);
        }
    }

    exit(0);
}
