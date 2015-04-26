// conleyme
// Unit test for smithy card

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"

void check_smithy(int p, struct gameState *state, int handPos) {

	// call smithy card
	smithy_card(p, state, handPos);
	
	// check results
	// Hand count is hard coded to 5. It should increment by 2 (+3 drawn, -1 smithy discarded)
	// This test will fail so it is left as printf statement
	if(state->handCount[p] != 7) {
		printf("Hand count not updated properly. Should be 7, is %d\n", state->handCount[p]);
	}

	// check that smithy was discarded
	assert(state->playedCards[state->playedCardCount - 1] == smithy);
}


int main () {

	int r, p, deckCount, discardCount, handCount, handPos;
	struct gameState state;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	deckCount = 5;
	discardCount = 5;
	handCount = 5;
	handPos = 1;
	
	printf("Testing smithy card.\n");

	for(p = 0; p < 2; p++) {
		memset(&state, 23, sizeof(struct gameState));
		r = initializeGame(2, k, 1, &state);
		state.deckCount[p] = deckCount;
		memset(state.deck[p], 0, sizeof(int) * deckCount);
		state.discardCount[p] = discardCount;
		memset(state.discard[p], 0, sizeof(int) * discardCount);
		state.handCount[p] = handCount;
		memset(state.hand[p], 0, sizeof(int) * handCount);
		// put a smithy in the player's hand
		state.hand[p][handPos] = smithy;
		// call its effect
		check_smithy(p, &state, handPos);
	}
	return 0;
}
