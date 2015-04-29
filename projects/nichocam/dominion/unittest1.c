#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//isGameOver
int main () {
	
	//Initializing game state
	struct gameState *test = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(3, cards, 55555, test);     //My favorite number is 5 so the seed is 5 5's

	printf("Start of isGameOver test\n"); //Opening message

	//Test 1: False game over. Game has just started and logically is not over.
	if (isGameOver(test) == 1)
		printf("\n!!!!!\nTest 1 failed.\n!!!!!\n\n");
	else
		printf("Test 1 passed.\n");

	//Test 2: Game over when three supply piles are empty.
	int i;

	for (i = 0; i < 3; i++)
		test->supplyCount[i] = 0;

	if (isGameOver(test) == 0)
		printf("\n!!!!!\nTest 2 failed.\n!!!!!\n\n");
	else
		printf("Test 2 passed.\n");

	test->supplyCount[0] = 5;  //Reset supply pile 1 so that it doesn't cause a false positive on the next test.

	//Test 3: Province deck is empty.
	test->supplyCount[province] = 0;

	if (isGameOver(test) == 0)
		printf("\n!!!!!\nTest 3 failed.\n!!!!!\n\n");
	else
		printf("Test 3 passed.\n");

	return 0;
}
