/* -----------------------------------------------------------------------
 * Testing the gainCard() function
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, res;
    int seed = 1000;
    int numPlayer = 2;
    int player;
    int cardsHandBefore;
    int discardBefore;
    int deckBefore;
    int supplyBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING gainCard():\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain an adventurer card to discard pile
    player = whoseTurn(&state);
    discardBefore = state.discardCount[player];
    supplyBefore = state.supplyCount[adventurer];
    gainCard(adventurer, &state, 0, player);
    assert(discardBefore == state.discardCount[player] - 1);
    assert(supplyBefore == state.supplyCount[adventurer] + 1);
    endTurn(&state);

    // Gain a council room card to deck
    player = whoseTurn(&state);
    deckBefore = state.deckCount[player];
    supplyBefore = state.supplyCount[council_room];
    gainCard(council_room, &state, 1, player);
    assert(deckBefore == state.deckCount[player] - 1);
    assert(supplyBefore == state.supplyCount[council_room] + 1);
    endTurn(&state);

    // Gain a feast card to hand
    player = whoseTurn(&state);
    cardsHandBefore = numHandCards(&state);
    supplyBefore = state.supplyCount[feast];
    gainCard(feast, &state, 2, player);
    assert(cardsHandBefore == numHandCards(&state) - 1);
    assert(supplyBefore == state.supplyCount[feast] + 1);
    endTurn(&state);

    // Draw all mine cards
    for (i = 0; i < 10; i++) {
        player = whoseTurn(&state);
        gainCard(mine, &state, 1, player);
        endTurn(&state);
    }

    // Attempt to draw a mine card
    player = whoseTurn(&state);
    res = gainCard(mine, &state, 1, player);
    assert(res == -1);

    printf("All tests passed!\n");

    return 0;
}
