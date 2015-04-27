/* -----------------------------------------------------------------------
 * Unit test for buyCard(), which tests that a successful buy is added to the
 * player's discard pile, decrements the coins variable correctly, reduces
 * numBuys by 1, and changes the phase. It also makes sure that an attempt to 
 * buy will fail if there are no buys left, the requested card has no supply, or 
 * the requested card costs more than the number of coins available.
 * 
 * Lines in makefile:
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int result;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	state->coins = 6;	//make sure have enough for buy to be successful
	
	// Test a successful buy
	int initialCoins = state->coins;
	int initialBuys = state->numBuys;
	buyCard(adventurer, state);
	// check the card was added to their discard pile (last)
	if (state->discard[0][ state->discardCount[0]-1 ] != adventurer)
	{
		printf("buyCard(): FAIL on adding card to discard pile\n");
		numFailures++;
	}
	// check the coins were used (coins variable decremented)
	if (state->coins != (initialCoins - getCost(adventurer)))
	{
		printf("buyCard(): FAIL on decrementing number of coins\n");
		numFailures++;
	}
	// check the number of remaining buys was decremented by 1
	if (state->numBuys != (initialBuys - 1))
	{
		printf("buyCard(): FAIL on decrementing number of buys\n");
		numFailures++;
	}
	// check that the phase changes
	if (state->phase != 1)
	{
		printf("buyCard(): FAIL on changing the phase\n");
		numFailures++;
	}
	
	// Test an attempted buy with no buys available
	state->numBuys = 0;
	result = buyCard(adventurer, state);
	if (result != -1)
	{
		printf("buyCard(): FAIL on verifying have buys available\n");
		numFailures++;
	}
	state->numBuys = 1;		//reset so doesn't keep causing failures for others
	
	// Test an attempted buy with no supply available
	state->supplyCount[adventurer] = 0;
	result = buyCard(adventurer, state);
	if (result != -1)
	{
		printf("buyCard(): FAIL on verifying have supply available\n");
		numFailures++;
	}
	
	// Test an attempted buy with insufficient coins	
	state->coins = 0;
	result = buyCard(smithy, state);
	if (result != -1)
	{
		printf("buyCard(): FAIL on verifying have sufficient coins\n");
		numFailures++;
	}	
	
	// overall results
	if (numFailures == 0)
	{
		printf("buyCard(): PASSed all tests.\n");
	}
	else
	{
		printf("buyCard(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}