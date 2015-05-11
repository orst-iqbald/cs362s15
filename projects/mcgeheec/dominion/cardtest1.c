/* -----------------------------------------------------------------------
 * Testing the smithy card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int player;
    int cardsHandBefore;
    int discardBefore;
    int deckBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING smithy card:\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain a smithy card to hand and play
    player = whoseTurn(&state);
    gainCard(smithy, &state, 2, player);
    cardsHandBefore = numHandCards(&state);
    discardBefore = state.discardCount[player];
    deckBefore = state.deckCount[player];
    playCard(numHandCards(&state) - 1, -1, -1, -1, &state);
    if (cardsHandBefore != numHandCards(&state) - 2) {
        printf("FAILED: cards in hand is %d, should be %d\n", numHandCards(&state), cardsHandBefore + 2);
    }
    //assert(cardsHandBefore == numHandCards(&state) - 2);

    assert(discardBefore == state.discardCount[player]);
    if (deckBefore != state.deckCount[player] + 3) {
        printf("FAILED: cards in deck is %d, should be %d\n", state.deckCount[player], deckBefore - 3);
    }
    //assert(deckBefore == state.deckCount[player] + 3);

    //printf("All tests passed!\n");

    return 0;
}
