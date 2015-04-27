/* -----------------------------------------------------------------------
 * Testing the scoreFor() function
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
    int player;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING scoreFor():\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    if (scoreFor(0, &state) != 3) {
        printf("FAILED: score is %d, should be 3\n", scoreFor(0, &state));
    }
    if (scoreFor(1, &state) != 3){
        printf("FAILED: score is %d, should be 3\n", scoreFor(1, &state));
    }

    // Give player 1 some more money
    endTurn(&state);
    player = whoseTurn(&state);
    while (state.coins < 6) {
        drawCard(player, &state);
        updateCoins(player, &state, 0);
    }
    buyCard(gold, &state);
    endTurn(&state);

    // Player 0 buys 5 estate cards and player 1 buys 5 province cards
    for (i = 0; i < 5; i++) {
        player = whoseTurn(&state);
        while (state.coins < 2) {
            drawCard(player, &state);
            updateCoins(player, &state, 0);
        }
        buyCard(estate, &state);
        endTurn(&state);

        player = whoseTurn(&state);
        while (state.coins < 8) {
            drawCard(player, &state);
            updateCoins(player, &state, 0);
        }
        buyCard(province, &state);
        endTurn(&state);
    }

    if (scoreFor(0, &state) != 8) {
        printf("FAILED: score is %d, should be 8\n", scoreFor(0, &state));
    }
    if (scoreFor(1, &state) != 33) {
        printf("FAILED: score is %d, should be 33\n", scoreFor(1, &state));
    }

    // Player 0 buys 5 duchy cards and player 1 buys 5 curse cards
    for (i = 0; i < 5; i++) {
        player = whoseTurn(&state);
        updateCoins(player, &state, 5);
        buyCard(duchy, &state);
        endTurn(&state);

        buyCard(curse, &state);
        endTurn(&state);
    }

    if (scoreFor(0, &state) != 23) {
        printf("FAILED: score is %d, should be 23\n", scoreFor(0, &state));
    }
    if (scoreFor(1, &state) != 28) {
        printf("FAILED: score is %d, should be 28\n", scoreFor(1, &state));
    }

    // Player 0 buys 3 gardens and player 1 buys 3 great halls
    for (i = 0; i < 3; i++) {
        player = whoseTurn(&state);
        updateCoins(player, &state, 4);
        buyCard(gardens, &state);
        endTurn(&state);

        player = whoseTurn(&state);
        updateCoins(player, &state, 3);
        buyCard(great_hall, &state);
        endTurn(&state);
    }

    if (scoreFor(0, &state) != 25) {
        printf("FAILED: score is %d, should be 25\n", scoreFor(0, &state));
    }
    if (scoreFor(1, &state) != 31) {
        printf("FAILED: score is %d, should be 31\n", scoreFor(1, &state));
    }

    return 0;
}
