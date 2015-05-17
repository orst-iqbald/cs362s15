/* ---------------------------------------------------------------------------------
 * Unit test for testing the effectAdventurer() function
 * cardtest1: cardtest1.c dominion.o rngs.o
 * 		gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
 *
 * ---------------------------------------------------------------------------------
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
	//Initialize game variables
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;
	int treasureCount = 0, i, card, handCount;

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("adventureTest(): Game initialization failed.\n");
		error = -1;
	}

	//Swap an adventurer card into the players hand
	state->hand[whoseTurn(state)][0] = adventurer;

	//Track the number of treasures in hand and number of adventurer cards
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

	//Call the effectAdventurer function
	cardAdventurer(whoseTurn(state), state);

	//Check the number of treasures and adventure cards in our new hand
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

	if(treasureCount != -2)
	{
		printf("adventureTest(): There was a problem putting treasure cards into the players hand\n");
		error = -1;
	}

	if(state->hand[whoseTurn(state)][0] == adventurer)
	{
		printf("adventureTest(): Adventurer card was not discared from hand\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("adventureTest(): All tests passed.\n");
	}

	//Set the deckCount to 0 and call effectAdventurer to force a shuffle
	state->deckCount[whoseTurn(state)] = 0;
	cardAdventurer(whoseTurn(state), state);

	free(state);
	return 0;
}