#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, j, c;
    int seed = 1000;
    int numPlayers = 4;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    for (i = 2; i <= numPlayers; ++i)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(i, k, seed, &G);

      printf("Test for whoseTurn() with %d players:\n", i);
      
      for (j = 0; j < i; ++j)
      {
        c = whoseTurn(&G);
        assert(c == j);
        printf("On player %d's turn, whoseTurn() returns player %d.\n", j, j);
        endTurn(&G);
      }
    }

    printf("All tests passed!\n");

    return 0;
}
