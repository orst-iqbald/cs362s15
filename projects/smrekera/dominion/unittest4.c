/*------------------------------------------------------------------
 * Unit test #4: updateCoins() function
 * unittest4: unittest4.c dominion.o rngs.o
 *		gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int player = 1;
	int bonus = 2;
	int coins;
	
	printf("updateCoins(): Test Begins\n");
	
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("updateCoins(): Game initialization failed.\n");
		error = -1;
	}
	
	state->handCount[player] = 3;
	state->hand[player][0] = 1;
	state->hand[player][1] = copper;
	state->hand[player][2] = copper;
	
	if(updateCoins(player, state, bonus) != 0) 
	{
			printf("updateCoins(): Failed to update coins\n");
			error = -1;
	} else {
		int expected = 4;
		coins = state->coins;
		if (expected != coins)
		{
			printf("updateCoins(): Failed to update coins with correct amount\n");
			error = -1;
		}
	}
	
	bonus = 4;
	
	state->handCount[player] = 4;
	state->hand[player][0] = 1;
	state->hand[player][1] = gold;
	state->hand[player][2] = silver;
	state->hand[player][3] = copper;
	
	if(updateCoins(player, state, bonus) != 0) 
	{
			printf("updateCoins(): Failed to update coins\n");
			error = -1;
	} else {
		int expected = 4;
		if (expected != state->coins)
		{
			printf("updateCoins(): Failed to update coins with correct amount\n");
			error = -1;
		}
	}
	
	bonus = 0;
	
	state->handCount[player] = 5;
	state->hand[player][0] = 1;
	state->hand[player][1] = gold;
	state->hand[player][2] = silver;
	state->hand[player][3] = gold;
	state->hand[player][4] = 3;
	
	if(updateCoins(player, state, bonus) != 0) 
	{
			printf("updateCoins(): Failed to update coins\n");
			error = -1;
	} else {
		int expected = 4;
		if (expected != state->coins)
		{
			printf("updateCoins(): Failed to update coins with correct amount\n");
			error = -1;
		}
	}
	
	if(error != -1)
	{
		printf("updateCoins(): Tests are finished. Passed all tests\n");
	}
	
	free(state);
	return 0;
}