/* ---------------------------------------------------------------------------------
 * Unit test for testing the effectSmithy() function
 * cardtest1: cardtest1.c dominion.o rngs.o
 * 		gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * ---------------------------------------------------------------------------------
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
	//Initialize game variables
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int handCount;

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("smithyTest(): Game initialization failed.\n");
		error = -1;
	}

	//Swap a smithy card into the players hand
	state->hand[whoseTurn(state)][0] = smithy;

	//Track the handCount
	handCount = state->handCount[whoseTurn(state)];

	//Call the effectSmithy function
	cardSmithy(0, whoseTurn(state), state);

	//Check that the smithy is in the discard pile
	if(state->playedCards[state->playedCardCount - 1] != smithy)
	{
		printf("smithyTest(): Smithy was not discarded properly\n");
		error = -1;
	}

	//handCount should increment by 2 (+3 from smithy, -1 from discarding smithy)
	if(state->handCount[whoseTurn(state)] != (handCount + 2))
	{
		printf("smithyTest(): HandCount was not properly incremented\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("smithyTest(): All tests passed.\n");
	}

	free(state);
	return 0;
}