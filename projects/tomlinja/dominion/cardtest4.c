#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, c;
    int seed = 1000;
    int numPlayers = 4;
    int r, handCount;
    int deckSize = 10;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int adventurers[MAX_HAND];
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; ++i)
    {
      adventurers[i] = adventurer;
      coppers[i] = copper;
      silvers[i] = silver;
      golds[i] = gold;
    }
    handCount = 3;

    printf("Testing playAdventurer() with copper cards.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    memcpy(G.deck[0], coppers, sizeof copper * deckSize);
    G.handCount[0] = handCount;
    G.deckCount[0] = deckSize;

    playAdventurer(&G, 0);
    c = numHandCards(&G);

    assert(c == handCount + 2);

    printf("Testing playAdventurer() with silver cards.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    memcpy(G.deck[0], silvers, sizeof silver * deckSize);
    G.handCount[0] = handCount;
    G.deckCount[0] = deckSize;

    playAdventurer(&G, 0);
    c = numHandCards(&G);

    assert(c == handCount + 2);

    printf("Testing playAdventurer() with empty deck.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    memcpy(G.discard[0], silvers, sizeof silver * deckSize);
    G.handCount[0] = handCount;
    G.discardCount[0] = deckSize;

    playAdventurer(&G, 0);
    c = numHandCards(&G);

    assert(c == handCount + 2);

    printf("Testing playAdventurer() with no coins in deck.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    memcpy(G.deck[0], adventurers, sizeof adventurer * deckSize);
    G.handCount[0] = handCount;
    G.deckCount[0] = deckSize;

    playAdventurer(&G, 0);
    c = numHandCards(&G);

    assert(c == handCount);

    printf("Testing playAdventurer() with gold cards.\n");

    memset(&G, 23, sizeof G);
    r = initializeGame(numPlayers, k, seed, &G);
    memcpy(G.deck[0], golds, sizeof gold * deckSize);
    G.handCount[0] = handCount;
    G.deckCount[0] = deckSize;

    playAdventurer(&G, 0);
    c = numHandCards(&G);

    assert(c == handCount + 2);

    printf("All tests passed!\n");

    return 0;
}
