/* -----------------------------------------------------------------------
 * Unit test for cardEffectSmithy(), which implements the Smithy card. Tests
 * that 3 cards are added to the player's hand and the Smithy card is added
 * to the played pile.
 * 
 * Lines in makefile:
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
	int numFailures = 0;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	state->hand[0][0] = smithy;	//make sure there's a smithy in their hand
	
	// Test the cardEffectSmithy function
	int initialHandCount = state->handCount[0];
	cardEffectSmithy(0, 0, state);
	// check that the Smithy is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != smithy)
	{
		printf("cardEffectSmithy(): FAIL on adding card to played pile\n");
		numFailures++;
	}
	// check that handCount has been incremented by 2 (3 cards added, then smithy discarded)
	if (state->handCount[0] != (initialHandCount + 2))
	{
		printf("cardEffectSmithy(): FAIL on properly incrementing handCount\n");
		numFailures++;
	}	
	
	// overall results
	if (numFailures == 0)
	{
		printf("cardEffectSmithy(): PASSed all tests.\n");
	}
	else
	{
		printf("cardEffectSmithy(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}