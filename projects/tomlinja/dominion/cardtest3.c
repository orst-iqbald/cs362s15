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

    printf("Testing playVillage() increases action amount by 2.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    G.numActions = 1;

    playVillage(&G, 0);

    assert(G.numActions == 3);

    printf("Testing playVillage() with hand sizes 1..%d.\n", MAX_HAND-1);
    
    for (handCount = 1; handCount <= MAX_HAND-1; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playVillage(&G, 0);
      c = numHandCards(&G);

      assert(c == handCount + 1);
    }

    printf("Testing playVillage() with hand sizes %d..%d.\n", MAX_HAND, MAX_HAND);

    for (handCount = MAX_HAND; handCount <= MAX_HAND; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playVillage(&G, 0);
      c = numHandCards(&G);

      printf("Handcount: %d; C: %d\n", handCount, c);
      assert(c == MAX_HAND);
    }


    printf("All tests passed!\n");

    return 0;
}
