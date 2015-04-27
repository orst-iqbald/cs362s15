/*------------------------------------------------------------------
 * Card test #1: smithyCard() card function
 * cardtest1: cardtest1.c dominion.o rngs.o
 *		gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main () {
	int error = 0;
	struct gameState * state = malloc(sizeof(struct gameState));
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	int handC;
	
	printf("smithyCard(): Test Begins");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("smithyCard(): Game initialization failed.\n");
		error = -1;
	}
	
	state->hand[whoseTurn(state)][0] = smithy;
	
	handC = state->handCount[whoseTurn(state)];
	
	smithyCard(state, 0, 0);
	
	if(state->playedCards[state->playedCardCount -1] != smithy)
	{
		printf("smithyCard(): Failed to discard smithy card\n");
		error = -1;
	}
	
	if(state->handCount[whoseTurn(state)] != (handC + 2))
	{
		printf("smithyCard(): Failed to increase the handCount properly\n");
		error  = -1;
	}
	
	if(error != -1)
	{
		printf("smithyCard(): Tests are finished. All tests passed.\n");
	}
	
	free(state);
	return 0;
}