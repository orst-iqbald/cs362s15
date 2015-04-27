/* -----------------------------------------------------------------------
 * Testing the village card
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
    int actionsBefore;
    int buysBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING village card:\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain a village card and play it
    player = whoseTurn(&state);
    gainCard(village, &state, 2, player);
    cardsHandBefore = numHandCards(&state);
    actionsBefore = state.numActions;
    buysBefore = state.numBuys;
    playCard(numHandCards(&state) - 1, -1, -1, -1, &state);
    assert(cardsHandBefore == numHandCards(&state));
    assert(buysBefore == state.numBuys);
    assert(actionsBefore == state.numActions - 1);
    endTurn(&state);

    // Try to play a village card with no more actions left
    player = whoseTurn(&state);
    gainCard(village, &state, 2, player);
    state.numActions = 0;
    cardsHandBefore = numHandCards(&state);
    actionsBefore = state.numActions;
    buysBefore = state.numBuys;
    playCard(numHandCards(&state) - 1, -1, -1, -1, &state);
    assert(cardsHandBefore == numHandCards(&state));
    assert(buysBefore == state.numBuys);
    assert(actionsBefore == state.numActions);
    endTurn(&state);



    printf("All tests passed!\n");

    return 0;
}
