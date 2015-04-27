#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void check_adventurer(int p, struct gameState *state) {

	int temphand[MAX_HAND];
	int z = 0;
	int cardDrawn =0;
	int card;
	int drawnTreasure = 0;
	int checkTreasure = 0;
	int checkAdventurer = 0;
	int checkPost = 0;

	// get number of treasure cards/adventurer in hand before adventurer effect
        for(int i = 0; i < state->handCount[p]; i++) {
                card = state->hand[p][i];
                if(card == copper || card == silver || card == gold) {
                        checkTreasure++;
                } else if (card == adventurer) {
			checkAdventurer++;
		}
        }

	// call card
	adventurer_card(state, temphand, drawnTreasure, z, p, cardDrawn);

	// check effect of card
	// post game state should have 2 more treasure cards
	for(int i = 0; i < state->handCount[p]; i++) {
		card = state->hand[p][i];
		if(card == copper || card == silver || card == gold) {
			checkTreasure--;
		} else if (card == adventurer) {
			checkPost++;
		}
	}

	// Printf statement as this test will fail
	if(checkTreasure != -2) {
		printf("Hand does not have 2 additional treasure cards, it has %d.\n", checkTreasure);
	}
	
	// subtract number of adventurer cards in hand after effect from number before
	// there should be one fewere adventurer card in hand
	int diff = checkAdventurer - checkPost;

	// check if adventurer was discarded - should have 1 fewer adventurer cards
	assert(diff == 1);
	
}

int main() {

	int players = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState state;	
	int r;

	printf("Testing adventurer card.\n");

	// initialize game
	memset(&state, 23, sizeof(struct gameState));
	r = initializeGame(players, k, seed, &state);

	// put adventurer in player 0's hand
	state.hand[0][0] = adventurer;

	check_adventurer(0, &state);

	return 0;
}
