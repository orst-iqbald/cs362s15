/* -----------------------------------------------------------------------
 * Unit test for discardCard(), which tests that the card is correctly
 * removed from the player's hand, meaning that the handCount has decreased
 * by one, the card is no longer in their hand, and the card has been added
 * to the played pile if it was not trashed.
 * 
 * Lines in makefile:
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
	int inHand = 0;
	int i;
	// Set up initial game state
	int numPlayers = 2;
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	struct gameState *state = malloc(sizeof(struct gameState));
	initializeGame(numPlayers, kCards, seed, state);
	// Change their hand so we know exactly what's in it
	int hand[5] = { copper, silver, gold, smithy, adventurer };
	memcpy(state->hand[0], hand, sizeof(int) * 5);
	int laterHand[1] = { silver };	//for use later
	
	// Test the card in the last position of the hand, with trash flag 1
	discardCard(state->handCount[0]-1, 0, state, 1);
	// check handCount decremented
	if (state->handCount[0] != 4)
	{
		printf("discardCard(): FAIL on handCount in last position with trash flag 1\n");
		numFailures++;
	}
	// check for that card (adventurer) in hand
	for (i = 0; i < state->handCount[0]; i++)
	{
		if (state->hand[0][i] == adventurer)
		{
			inHand = 1;
		}
	}
	if (inHand == 1)
	{
		printf("discardCard(): FAIL on removal from hand in last position with trash flag 1\n");
		numFailures++;
	}
	
	// Test the card in the first position of the hand, with trash flag 0
	discardCard(0, 0, state, 0);
	// check handCount decremented
	if (state->handCount[0] != 3)
	{
		printf("discardCard(): FAIL on handCount in first position with trash flag 0\n");
		numFailures++;
	}
	// check for that card (copper) in hand
	inHand = 0;
	for (i = 0; i < state->handCount[0]; i++)
	{
		if (state->hand[0][i] == copper)
		{
			inHand = 1;
		}
	}
	if (inHand == 1)
	{
		printf("discardCard(): FAIL on removal from hand in first position with trash flag 0\n");
		numFailures++;
	}
	// check that it's in the played pile (last)
	if (state->playedCards[state->playedCardCount-1] != copper)
	{
		printf("discardCard(): FAIL on addition to played pile in first position with trash flag 0\n");
		numFailures++;
	}
	
	// Test the last remaining card in the hand, with trash flag 1
	memcpy(state->hand[0], laterHand, sizeof(int) * 1);	//set hand to have 1 card
	state->handCount[0] = 1;
	discardCard(0, 0, state, 1);
	// check handCount decremented
	if (state->handCount[0] != 0)
	{
		printf("discardCard(): FAIL on handCount on last card with trash flag 1\n");
		numFailures++;
	}
	// check for that card (silver) in hand
	inHand = 0;
	for (i = 0; i < state->handCount[0]; i++)
	{
		if (state->hand[0][i] == silver)
		{
			inHand = 1;
		}
	}
	if (inHand == 1)
	{
		printf("discardCard(): FAIL on removal from hand on last card with trash flag 1\n");
		numFailures++;
	}

	// overall results
	if (numFailures == 0)
	{
		printf("discardCard(): PASSed all tests.\n");
	}
	else
	{
		printf("discardCard(): FAILed %d tests.\n", numFailures);
	}
	
	// clean up and exit
	free(state);
	return 0;
}