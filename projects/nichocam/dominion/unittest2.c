#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//shuffle
int main() {

	//Initializing game state
	struct gameState *test1 = malloc(sizeof(struct gameState));
	struct gameState *test2 = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(3, cards, 55555, test1);     //My favorite number is 5 so the seed is 5 5's
	memcpy(test2, test1, sizeof(struct gameState));

	printf("Start of Shuffle test\n");

	//Test 1: Shuffle shuffles
	shuffle(1, test1);
	if (memcmp(test1, test2, sizeof(struct gameState)) == 0)
		printf("\n!!!!!\nTest 1 failed.\n!!!!!\n\n");
	else
		printf("Test 1 passed.\n");

	//Test 2: Shuffle shuffles differently
	memcpy(test1, test2, sizeof(struct gameState)); //restore previous game state.
	shuffle(1, test2);
	if (memcmp(test1, test2, sizeof(struct gameState)) == 0)
		printf("\n!!!!!\nTest 2 failed.\n!!!!!\n\n");
	else
		printf("Test 2 passed.\n");

	//Test 3: Empty Deck
	test1->deckCount[1] = 0;
	if (shuffle(1, test1) != -1)
		printf("\n!!!!!\nTest 3 failed.\n!!!!!\n\n");
	else
		printf("Test 3 passed.\n");

	return 0;
}
