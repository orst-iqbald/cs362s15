#include "dominion.h"
#include "dominion_helpers.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, j, c;
    int seed = 1000;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int t[3] = {copper, silver, gold};
    struct gameState G;

    SelectStream(8);
    PlantSeeds(-1);

    for (i = 0; i < 20; ++i)
    {
      int handCount = floor(Random() * MAX_HAND);
      int numPlayers = floor(Random() * MAX_PLAYERS-2) + 2;
      int player = floor(Random() * numPlayers);
      int deckSize = floor(Random() * MAX_DECK);
      int cards[MAX_HAND];
      int actions = floor(Random() * 5);
      for (j = 0; j < MAX_HAND; ++j)
      {
        int randnum = floor(Random() * 12);
        // Give random card from kingdom cards.
        if (randnum <= 9)
        {
          cards[j] = k[randnum];
        }
        // Give random currency card.
        else
        {
          cards[j] = t[randnum-10];
        }
      }

      memset(&G, 23, sizeof G);
      r = initializeGame(numPlayers, k, seed, &G);
      memcpy(G.deck[player], cards, sizeof adventurer * deckSize);
      G.handCount[player] = handCount;
      G.deckCount[player] = deckSize;
      G.numActions = actions;
  
      playVillage(&G, player);
      c = numHandCards(&G);
  
      assert(G.numActions == actions+2);
      assert(c == handCount + 1);
    }

    printf("All tests passed!\n");

    return 0;
}
