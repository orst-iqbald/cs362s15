#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int c;
    int seed = 1000;
    int numPlayers = 4;
    int r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("Testing playSmithy() with hand sizes 1..%d.\n", MAX_HAND-3);
    
    for (handCount = 1; handCount <= MAX_HAND-3; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playSmithy(&G, 0);
      c = numHandCards(&G);

      printf("Handcount: %d; C: %d\n", handCount, c);
      assert(c == handCount + 3);
    }

    printf("Testing playSmithy() with hand sizes %d..%d.\n", MAX_HAND-2, MAX_HAND);

    for (handCount = MAX_HAND-2; handCount <= MAX_HAND; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playSmithy(&G, 0);
      c = numHandCards(&G);

      printf("Handcount: %d; C: %d\n", handCount, c);
      assert(c == MAX_HAND);
    }

    printf("All tests passed!\n");

    return 0;
}
