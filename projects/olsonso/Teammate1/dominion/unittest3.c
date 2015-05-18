#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//discardCard
int main() {

	//Initializing game state
	struct gameState *test = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(3, cards, 55555, test);     //My favorite number is 5 so the seed is 5 5's
	
	printf("Start of discardCard test\n");
	
	//Set hand for testing
	int test_hand[5] = { adventurer, council_room, feast, gardens, mine };
	memcpy(test->hand[0], test_hand, sizeof(int)* 5);
	int hand_count = test->handCount[0];

	//Test 1: Discarded card is played
	discardCard(test->handCount[0] - 1, 0, test, 0);

	if (test->handCount[0] != (hand_count - 1))
		printf("\n!!!!!\nTest 1 failed hand count.\n!!!!!\n\n");
	hand_count--;
	if (test->hand[0][test->handCount[0]-1] == mine)
		printf("\n!!!!!\nTest 1 failed to discard.\n!!!!!\n\n");
	if (test->hand[0][test->handCount[0] - 1] == gardens){
		if (test->playedCards[test->playedCardCount - 1] != mine)
			printf("\n!!!!!\nTest 1 failed to place discarded card in played pile.\n!!!!!\n\n");
		else
			printf("Test 1 passed.\n");
	}

	//Test 2: Discarded card is not played
	discardCard(2, 0, test, 1);

	if (test->handCount[0] != (hand_count - 1))
		printf("\n!!!!!\nTest 2 failed hand count.\n!!!!!\n\n");
	hand_count--;
	if (test->hand[0][2] == feast)
		printf("\n!!!!!\nTest 2 failed to discard.\n!!!!!\n\n");
	if (test->hand[0][test->handCount[0] - 1] == gardens){
		if (test->playedCards[test->playedCardCount - 1] == feast)
			printf("\n!!!!!\nTest 2 failed to, discarded card in played pile.\n!!!!!\n\n");
		else
			printf("Test 2 passed.\n");
	}

	//Test 3: Trash all cards in hand
	for (; hand_count > 0; hand_count--)
		discardCard(0, 0, test, 0);
	if (test->handCount[0] != 0)
		printf("\n!!!!!\nTest 3 failed to remove all cards.\n!!!!!\n\n");
	else
		printf("Test 3 passed.\n");
	//Test 4: Discard from empty hand
	discardCard(0, 0, test, 0);

		return 0;
}
