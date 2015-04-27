/*------------------------------------------------------------------
 * Unit test #3: initializeGame() function
 * unittest3: unittest3.c dominion.o rngs.o
 *		gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
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
	
	struct gameState * state = malloc(sizeof(struct gameState));
	int error = 0;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1111;
	
	printf("initializeGame(): Test Begins\n");
	
	int numPlayer = 10;
	//check if game will initialize with too many players
	if(initializeGame(numPlayer, cards, seed, state) != -1)
	{
		printf("initializeGame(): Failed to allow too many players\n");
		error = -1;
	}
	
	numPlayer = 1;
	//check if game will initialize with too few players
	if(initializeGame(numPlayer, cards, seed, state) != -1)
	{
		printf("initializeGame(): Failed to allow too few players\n");
		error = -1;
	}
	
	numPlayer = 2;
	
	//checking correct amounts against the state of the game
	if(initializeGame(numPlayer, cards, seed, state) != 0)
	{
		printf("initializeGame(): Failed to allow acceptable amount of players\n");
		error = -1;
	}
	
	if(state->supplyCount[curse] != 10)
	{
		printf("initializeGame(): Curse card amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[estate] != 8)
	{
		printf("initializeGame(): Estate card amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[duchy] != 8)
	{
		printf("initializeGame(): Duchy card amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[province] != 8)
	{
		printf("initializeGame(): Province card amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[gold] != 30)
	{
		printf("initializeGame(): Gold amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[silver] != 40)
	{
		printf("initializeGame(): Silver amount is incorrect\n");
		error = -1;
	}
	
	if(state->supplyCount[copper] != 60 - (7 * numPlayer))
	{
		printf("initializeGame(): Copper amount is incorrect\n");
		error = -1;
	}
		
	if(error != -1)
	{
		printf("initializeGame(): Tests are finished. Passed all tests\n");
	}
	
	free(state);
	return 0;
	
	
}