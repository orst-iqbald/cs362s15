/*------------------------------------------------------------------
 * Unit test #2: isGameOver() function
 * unittest2: unittest2.c dominion.o rngs.o
 *		gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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
	int numPlayer= 2;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	
	
	printf("isGameOver: Test Begins\n");
	
	//initialize game
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("isGameOver(): Game failed to initialize.\n");
		error = -1;
	}
	
	state->supplyCount[province] = 0;
	//Check if all province card are gone the game will end
	if(isGameOver(state) != 1) 
	{
		printf("isGameOver(): Failed to end game when Province card equals zero\n");
		error = -1;
	}
	//set province to amount that would not end game
	state->supplyCount[province] =4;
	
	state->supplyCount[feast] = 0;
	state->supplyCount[mine] = 0;
	state->supplyCount[remodel] = 0;
	//Check if 3 supply files are empty that game will end
	if(isGameOver(state) != 1)
	{
		printf("isGameOver(): Failed to end game when 3 supply pile were empty\n");
		error = -1;
	}
	//restoring supply cards
	state->supplyCount[feast] = 5;
	state->supplyCount[mine] = 5;
	state->supplyCount[remodel] = 5;
	
	state->supplyCount[smithy] = 0;
	state->supplyCount[village] = 0;
	state->supplyCount[gardens] = 0;
	//Check if 3 different supply files are empty that game will end
	if(isGameOver(state) != 1)
	{
		printf("isGameOver(): Failed to end game when 3 supply pile were empty\n");
		error = -1;
	}
	
	if(error != -1)
	{
		printf("isGameOver(): Tests are finished. Passed all tests\n");
	}
	
	free(state);
	return 0;
}	
