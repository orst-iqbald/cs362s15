/* -----------------------------------------------------------------------
 * Unit test for endTurn(), which tests that the player's hand is emptied
 * (handCount of 0 and size of discard pile grows by previous handCount), the 
 * current player (whoseTurn) has been shifted to the next player, the variables
 * outpostPlayed, phase, numActions, numBuys, and playedCardCount have been
 * reset, the next player has 5 cards in their hand, and the coins variables
 * is set based on those cards.
 * 
 * Lines in makefile:
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
	int numCoins = 0;
	int i, initialHandCount, initialDiscardCount;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	
	// Test ending the turn of the first player
	initialHandCount = state->handCount[0];
	initialDiscardCount = state->discardCount[0];
	endTurn(state);
	// check that first player's handCount is now 0
	if (state->handCount[0] != 0)
	{
		printf("endTurn(): FAIL on resetting first player's handCount\n");
		numFailures++;
	}
	// check that first player's hand was added to discard (discardCount grows)
	if (state->discardCount[0] != (initialHandCount + initialDiscardCount))
	{
		printf("endTurn(): FAIL on adding first player's hand to discardCount\n");
		numFailures++;
	}
	// check that current player (whoseTurn) is now the second player
	if (state->whoseTurn != 1)
	{
		printf("endTurn(): FAIL on moving whoseTurn from 1st to 2nd player\n");
		numFailures++;
	}
	// check outpostPlayed, phase, numActions, numBuys, and playedCardCount reset
	if (state->outpostPlayed != 0)
	{
		printf("endTurn(): FAIL on resetting outpostPlayed\n");
		numFailures++;
	}
	if (state->phase != 0)
	{
		printf("endTurn(): FAIL on resetting phase\n");
		numFailures++;
	}
	if (state->numActions != 1)
	{
		printf("endTurn(): FAIL on resetting numActions\n");
		numFailures++;
	}
	if (state->numBuys != 1)
	{
		printf("endTurn(): FAIL on resetting numBuys\n");
		numFailures++;
	}
	if (state->playedCardCount != 0)
	{
		printf("endTurn(): FAIL on resetting playedCardCount\n");
		numFailures++;
	}
	// check next/ new current player (2nd) has 5 cards in hand
	if (state->handCount[1] != 5)
	{
		printf("endTurn(): FAIL on putting 5 cards in next (2nd) player's hand\n");
		numFailures++;
	}
	// check that state->coins matches the value of coins in their hand
	for (i = 0; i < 5; i++)
	{
		if (state->hand[1][i] == copper)
			numCoins += 1;
		if (state->hand[1][i] == silver)
			numCoins += 2;
		if (state->hand[1][i] == gold)
			numCoins += 3;
	}
	if (state->coins != numCoins)
	{
		printf("endTurn(): FAIL on setting coins based on next (2nd) player's hand\n");
		numFailures++;
	}
	
	// Test ending the turn of the second player
	initialHandCount = state->handCount[1];
	initialDiscardCount = state->discardCount[1];
	endTurn(state);
	// check that second player's handCount is now 0
	if (state->handCount[1] != 0)
	{
		printf("endTurn(): FAIL on resetting second player's handCount\n");
		numFailures++;
	}
	// check that second player's hand was added to discard (discardCount grows)
	if (state->discardCount[1] != (initialHandCount + initialDiscardCount))
	{
		printf("endTurn(): FAIL on adding second player's hand to discardCount\n");
		numFailures++;
	}
	// check that current player (whoseTurn) is now the first player (wraparound)
	if (state->whoseTurn != 0)
	{
		printf("endTurn(): FAIL on moving whoseTurn from 2nd to 1st player\n");
		numFailures++;
	}
	// check next/ new current player (1st) has 5 cards in hand
	if (state->handCount[0] != 5)
	{
		printf("endTurn(): FAIL on putting 5 cards in next (1st) player's hand\n");
		numFailures++;
	}
	// check that state->coins matches the value of coins in their hand
	numCoins = 0;
	for (i = 0; i < 5; i++)
	{
		if (state->hand[0][i] == copper)
			numCoins += 1;
		if (state->hand[0][i] == silver)
			numCoins += 2;
		if (state->hand[0][i] == gold)
			numCoins += 3;
	}
	if (state->coins != numCoins)
	{
		printf("endTurn(): FAIL on setting coins based on next (1st) player's hand\n");
		numFailures++;
	}
	
	// overall results
	if (numFailures == 0)
	{
		printf("endTurn(): PASSed all tests.\n");
	}
	else
	{
		printf("endTurn(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}