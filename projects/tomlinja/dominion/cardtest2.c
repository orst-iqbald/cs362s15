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

    printf("Testing playCouncilRoom() increases buy amount by 1.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    G.numBuys = 1;

    playCouncilRoom(&G, 0);

    assert(G.numBuys == 2);

    printf("Testing playCouncilRoom() increases other players hands by 1.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    G.handCount[1] = 1;
    G.handCount[2] = 1;
    G.handCount[3] = 1;

    playCouncilRoom(&G, 0);

    assert(G.handCount[1] == 2);
    assert(G.handCount[2] == 2);
    assert(G.handCount[3] == 2);

    printf("Testing playCouncilRoom() with hand sizes 1..%d.\n", MAX_HAND-4);
    
    for (handCount = 1; handCount <= MAX_HAND-4; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playCouncilRoom(&G, 0);
      c = numHandCards(&G);

      printf("Handcount: %d; C: %d\n", handCount, c);
      assert(c == handCount + 4);
    }

    printf("Testing playCouncilRoom() with hand sizes %d..%d.\n", MAX_HAND-3, MAX_HAND);

    for (handCount = MAX_HAND-3; handCount <= MAX_HAND; ++handCount)
    {
      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      G.handCount[0] = handCount;

      playCouncilRoom(&G, 0);
      c = numHandCards(&G);

      printf("Handcount: %d; C: %d\n", handCount, c);
      assert(c == MAX_HAND);
    }


    printf("All tests passed!\n");

    return 0;
}
