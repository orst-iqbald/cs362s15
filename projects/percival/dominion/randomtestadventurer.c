/* -----------------------------------------------------------------------
 * Random tester for cardEffectAdventurer(), which implements the Adventurer card. 
 * Verifies that the player's hand grows by 2 cards, that their hand includes at
 * least 2 treasures, and that the Adventurer card is added to the played pile.
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
	int numTreasures = 0;		// to hold number of treasures
	int i, j;					// loop counters
	int initialHandCount;		// to capture for later comparison
	int randIdx;				// to store random indices generated
	int seed;					// seed used for each iteration
	int handPos;				// position in hand to add adventurer
	
	// Set up random number generator
	int startSeed = 12345;
	SelectStream(1);
	PutSeed((long)startSeed);
	
	// Set up initial game parameters
	int numPlayers = 2;
	int maxCards = MAX_HAND / 3;	//so never too many in any place
	int kCards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	
	// Repeat the random test 100 times - should include shuffles
	for (j = 0; j < 100; j++)
	{
		// set up an initial game state
		struct gameState *state = malloc(sizeof(struct gameState));
		seed = floor((Random() * startSeed) + 1);	// so random start
		initializeGame(numPlayers, kCards, seed, state);
		
		numIterFailures = 0;	//reset for iteration
		numTreasures = 0;		//reset for iteration
		
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
		// then put the adventurer in a random position in their hand, so have
		handPos = floor(Random() * state->handCount[state->whoseTurn]);
		state->hand[state->whoseTurn][handPos] = adventurer;
		
		// Print test case information
		printf("\nIteration %d: Player %d has %d cards in hand, ", j, state->whoseTurn, state->handCount[state->whoseTurn]);
		printf("%d in deck, %d in discard, ", state->deckCount[state->whoseTurn], state->discardCount[state->whoseTurn]);
		printf("and the adventurer in hand position %d.\n", handPos);
				
		// Call the cardEffectAdventurer function
		initialHandCount = state->handCount[state->whoseTurn];//store initial hand count
		cardEffectAdventurer(state->whoseTurn, state);
		
		// check that there are 2 more cards in the player's hand
		// (count is actually 1 more to account for discarded Adventurer)
		if (state->handCount[state->whoseTurn] != (initialHandCount + 1))
		{
			printf("Iteration %d - cardEffectAdventurer(): FAIL on adding two cards to hand\n", j);
			numIterFailures++;
		}
		// check that there are at least two treasure cards in player's hand
		for (i = 0; i < state->handCount[state->whoseTurn]; i++)
		{
			if (state->hand[state->whoseTurn][i] == copper || state->hand[state->whoseTurn][i] == silver
				|| state->hand[state->whoseTurn][i] == gold)
			{
				numTreasures++;
			}
		}
		if (numTreasures < 2)
		{
			printf("Iteration %d - cardEffectAdventurer(): FAIL on having at least 2 treasures in hand\n", j);
			numIterFailures++;
		}
		// check that Adventurer is in the played pile (last)
		if (state->playedCards[state->playedCardCount-1] != adventurer)
		{
			printf("Iteration %d - cardEffectAdventurer(): FAIL on adding card to played pile\n", j);
			numIterFailures++;
		}
			
		// results for iteration
		if (numIterFailures == 0)
		{
			printf("Iteration %d - cardEffectAdventurer(): PASSed all tests.\n", j);
		}
		else
		{
			printf("Iteration %d - cardEffectAdventurer(): FAILed %d tests.\n", j, numIterFailures);
		}
		numFailures += numIterFailures;
		
		// clean up
		free(state);
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
	
	return 0;
}