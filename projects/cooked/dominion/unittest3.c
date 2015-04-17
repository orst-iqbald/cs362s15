/* ---------------------------------------------------------------------------------
 * Unit test for testing the shuffle() function
 * unittest3: unittest3.c dominion.o rngs.o
 * 		gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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

int testCompare(const void* a, const void* b) {
  if (*(int*)a > *(int*)b)
    return 1;
  if (*(int*)a < *(int*)b)
    return -1;
  return 0;
}

int main() {
	int error = 0;
	//Initialize game variables
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine,
	 remodel, smithy, village, baron, great_hall};
	int seed = 12345;

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Deck variables
	int newDeck[10];
	int i;

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("shuffle(): Game initialization failed.\n");
		error = -1;
	}

	//Reset the prng
	SelectStream(1);
	PutSeed((long)seed);

	//Copy over player 1's shuffled deck
	for(i = 0; i < 10; ++i)
	{
		newDeck[i] = state->deck[0][i];
	}

	//Sort player 1's deck
	qsort ((void*)(state->deck[0]), 10, sizeof(int), testCompare);

	//Compare the sorted deck to the shuffled deck, should fail comparison
	if(memcmp(newDeck, state->deck[0], sizeof(newDeck)) == 0)
	{
		printf("shuffle(): Sort failed, player 1's deck is not in sorted order\n");
		error = -1;
	}

	state->deckCount[0] = 10;
	if(shuffle(0, state) < 0)
	{
		printf("shuffle(): An error occured while shuffling player 1's deck\n");
		error = -1;
	}

	if(memcmp(newDeck, state->deck[0], sizeof(newDeck)) != 0)
	{
		printf("shuffle(): Shuffled deck was not deterministic, shuffle() has failed\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("shuffle(): All tests passed.\n");
	}

	free(state);
	return 0;
}