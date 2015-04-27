/* -----------------------------------------------------------------------
 * Testing the buyCard() function
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int player, r;
    int res;
    int coinsBefore;
    int discardBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING buyCard():\n");

    r = initializeGame(numPlayer, k, seed, &state); // initialize a new game
    player = whoseTurn(&state);

    // Get enough coins to buy village
    while (state.coins < 3) {
        drawCard(player, &state);
        updateCoins(player, &state, 0);
    }

    // Buy village
    coinsBefore = state.coins;
    discardBefore = state.discardCount[player];
    res = buyCard(village, &state);
    assert(res == 0);
    assert(state.numBuys == 0);
    assert(state.phase == 1);
    assert(state.coins == coinsBefore - 3);
    assert(state.discard[player][ state.discardCount[player] ] = village);
    assert(state.discardCount[player] == discardBefore + 1);

    // Attempt to buy village when there are no more buys left
    res = buyCard(village, &state);
    assert(res == -1);

    endTurn(&state);

    // Make it so the player does not have enough coins to buy feast
    state.coins = 1;
    res = buyCard(feast, &state);
    assert(res == -1);
    assert(state.numBuys == 1);

    endTurn(&state);

    // Buy up all the mine cards
    for (i = 0; i < 10; i++) {
        player = whoseTurn(&state);
        while (state.coins < 5) {
            drawCard(player, &state);
            updateCoins(player, &state, 0);
        }
        buyCard(mine, &state);
        endTurn(&state);
    }

    coinsBefore = state.coins;
    res = buyCard(mine, &state);
    assert(res == -1);
    assert(state.numBuys == 1);
    assert(coinsBefore == state.coins);


    printf("All tests passed!\n");

    return 0;
}
