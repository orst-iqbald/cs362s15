/*------------------------------------------------------------------
 * Unit test #1: shuffle() function
 * unittest1: unittest1.c dominion.o rngs.o
 *		gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
 *------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"


int main () {
	int error = 0;
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	
	//Build gamestate
	struct gameState * state = malloc(sizeof(struct gameState));
	
	int newDeck[10];
	int i;
	
	printf("shuffle(): Test Begins\n");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("shuffle(): Game initialization failed.\n");
		error = -1;
	}
	
	for(i = 0; i < 10; i++) 
	{
		newDeck[i] = state->deck[0][i];
	}
	
	
	state->deckCount[0] = 0;
	if(shuffle(0, state) != -1)
	{
		printf("shuffle(): Does not check if player has 1 card or more.\n");
		error = -1;
	}
	
	state->deckCount[0] = 10;
	if(shuffle(0, state) < 0)
	{
		printf("shuffle(): Error shuffling player's cards.\n");
	}
	
	if(error != -1)
	{
		printf("shuffle(): Tests are finished. All tests passed.\n");
	}
	
	free(state);
	return 0;
}
	
