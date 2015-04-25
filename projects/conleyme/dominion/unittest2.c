// conleyme
// Unit test for discardCard function

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void check_discard(struct gameState *post, int trash, int flag) {

	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int turn = whoseTurn(post);

	if(flag == 1) {
		// case 1: no trash flag, card is last card in hand
		// put a smithy card in player's last pos in hand
		int last = (post->handCount[turn]-1);
		post->hand[turn][last] = smithy;
		if(trash != 1) {
			discardCard(last, turn, post, 0);

        		// test if card is in played pile
	        	assert(post->playedCards[post->playedCardCount-1] == smithy);
	        	assert(post->playedCardCount == (pre.playedCardCount+1));

			// card is last card in hand, so check if card has been removed from player's hand
			assert(post->handCount[turn] == (pre.handCount[turn]-1));
		} else { // trash flag set
			discardCard(last, turn, post, 1);
			// make sure played card count is same as previous
                        assert(post->playedCardCount == pre.playedCardCount);
                        assert(post->handCount[turn] == (pre.handCount[turn]-1));
		}
	} else if (flag == 2) {
		// case 2: no trash flag, card is only card in hand
		// set player's hand count to 1, put smithy in hand
		post->handCount[turn] = 1;
		post->hand[turn][0] = smithy;
		discardCard(0, turn, post, 0);

                // test if card is in played pile
                assert(post->playedCards[post->playedCardCount-1] == smithy);

		// Played card count should have increased by 1
                assert(post->playedCardCount == (pre.playedCardCount+1));

		// hand count should be 0 as only card was discarded
                assert(post->handCount[turn] == 0);
	} else if (flag == 3) {
		// case 3: no trash flag, card is not only card in hand
		// make sure player has a hand of > 1
		post->handCount[turn] = 5;
		// put a smithy card in pos 0 of player's hand
		post->hand[turn][0] = smithy;
		// put a smithy card in pos 4 of player's hand to check post condition
		post->hand[turn][4] = copper;
		
		discardCard(0, turn, post, 0);

                // test if card is in played pile
                assert(post->playedCards[post->playedCardCount-1] == smithy);
                assert(post->playedCardCount == (pre.playedCardCount+1));

		// check that discarded card was replaced by last card in hand
		assert(post->hand[turn][0] == copper);
                // check that hand count was decreased by 1
                assert(post->handCount[turn] == 4);
	}
}

int main() {

	int r;
	int players = 2;

        struct gameState post;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	r = initializeGame(players, k, 1000, &post);

	printf("Testing discardCard function.\n");

	// check case 1: card is last card in hand, no trash flag
	check_discard(&post, 0, 1);
	// check case 1 with trash: card is last card in hand, trash card set
	check_discard(&post, 1, 1);
	// check case 2: card is only card in hand, no trash flag
	check_discard(&post, 0, 2);
	// check case 3: card is not only card in hand, no trash flag
	check_discard(&post, 0, 3);

	return 0;
}
