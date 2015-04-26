/*
 Matthew Ahle
 CS362 Assignment 3
 4/24/2015
 
 Adventurer card test
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int main() {
	int error = 0;
	/* initialize game variables */
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int treasureCount = 0, i, card, handCount;

	/* build gamestate to test */
	struct gameState *state = malloc(sizeof(struct gameState));

	/* initialize gamestate */
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("adventureTest(): Game initialization failed.\n");
		error = -1;
	}

	/* swap adventurer card into the players hand */
	state->hand[whoseTurn(state)][0] = adventurer;

	/* track number of treasures and number of adventurer cards in hand */
	for(i = 0; i < state->handCount[whoseTurn(state)]; ++i)
	{
		card = state->hand[whoseTurn(state)][i];
		if(card == copper ||
			card == silver ||
			card == gold)
		{
			++treasureCount;
		}
	}

	handCount = state->handCount[whoseTurn(state)];

	/* call effectAdventurer function */
	effectAdventurer(state, 0);

	/* check number of treasures and adventure cards in new hand */
	for(i = 0; i < state->handCount[whoseTurn(state)]; ++i)
	{
		card = state->hand[whoseTurn(state)][i];
		if(card == copper ||
			card == silver ||
			card == gold)
		{
			--treasureCount;
		}
	}
	/* if there is an error */
	if(treasureCount != -2)
	{
		printf("adventureTest(): There was a problem putting treasure cards into the players hand\n");
		error = -1;
	}
	/* if there is this error */
	if(state->hand[whoseTurn(state)][0] == adventurer)
	{
		printf("adventureTest(): Adventurer card was not discared from hand\n");
		error = -1;
	}
	/* if all tests pass */
	if(error != -1)
	{
		printf("adventureTest(): All tests passed.\n");
	}

	/* set deckCount to 0 and call effectAdventurer to force shuffle */
	state->deckCount[whoseTurn(state)] = 0;
	effectAdventurer(state, 0);

	free(state);
	return 0;
}