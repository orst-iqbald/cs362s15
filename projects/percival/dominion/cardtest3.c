/* -----------------------------------------------------------------------
 * Unit test for cardEffectGreatHall(), which implements the GreatHall card. 
 * Tests that the player's hand grows by 1 card, the number of actions
 * increases by 1, and the Great Hall card is added to the played pile.
 * 
 * Lines in makefile:
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	state->hand[0][0] = great_hall;	//make sure there's a great hall in their hand
	
	// Test the cardEffectGreatHall function
	int initialHandCount = state->handCount[0];
	int initialNumActions = state->numActions;
	cardEffectGreatHall(0, state, 0);
	// check that there's 1 more card in the player's hand
	// (count actually stays same because also lost 1 for the discarded Great Hall)
	if (state->handCount[0] != initialHandCount)
	{
		printf("cardEffectGreatHall(): FAIL on adding a card to player's hand\n");
		numFailures++;
	}
	// check that there's 1 more action available
	if (state->numActions != (initialNumActions + 1))
	{
		printf("cardEffectGreatHall(): FAIL on added an action\n");
		numFailures++;
	}
	// check that Great Hall is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != great_hall)
	{
		printf("cardEffectGreatHall(): FAIL on adding card to played pile\n");
		numFailures++;
	}
	
	// overall results
	if (numFailures == 0)
	{
		printf("cardEffectGreatHall(): PASSed all tests.\n");
	}
	else
	{
		printf("cardEffectGreatHall(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}