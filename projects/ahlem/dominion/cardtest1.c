/*
 Matthew Ahle
 CS362 Assignment 3
 4/24/2015

 Smithy card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int error = 0;
	/* initialize game variables */
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int handCount;

	/* build gamestate to test */
	struct gameState *state = malloc(sizeof(struct gameState));

	/* initialize gamestate */
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("smithyTest(): Game initialization failed.\n");
		error = -1;
	}

	/* swap smithy card into players hand */
	state->hand[whoseTurn(state)][0] = smithy;

	/* track handCount */
	handCount = state->handCount[whoseTurn(state)];

	/* call effectSmithy function */
	effectSmithy(state, 0);

	/* check that smithy is in discard pile */
	if(state->playedCards[state->playedCardCount - 1] != smithy)
	{
		printf("smithyTest(): Smithy was not discarded properly\n");
		error = -1;
	}

	/* handCount should increment by 2 */
	if(state->handCount[whoseTurn(state)] != (handCount + 2))
	{
		printf("smithyTest(): HandCount was not properly incremented\n");
		error = -1;
	}
	/* if no error then.. */
	if(error != -1)
	{
		printf("smithyTest(): All tests passed.\n");
	}

	free(state);
	return 0;
}