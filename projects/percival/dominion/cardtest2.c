/* -----------------------------------------------------------------------
 * Unit test for cardEffectAdventurer(), which implements the Adventurer card. 
 * Tests that the player's hand grows by 2 cards, that their hand includes at
 * least 2 treasures, and that the Adventurer card is added to the played pile.
 * 
 * Lines in makefile:
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	int numTreasures = 0;
	int i;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	state->hand[0][0] = adventurer;	//make sure there's an adventurer in their hand
	
	// Test the cardEffectAdventurer function
	int initialHandCount = state->handCount[0];
	cardEffectAdventurer(0, state);
	// check that there are 2 more cards in the player's hand
	// (count is actually 1 more to account for discarded Adventurer)
	if (state->handCount[0] != (initialHandCount + 1))
	{
		printf("cardEffectAdventurer(): FAIL on adding two cards to hand\n");
		numFailures++;
	}
	// check that there are at least two treasure cards in player's hand
	for (i = 0; i < state->handCount[0]; i++)
	{
		if (state->hand[0][i] == copper || state->hand[0][i] == silver
			|| state->hand[0][i] == gold)
		{
			numTreasures++;
		}
	}
	if (numTreasures < 2)
	{
		printf("cardEffectAdventurer(): FAIL on having at least 2 treasures in hand\n");
		numFailures++;
	}
	// check that Adventurer is in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != adventurer)
	{
		printf("cardEffectAdventurer(): FAIL on adding card to played pile\n");
		numFailures++;
	}
		
	// overall results
	if (numFailures == 0)
	{
		printf("cardEffectAdventurer(): PASSed all tests.\n");
	}
	else
	{
		printf("cardEffectAdventurer(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}