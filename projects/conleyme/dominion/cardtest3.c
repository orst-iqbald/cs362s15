#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define PLAYERS 2

void check_council(struct gameState *state) {

        int buys;
        int hands[PLAYERS];
        for(int i = 0; i < PLAYERS; i++) {
                hands[i] = state->handCount[i];
        }
        buys = state->numBuys;

        // put card into player's hand
        state->hand[0][0] = council_room;

        council_room_card(0, 0, state);

        // check hand counts
        // current player should have 3 additional cards, other players each have 1
        // This test will fail so printf statements are left
        for(int i = 0; i < PLAYERS; i++) {
                if(i == 0) {
                        if(state->handCount[i] != (hands[i] + 3)) {
                                printf("Player 1 hand count incorrect. Should have %d cards, has %d cards.\n", (hands[i]+3), state->handCount[i]);
                        }
                } else {
                        if(state->handCount[i] != (hands[i] + 1)) {
                                printf("Player 2 hand count incorrect. Should have %d cards, has %d cards.\n", (hands[i]+1), state->handCount[i]);
                        }
                }
        }

        // check number of buys
        assert(state->numBuys == (buys+1));

        // check if council room was discarded
        assert(state->playedCards[state->playedCardCount - 1] == council_room);

}

int main() {

        int players = 2;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        int seed = 1000;
        struct gameState state;
        int r;
	int handCount = 5;

	printf("Checking council room card.\n");

        // initialize game
        memset(&state, 23, sizeof(struct gameState));
        r = initializeGame(players, k, seed, &state);
        state.handCount[0] = handCount;
        memset(state.hand[0], 0, sizeof(int) * handCount);
        check_council(&state);
        return 0;
}                       
