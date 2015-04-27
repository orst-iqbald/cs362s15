/* -----------------------------------------------------------------------
 * Testing the council room card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int i, p;
    int seed = 1000;
    int numPlayer = 4;
    int player;
    int cardsHandBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING council room card:\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain a council room and play it
    player = whoseTurn(&state);
    gainCard(council_room, &state, 2, player);
    cardsHandBefore = numHandCards(&state);
    playCard(numHandCards(&state) - 1, -1, -1, -1, &state);
    assert(cardsHandBefore == numHandCards(&state) - 3);
    assert(state.numBuys == 2);
    // Check that the other players have gained a card
    for (i = 1; i < numPlayer; i++) {
        p = player + i;
        if (p == numPlayer) {
            p = 0;
        }
        if (state.handCount[p] != 6) {
            printf("FAILED: player %d has %d cards, should have 6\n", p, state.handCount[p]);
        }

        //assert(state.handCount[p] == 6);
    }

    //printf("All tests passed!\n");

    return 0;
}
