/* -----------------------------------------------------------------------
 * Random tester for cardEffectGreatHall(), which implements the Great Hall card. 
 * Verifies that the player's hand grows by 1 card, the number of actions
 * increases by 1, and the Great Hall card is added to the played pile.
 * Randomness is focused on how the player's hand, deck and discard pile are 
 * filled, which are the main game state factors.
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "rngs.h"

#define NUM_POSSIBLE_CARDS 16
const int POSSIBLE_CARDS[NUM_POSSIBLE_CARDS] = {adventurer, council_room, feast,
	gardens, mine, remodel, smithy, village, baron, great_hall, copper, silver,
	gold, estate, duchy, province};

int main() 
{
	int numFailures = 0;		// to track overall number of failures
	int numIterFailures = 0;	// to track number of failures in iteration
	int i, j;					// loop counters
	int initialHandCount;		// to capture for later comparison
	int initialNumActions;		// to capture for later comparison
	int randIdx;				// to store random indices generated
	int seed;					// seed used for each iteration
	int handPos;				// position in hand to add Great Hall
	
	// Set up random number generator
	int startSeed = 12345;
	SelectStream(1);
	PutSeed((long)startSeed);
	
	// Set up initial game parameters
	int numPlayers = 2;
	int maxCards = MAX_HAND / 3;	//so never too many in any place
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	
	// Repeat the random test 100 times
	for (j = 0; j < 100; j++)
	{
		// set up an initial game state
		struct gameState *state = malloc(sizeof(struct gameState));
		seed = floor((Random() * startSeed) + 1);	// so random start
		initializeGame(numPlayers, kCards, seed, state);
		
		numIterFailures = 0;	//reset for iteration
		
		// Randomly adjust the game state, starting with turn and counts
		state->whoseTurn = floor(Random() * numPlayers);
		state->handCount[state->whoseTurn] = floor(Random() * maxCards) + 1;
		state->deckCount[state->whoseTurn] = floor(Random() * maxCards) + 1;
		state->discardCount[state->whoseTurn] = floor(Random() * maxCards) + 1;
		// set deck randomly
		for (i = 0; i < state->deckCount[state->whoseTurn]; i++)
		{
			// pick a random index from POSSIBLE_CARDS to put in position
			randIdx = floor(Random() * NUM_POSSIBLE_CARDS);
			state->deck[state->whoseTurn][i] = POSSIBLE_CARDS[randIdx];
		}
		// set hand randomly
		for (i = 0; i < state->handCount[state->whoseTurn]; i++)
		{
			// pick a random index from POSSIBLE_CARDS to put in position
			randIdx = floor(Random() * NUM_POSSIBLE_CARDS);
			state->hand[state->whoseTurn][i] = POSSIBLE_CARDS[randIdx];
		}
		// set discard randomly
		for (i = 0; i < state->discardCount[state->whoseTurn]; i++)
		{
			// pick a random index from POSSIBLE_CARDS to put in position
			randIdx = floor(Random() * NUM_POSSIBLE_CARDS);
			state->discard[state->whoseTurn][i] = POSSIBLE_CARDS[randIdx];
		}
		// then put the Great Hall in a random position in their hand, so have
		handPos = floor(Random() * state->handCount[state->whoseTurn]);
		state->hand[state->whoseTurn][handPos] = great_hall;
		// also randomly set the number of actions between 1 and 10 (reasonable range)
		state->numActions = floor(Random() * 10) + 1;
		
		// Print test case information
		printf("\nIteration %d: Player %d has %d cards in hand, ", j, state->whoseTurn, state->handCount[state->whoseTurn]);
		printf("%d in deck, %d in discard, ", state->deckCount[state->whoseTurn], state->discardCount[state->whoseTurn]);
		printf("%d actions, and the Great Hall in hand position %d.\n", state->numActions, handPos);
				
		// Call the cardEffectGreatHall function
		initialHandCount = state->handCount[state->whoseTurn];//store initial hand count
		initialNumActions = state->numActions;		//store initial number of actions
		cardEffectGreatHall(state->whoseTurn, state, handPos);
		
		// check that there's "1 more card" in the player's hand
		// (count actually stays same because also lost 1 for the discarded Great Hall)
		if (state->handCount[state->whoseTurn] != initialHandCount)
		{
			printf("Iteration %d - cardEffectGreatHall(): FAIL on adding a card to player's hand\n", j);
			numIterFailures++;
		}
		// check that there's 1 more action available
		if (state->numActions != (initialNumActions + 1))
		{
			printf("Iteration %d - cardEffectGreatHall(): FAIL on adding an action\n", j);
			numIterFailures++;
		}
		// check that Great Hall is in the played pile (last)
		if (state->playedCards[state->playedCardCount-1] != great_hall)
		{
			printf("Iteration %d - cardEffectGreatHall(): FAIL on adding card to played pile\n", j);
			numIterFailures++;
		}
			
		// results for iteration
		if (numIterFailures == 0)
		{
			printf("Iteration %d - cardEffectGreatHall(): PASSed all tests.\n", j);
		}
		else
		{
			printf("Iteration %d - cardEffectGreatHall(): FAILed %d tests.\n", j, numIterFailures);
		}
		numFailures += numIterFailures;
		
		// clean up
		free(state);
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
	
	return 0;
}