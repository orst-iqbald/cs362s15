/* -----------------------------------------------------------------------
 * Testing the discardCard() function
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
    int playedBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING discardCard():\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain a mine card and discard it
    player = whoseTurn(&state);
    gainCard(mine, &state, 2, player);
    cardsHandBefore = numHandCards(&state);
    playedBefore = state.playedCardCount;
    discardCard(numHandCards(&state) - 1, player, &state, 0);
    assert(cardsHandBefore == numHandCards(&state) + 1);
    assert(playedBefore == state.playedCardCount - 1);
    endTurn(&state);

    // Gain a smithy card and trash it
    player = whoseTurn(&state);
    gainCard(smithy, &state, 2, player);
    cardsHandBefore = numHandCards(&state);
    playedBefore = state.playedCardCount;
    discardCard(numHandCards(&state) - 1, player, &state, 1);
    assert(cardsHandBefore == numHandCards(&state) + 1);
    assert(playedBefore == state.playedCardCount);
    endTurn(&state);

    printf("All tests passed!\n");

    return 0;
}
