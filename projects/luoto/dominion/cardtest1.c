/**
 * Unit Tests for the card int smithyCard(int handPos, int currentPlayer, struct gameState *state)
 *
 * + 3 Cards
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

    // initialize game
    initializeGame(numPlayer, k, seed, &G);

    // begin test
    printf ("TESTING smithyCard():\n");

    G.hand[1][5] = smithy; // give player a smithyCard at hand position 5;
    G.playedCards[0] = 0;
    G.playedCardCount = 0;

    G.handCount[1] = 6; // current has 6 cards in hand
    printf("Player 1 currently has %d card(s) in hand\n", G.handCount[1]);
    smithyCard(5, 1, &G); // play smithy card
    printf("Cards in hand = %d, expected cards in hand = %d\n", G.handCount[1], 8);
    printf("Cards in play = %d\n, expected cards in play = %d\n", G.playedCardCount, 1);

    assert(G.playedCardCount == 1);
    // assert(G.handCount[1] == 6 + 3 - 1); // should have 8 cards in hand
    
    return 0;
}

// getting extra card in hand