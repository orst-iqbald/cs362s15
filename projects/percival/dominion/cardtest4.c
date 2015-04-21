/* -----------------------------------------------------------------------
 * Unit test for cardEffectSteward(), which implements the Steward card. 
 * Tests that if choice1 is 1 then 2 cards are added to the player's hand (with
 * no changes to the coins or discards), if choice1 is 2 then the number of coins
 * increases by 2 (with no changes to hand or discards), and if choice1 is
 * something else then 2 cards are removed from the player's hand and trashed
 * (with no changes to coins). Also tests that the Steward is added to the
 * played pile.
 * 
 * Lines in makefile:
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
	int initialHandCount;
	int initialNumCoins;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, steward
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	
	// Test cardEffectSteward function with choice1 set to 1
	state->hand[0][0] = steward;	//make sure there's a steward in their hand
	initialHandCount = state->handCount[0];
	initialNumCoins = state->coins;
	cardEffectSteward(0, state, 1, 1, 2, 0);
	// check that there are "2 more cards" in player's hand
	// (count is actually 1 more to account for discarded Steward)
	if (state->handCount[0] != (initialHandCount + 1))
	{
		printf("cardEffectSteward(): FAIL on adding 2 cards to hand with option 1\n");
		numFailures++;
	}
	// check that the number of coins is unaltered
	if (state->coins != initialNumCoins)
	{
		printf("cardEffectSteward(): FAIL on not changing coins with option 1\n");
		numFailures++;
	}
	// check that Steward is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != steward)
	{
		printf("cardEffectSteward(): FAIL on adding card to played pile with option 1\n");
		numFailures++;
	}
	
	// Test cardEffectSteward function with choice1 set to 2
	state->hand[0][0] = steward;	//make sure there's a steward in their hand
	initialHandCount = state->handCount[0];
	initialNumCoins = state->coins;
	cardEffectSteward(0, state, 2, 1, 2, 0);
	// check that the number of cards in player's hand is "unaltered"
	// (count is actually 1 less due to discarded Steward)
	if (state->handCount[0] != (initialHandCount - 1))
	{
		printf("cardEffectSteward(): FAIL on not changing hand with option 2\n");
		numFailures++;
	}
	// check that the number of coins has increased by 2
	if (state->coins != (initialNumCoins + 2))
	{
		printf("cardEffectSteward(): FAIL on adding 2 coins with option 2\n");
		numFailures++;
	}
	// check that Steward is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != steward)
	{
		printf("cardEffectSteward(): FAIL on adding card to played pile with option 2\n");
		numFailures++;
	}
	
	// Test cardEffectSteward function with choice1 set to 3
	state->hand[0][0] = steward;	//make sure there's a steward in their hand
	initialHandCount = state->handCount[0];
	initialNumCoins = state->coins;
	cardEffectSteward(0, state, 3, 1, 2, 0);
	// check that there are "2 fewer" cards in player's hand (they were trashed)
	// (count is actually 3 less due to discarded Steward)
	if (state->handCount[0] != (initialHandCount - 3))
	{
		printf("cardEffectSteward(): FAIL on trashing 2 cards from hand with option 3\n");
		numFailures++;
	}
	// check that the number of coins is unaltered
	if (state->coins != initialNumCoins)
	{
		printf("cardEffectSteward(): FAIL on not changing coins with option 3\n");
		numFailures++;
	}
	// check that Steward is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != steward)
	{
		printf("cardEffectSteward(): FAIL on adding card to played pile with option 3\n");
		numFailures++;
	}
	
	// overall results
	if (numFailures == 0)
	{
		printf("cardEffectSteward(): PASSed all tests.\n");
	}
	else
	{
		printf("cardEffectSteward(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}