#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main() {

	//Initializing game state
	struct gameState *test = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(3, cards, 55555, test);     //My favorite number is 5 so the seed is 5 5's
	test->hand[0][0] = smithy;             //ensure smithy is in the hand
	test->hand[0][1] = mine;             //ensure second card is not smithy

	printf("Start of smithy test\n"); //Opening message

	assert(test->handCount[0] == 5); //Standard hand size

	playCard(0, -1, -1, -1, test);

	assert(test->handCount[0] == 7); //5+3-1=7
	assert(test->hand[0][0] != smithy); // smithy was actually discarded

	printf("no bugs with Smithy\n");

	return 0;
}
