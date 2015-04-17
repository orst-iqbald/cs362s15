/* ---------------------------------------------------------------------------------
 * Unit test for testing the initializeGame() function
 * unittest2: unittest2.c dominion.o rngs.o
 * 		gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
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

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Declare looping variables
	int i, j;

	//Housekeeping variables for checking hands
	int copperCount, estateCount;

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("initializeGame(): Game initialization failed.\n");
		error = -1;
	}

	//Check that the number of curse cards was set properly
	if(state->supplyCount[curse] != 10) 
	{
		printf("initializeGame(): Number of curse cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of estate cards was set properly
	if(state->supplyCount[estate] != 8) 
	{
		printf("initializeGame(): Number of estate cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of duchy cards was set properly
	if(state->supplyCount[duchy] != 8) 
	{
		printf("initializeGame(): Number of duchy cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of province cards was set properly
	if(state->supplyCount[province] != 8) 
	{
		printf("initializeGame(): Number of province cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of copper cards was set properly
	if(state->supplyCount[copper] != (60 - (7 * numPlayer))) 
	{
		printf("initializeGame(): Number of copper cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of silver cards was set properly
	if(state->supplyCount[silver] != 40) 
	{
		printf("initializeGame(): Number of silver cards is incorrect.\n");
		error = -1;
	}

	//Check that the number of gold cards was set properly
	if(state->supplyCount[gold] != 30) 
	{
		printf("initializeGame(): Number of gold cards is incorrect.\n");
		error = -1;
	}

	for(i = adventurer; i <= treasure_map; ++i)		//loop all cards
	{
		for(j = 0; j < 10; ++j)		//loop chosen cards
		{
			if(cards[j] == i)		//Found a match
			{
				//Check if card is a 'Victory' Kingdom card
				if(cards[j] == great_hall || cards[j] == gardens)
				{
					if(state->supplyCount[i] != 8)
					{
						printf("initializeGame(): Supply count of a 'Victory' kingdom cards is incorrect\n");
						error = -1;
					}
				}
				else
				{
					if(state->supplyCount[i] != 10)
					{
						printf("initializeGame(): Supply count of kingdom cards is incorrect\n");
						error = -1;
					}
				}
			}
		}
	}

	//Make sure each player has 7 copper cards and 3 estate cards
	for(i = 0; i < numPlayer; ++i)
	{
		copperCount = 0;
		estateCount = 0;
		for(j = 0; j < 10; ++j) 
		{
			if(state->deck[i][j] == copper)
			{
				++copperCount;
			}

			if(state->deck[i][j] == estate)
			{
				++estateCount;;
			}
		}

		if(copperCount != 7 && estateCount != 3)
		{
			printf("initializeGame(): Player %i has an inappropriate number of copper or estate cards\n", numPlayer + 1);
			error = -1;
		}
	}

	//Check that each supply card has its embargo tokens initialized to 0
	for(i = 0; i <= treasure_map; ++i)
	{
		if(state->embargoTokens[i] != 0)
		{
			printf("initializeGame(): Embargo tokens were not properly initialized\n");
			error = -1;
		}
	}

	//Check miscellaneous state variables, fail if any are incorrect
	if(state->outpostPlayed != 0 ||
		state->phase != 0 ||
		state->numActions != 1 ||
		state->numBuys != 1 ||
		state->playedCardCount != 0 ||
		state->whoseTurn != 0 ||
		state->handCount[state->whoseTurn] != 5)
	{
		printf("initializeGame(): Error in the miscellaneous state variables\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("initializeGame(): All tests passed.\n");
	}

	free(state);
	return 0;
}