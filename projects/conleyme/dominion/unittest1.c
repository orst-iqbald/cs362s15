#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define PLAYERS 2
#define MAX_BONUS 10
#define MAX_HAND_COUNT 10
#define TEST_DEBUG 1

int calculate(int count, int card, int bonus);
void fill_hand(struct gameState *state, int player, int card);
int get_coins(struct gameState *state, int player, int bonus);

int calculate(int count, int card, int bonus) {

	switch(card) {

		case copper: 
			return count + bonus;
		case silver:
			return (count * 2) + bonus;
		case gold:
			return (count * 3) + bonus;
		default: // not a treasure card
			return bonus;

	}
	return -1; // should not get here
}

void fill_hand(struct gameState *state, int player, int card) {

	for(int i = 0; i < state->handCount[player]; i++) {
		state->hand[player][i] = card;
	}
}

int get_coins(struct gameState *state, int player, int bonus) {
	if(updateCoins(player, state, bonus) == 0) {
		return state->coins;
	}
	else {
		return -1;
	}
}

int main () {

	int seed = 1000;
	int p, r, handCount;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;
	
	printf("Testing updateCoins function\n");
	for (p = 0; p < MAX_PLAYERS; p++) {
		for(handCount = 1; handCount <= MAX_HAND_COUNT; handCount++) {
			for(bonus = 0; bonus <= MAX_BONUS; bonus++) {
				memset(&state, 23, sizeof(struct gameState));
				r = initializeGame(MAX_PLAYERS, k, seed, &state);
				state.handCount[p] = handCount;
				// Check coins for all coppers
				fill_hand(&state, p, copper);
				assert(calculate(handCount, copper, bonus) == get_coins(&state, p, bonus));
				// Check coins for all silvers
				fill_hand(&state, p, silver);
                                assert(calculate(handCount, silver, bonus) == get_coins(&state, p, bonus));
				// Check coins for all golds
                                fill_hand(&state, p, gold);
                                assert(calculate(handCount, gold, bonus) == get_coins(&state, p, bonus));
				// Check coins for all non-treasure
                                fill_hand(&state, p, smithy);
                                assert(calculate(handCount, smithy, bonus) == get_coins(&state, p, bonus));
			}
		}
	}

	return 0;
}
