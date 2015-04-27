/* -----------------------------------------------------------------------
 * Unit test for gainCard(), which tests that the card is added to the correct
 * one of discard, deck, or hand, that it does nothing if the supply pile is
 * empty, and that it decrements the amount in the supply pile.
 * 
 * Lines in makefile:
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
	int theCard = adventurer;
	int thePlayer = 0;
	int result;
	
	// Test adding it to discard pile
	gainCard(theCard, state, 0, thePlayer);
	// check it's in the player's discard (last)
	if (state->discard[thePlayer][ state->discardCount[thePlayer]-1 ] != theCard)
	{
		printf("gainCard(): FAIL on adding to discard pile\n");
		numFailures++;
	}
	// check the supply was decremented
	if (state->supplyCount[theCard] != 9)
	{
		printf("gainCard(): FAIL on decrementing supply when adding to discard\n");
		numFailures++;
	}
	
	// Test adding it to deck
	gainCard(theCard, state, 1, thePlayer);
	// check it's in the player's deck (last)
	if (state->deck[thePlayer][ state->deckCount[thePlayer]-1 ] != theCard)
	{
		printf("gainCard(): FAIL on adding to deck\n");
		numFailures++;
	}
	// check the supply was decremented
	if (state->supplyCount[theCard] != 8)
	{
		printf("gainCard(): FAIL on decrementing supply when adding to deck\n");
		numFailures++;
	}
	
	// Test adding it to hand
	gainCard(theCard, state, 2, thePlayer);
	// check it's in the player's hand (last)
	if (state->hand[thePlayer][ state->handCount[thePlayer]-1 ] != theCard)
	{
		printf("gainCard(): FAIL on adding to hand\n");
		numFailures++;
	}
	// check the supply was decremented
	if (state->supplyCount[theCard] != 7)
	{
		printf("gainCard(): FAIL on decrementing supply when adding to hand\n");
		numFailures++;
	}
	
	// Test trying to gain when there is no supply
	state->supplyCount[theCard] = 0;
	result = gainCard(theCard, state, 0, thePlayer);
	// check returned -1
	if (result != -1)
	{
		printf("gainCard(): FAIL on catching empty supply pile\n");
		numFailures++;
	}
	// check didn't decrement supply further (function didn't do anything)
	if (state->supplyCount[theCard] != 0)
	{
		printf("gainCard(): FAIL on handling empty supply pile\n");
		numFailures++;
	}
	
	// overall results
	if (numFailures == 0)
	{
		printf("gainCard(): PASSed all tests.\n");
	}
	else
	{
		printf("gainCard(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}