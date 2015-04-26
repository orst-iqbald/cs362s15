#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define PLAYERS 2

void check_end_turn(struct gameState *post, int turn) {

        struct gameState pre;
        memcpy(&pre, post, sizeof(struct gameState));

	endTurn(post);

	// check that discardCount = pre hand count + pre discard count	
	assert(post->discardCount[0] == (pre.discardCount[0] + pre.handCount[0]));

	// check that top card on discard pile is prevous last card in hand
	assert(post->discard[0][post->discardCount[0]-1] == pre.hand[0][pre.handCount[0]-1]);
	// check that hand has been drawn to 5 cards
	assert(post->handCount[whoseTurn(post)] == 5);

	//check that state variables have been reset
	assert(post->outpostPlayed == 0 && post->phase == 0 && post->numActions == 1 && post->numBuys == 1 && post->playedCardCount == 0);

	// check that after ending turn of last player, the turn loops around back to 0
	endTurn(post);

	if(whoseTurn(post) == 0);
}

int main() {

        int r;

        struct gameState post;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        r = initializeGame(PLAYERS, k, 1000, &post);

	printf("Testing endTurn function.\n");

	check_end_turn(&post, 0);

	return 0;
}
