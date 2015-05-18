#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main () {

	//Initializing game state
	struct gameState *test1 = malloc(sizeof(struct gameState));
	struct gameState *test2 = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(3, cards, 55555, test1);     //My favorite number is 5 so the seed is 5 5's
	test1->hand[0][0] = adventurer;             //ensure adventurer is in the hand
	test1->hand[0][1] = mine;             //ensure adventurer is not second
	memcpy(test2, test1, sizeof(struct gameState));
	
	printf("Start of Adventurer test\n"); //Opening message
	
	playCard(0, -1, -1, -1, test1);
	
	printf("test 1: new cards\n");

	if (memcmp(test1, test2, sizeof(struct gameState)) == 0)
		printf("\n!!!!!\nTest 1 failed.\n!!!!!\n\n");
	else
		printf("Test 1 passed.\n");

	printf("test 2: discard\n");
	if (test1->hand[0][0] == adventurer)
		printf("\n!!!!!\nTest 2 failed.\n!!!!!\n\n");
	else
		printf("Test 2 passed.\n");


	return 0;
}
