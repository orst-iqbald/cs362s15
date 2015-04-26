/**
 * Unit Tests for the function int drawCard(int player, struct gameState *state)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(void) {
    // game parameters
    int seed = 500;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    // test parameters
    int player = 1;
    int initialHandCards = 3;
    int initialDeckCards = 20;

    // counters
    int i;

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    // begin test
    printf ("TESTING drawCard():\n");

    printf ("Test player %d with %d card(s) and a deck of %d card(s).\n", player, initialHandCards, initialDeckCards);
    G.handCount[player] = initialHandCards;
    G.deckCount[player] = initialDeckCards;
    
    drawCard(player, &G);
    printf("G.handCount[%d] = %d, expected = %d\n", player, G.handCount[player], initialHandCards + 1);
    printf("G.deckCount[%d] = %d, expected = %d\n", player, G.deckCount[player], initialDeckCards - 1);
    assert(G.handCount[player] == initialHandCards + 1);
    assert(G.deckCount[player] == initialDeckCards - 1);

    for(i = 0; i < 10; i++) {
        drawCard(player, &G);
    }
    printf("G.handCount[%d] = %d, expected = %d\n", player, G.handCount[player], initialHandCards + 1 + 10);
    printf("G.deckCount[%d] = %d, expected = %d\n", player, G.deckCount[player], initialDeckCards - 1 - 10);
    assert(G.handCount[player] == initialHandCards + 1 + 10);
    assert(G.deckCount[player] == initialDeckCards - 1 - 10);

    return 0;
}