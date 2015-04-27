#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//whoseTurn
int main() {

	//Initializing game state
	struct gameState *test = malloc(sizeof(struct gameState));
	int cards[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	initializeGame(2, cards, 55555, test);     //My favorite number is 5 so the seed is 5 5's
	int whose_turn = 0;

	printf("Start of whoseTurn test\n");

	//Test 1: STarts with player 1
	if (whoseTurn(test) != whose_turn)
		printf("\n!!!!!\nTest 1 failed.\n!!!!!\n\n");
	else
		printf("Test 1 passed.\n");

	//Test 2: increments after end turn
	whose_turn++;
	endTurn(test);
	if (whoseTurn(test) != whose_turn)
		printf("\n!!!!!\nTest 2 failed.\n!!!!!\n\n");
	else
		printf("Test 2 passed.\n");

	//Test 3: wraps back around
	whose_turn--;
	endTurn(test);
	if (whoseTurn(test) != whose_turn)
		printf("\n!!!!!\nTest 3 failed.\n!!!!!\n\n");
	else
		printf("Test 3 passed.\n");

	//Test 4: Whose turn assumes nothing about the game, and calls no other function
	test->whoseTurn = 5;  //more than the max number of players
	if (whoseTurn(test) != 5)
		printf("\n!!!!!\nTest 4 failed.\n!!!!!\n\n");
	else
		printf("Test 4 passed.\n");


		return 0;
}
