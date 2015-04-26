#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

void check_cutpurse(struct gameState *state) {

	int turn = whoseTurn(state);
	int coin_count;
	int copper_count[4] = {0, 0, 0, 0};
	
	// put cutpurse card into current player's hand and next player's hand
	state->hand[turn][0] = cutpurse;

	// give player 2 an entire hand of coppers
	for(int i = 0; i < state->handCount[2]; i++) {
		state->hand[2][i] = copper;
	}

	// initial coin count
	coin_count = state->coins;
	
	// initial copper count per player
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < state->handCount[i]; j++) {
			if(state->hand[i][j] == copper) {
				copper_count[i]++;
			}
		}
	}

	// call cutpurse
	cutpurse_card(0, turn, state);
	
	// check if coins increased by 1 - +2 bonus for current player, -1 copper from player 2
	assert(state->coins == (coin_count+1));

	// update copper counts for all players except 1
	for(int i = 0; i < 4; i++) {	
		if(i != turn && copper_count[i] > 0) {
			for(int j = 0; j < state->handCount[i]; j++) {
				if(state->hand[i][j] == copper) {
					copper_count[i]--;
				}
			}
			if(copper_count[i] != 1) {
                        	printf("Error removing coppers. Copper count should be 1, is %d\n", copper_count[i]);
			}
		}
	}	

	// check if cutpurse was discarded
	assert(state->playedCards[state->playedCardCount - 1] == cutpurse);
}

int main() {

        int players = 4;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        int seed = 1000;
        struct gameState state;
        int r;

	printf("Testing cutpurse card.\n");

        // initialize game
        memset(&state, 23, sizeof(struct gameState));
        r = initializeGame(players, k, seed, &state);
        check_cutpurse(&state);
        return 0;
}
