/* -----------------------------------------------------------------------
 * Testing the adventurer card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Counts the number of treasure cards in the player's hand
int numTreasureCards(struct gameState *state, int player);

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int player;
    int cardsHandBefore;
    int discardBefore;
    int deckBefore;
    int treasureBefore;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState state;

    printf ("TESTING adventurer card:\n");

    initializeGame(numPlayer, k, seed, &state); // initialize a new game

    // Gain an adventurer card to hand and play
    player = whoseTurn(&state);
    gainCard(adventurer, &state, 2, player);
    treasureBefore = numTreasureCards(&state, player);
    cardsHandBefore = numHandCards(&state);
    deckBefore = state.deckCount[player];
    discardBefore = state.discardCount[player];
    playCard(numHandCards(&state) - 1, -1, -1, -1, &state);
//    if (treasureBefore != numTreasureCards(&state, player) - 2) {
//        printf("FAILED: treasure cards in hand is %d, should be %d\n",
//               numTreasureCards(&state, player), treasureBefore + 2);
//    }
    assert(treasureBefore == numTreasureCards(&state, player) - 2);
    if (cardsHandBefore != numHandCards(&state) - 1) {
        printf("FAILED:  cards in hand is %d, should be %d\n", numHandCards(&state), cardsHandBefore + 1);
    }
    //assert(cardsHandBefore == numHandCards(&state) - 1);
//    if (deckBefore + discardBefore != state.deckCount[player] + state.discardCount[player] + 2) {
//        printf("FAILED:  the sum of the cards in deck and discard is %d, should be %d\n",
//               state.deckCount[player] + state.discardCount[player], deckBefore + discardBefore - 2);
//    }
    assert(deckBefore + discardBefore == state.deckCount[player] + state.discardCount[player] + 2);


    //printf("All tests passed!\n");

    return 0;
}

int numTreasureCards(struct gameState *state, int player) {
    int i;
    int treasures = 0;
    for (i = 0; i < state->handCount[player]; i++) {
        if (state->hand[player][i] == copper) {
            treasures = treasures + 1;
        } else if (state->hand[player][i] == silver) {
            treasures = treasures + 1;
        } else if (state->hand[player][i] == gold) {
            treasures = treasures + 1;
        }
    }

    return treasures;
}
