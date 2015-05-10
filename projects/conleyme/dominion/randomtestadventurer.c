#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

void check_adventurer(int p, struct gameState *state) {

        int temphand[MAX_HAND];
        int z = 0;
        int cardDrawn =0;
        int card;
        int drawnTreasure = 0;
        int checkTreasure = 0;
	int postTreasure = 0;
	int cop1 = 0;
	int sil1 = 0;
	int gol1 = 0;

	int cop2 = 0;
	int sil2 = 0;
	int gol2 = 0;

	int prehand = state->handCount[p];

        // get number of treasure cards/adventurer in hand before adventurer effect
        for(int i = 0; i < state->handCount[p]; i++) {
                card = state->hand[p][i];
                if(card == copper) {
			cop1++;
                        checkTreasure++;
		} else if(card == silver) {
			sil1++;
			checkTreasure++;
                } else if(card == gold) {
			gol1++;
			checkTreasure++;
		}
        }

        // call card
        adventurer_card(state, temphand, drawnTreasure, z, p, cardDrawn);

        // check effect of card
        for(int i = 0; i < state->handCount[p]; i++) {
                card = state->hand[p][i];
                if(card == copper) {
			cop2++;
                        postTreasure++;
                } else if(card == silver) {
			sil2++;
                        postTreasure++;
                } else if(card == gold) {
			gol2++;
                        postTreasure++;
                }

        }

	//printf("Before: %d treasure %d copper %d silver %d gold\n", checkTreasure, cop1, sil1, gol1);
	//printf("After: %d treasure %d copper %d silver %d gold\n", postTreasure, cop2, sil2, gol2);

	int diff = checkTreasure - postTreasure;

	if(diff != -2) {
		printf("Difference is %d\n", diff);
	}

	if(state->handCount[p] != (prehand + 2)) {
		printf("Hand count is incorrect.\n");
	}

	if(cop1 - cop2 == 0) {
		printf("Kept 0 copper\n");
	}
}

int main() {

        int players = 2;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        int seed = 1000;
        struct gameState state;
	int player;
        int r;
	int card;
	int tests = 10;

	srand(time(NULL));

        printf("Testing adventurer card.\n");

	for(int i = 0; i < tests; i++) {

        	// initialize random gamestate
	
		r = initializeGame(players, k, seed, &state);

		player = floor(rand() % players);
		state.whoseTurn = player;
		
		// test empty deck condition
		if(rand() % 4 == 0) {
			state.deckCount[player] = 0;
		} else {
			state.deckCount[player] = rand() % MAX_DECK;
		}
		state.discardCount[player] = rand() % MAX_DECK;
		state.handCount[player] = rand() % MAX_HAND;
		state.playedCardCount = rand() % MAX_DECK;

		// give player a valid hand
		for(int i = 0; i <= state.handCount[player]; i++) {
			state.hand[player][i] = floor(Random() * 28);
		}
		// put treasure cards in deck
		for(int i = 0; i <= state.deckCount[player]; i++) {
			card = rand() % 6;
			if(card == 0) {
				state.deck[player][i] = gold;
			} else if (card == 1) {
				state.deck[player][i] = silver;
			} if (card == 2 || card == 3) {
				state.deck[player][i] = copper;
			} else {
				state.deck[player][i] = (rand() % treasure_map);
			}
		}

		// fill discard pile
		for(int i = 0; i <= state.discardCount[player]; i++) {
			state.discard[player][i] = floor(Random() * 28);
		}

		// put adventurer card in hand
		int pos = rand() % state.handCount[player];
		state.hand[player][pos] = adventurer;

	        check_adventurer(player, &state);
	}
        return 0;
}

