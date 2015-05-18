#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

void check_cutpurse(int pos, int turn, struct gameState *state) {

        int coin_count;
        int copper_count[4] = {0, 0, 0, 0};
	struct gameState pre;
	memcpy(&pre, state, sizeof(struct gameState));

        // initial coin count
        updateCoins(turn, state, 0);

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
        cutpurse_card(pos, turn, state);

        // check if coins increased by 2 for current player
        assert(state->coins == (coin_count+2));

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
	
	// update hands
	pre.handCount[turn]--;
	pre.playedCardCount++;

	for(int i = 0; i < 4; i++) {
		if((i != turn)) {
			if(copper_count[i] == 1) {
				pre.handCount[i]--;
				pre.playedCardCount++;
	//			pre.discardCount[i]++;
			}
		}
	}

	
	for(int i = 0; i < 4; i++) {
		if(pre.handCount[i] != state->handCount[i]) {
			printf("Bad hand count for player %d\n", i);
		}
	//	if(pre.discardCount[i] != state->discardCount[i]) {
	//		printf("Bad discard count for player %d, pre: %d post: %d\n", i, pre.discardCount[i], state->discardCount[i]);
	//	}
	}
	if(pre.playedCardCount != state->playedCardCount) {
		printf("Bad played card count. Pre: %d post: %d\n", pre.playedCardCount, state->playedCardCount);
	}
}

int main() {

        int players = 4;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        int seed = 1000;
        struct gameState state;
        int r;
	int tests = 10;
	int player;

	srand(time(NULL));

        printf("Testing cutpurse card.\n");

	for(int i = 0; i < tests; i++) {

        	// initialize game
	        memset(&state, 23, sizeof(struct gameState));
        	r = initializeGame(players, k, seed, &state);

		player = rand() % players;
		state.whoseTurn = player;

		// initialize for all 4 players
		for(int i = 0; i < players; i++) {
			state.deckCount[i] = rand() % MAX_DECK;
			state.discardCount[i] = rand() % MAX_DECK;
			state.handCount[i] = rand() % MAX_HAND;
		}
		state.playedCardCount = rand() % 4 + 1;

		// give current player valid hand with a cutpurse card
		for(int i = 0; i <= state.handCount[player]; i++) {
			state.hand[player][i] = rand() % treasure_map;
		}
		int pos = rand() % state.handCount[player];
		state.hand[player][pos] = cutpurse;

		// give other players coppers + others
		for(int i = 0; i < players; i++) {
			if(i != player) {
				for(int j = 0; j <= state.handCount[i]; j++) {
					if(rand() % 2 == 0) {
						state.hand[i][j] = copper;
					} else {
						state.hand[i][j] = rand() % treasure_map;
					}
				}
			}
		}
        	check_cutpurse(pos, player, &state);
	}
        return 0;
}

