/*------------------------------------------------------------------
 * Card test #2: adventurerCard() card function
 * cardtest2: cardtest2.c dominion.o rngs.o
 *		gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
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
	struct gameState * state = malloc(sizeof(struct gameState));
	int numPlayer = 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	int i, Card, handCount;
	int tCount = 0;
	
	printf("adventurerCard(): Test Begins");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("adventurerCard(): Game initialization failed.\n");
		error = -1;
	}
	
	state->hand[whoseTurn(state)][0] = adventurer;
	
	for(i = 0; i < state->handCount[whoseTurn(state)]; i++)
	{
		Card = state->hand[whoseTurn(state)][i];
		if(Card == copper || Card == silver || Card == gold)
		{
			tCount++;
		}
	}
	
	handCount = state->handCount[whoseTurn(state)];
	
	adventurerCard(state, 0, 0);
	
	for(i = 0; i < state->handCount[whoseTurn(state)]; i++)
	{
		Card = state->hand[whoseTurn(state)][i];
		if(Card == copper || Card == silver || Card == gold)
		{
			tCount--;
		}
	}
	
	if(tCount != -2)
	{
		printf("adventureCard(): Failed to put treasure cards in player hand\n");
		error = -1;
	}
	
	if(error != -1)
	{
		printf("adventurerCard(): Tests are finished. All tests passed.\n");
	}
	
	free(state);
	return 0;
}
