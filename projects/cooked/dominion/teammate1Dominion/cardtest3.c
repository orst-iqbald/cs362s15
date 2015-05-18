/* ---------------------------------------------------------------------------------
 * Unit test for testing the effectCouncilRoom() function
 * cardtest3: cardtest3.c dominion.o rngs.o
 * 		gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	int handCount[numPlayer];
	int i, buyCount;

	//Build a gamestate to test with
	struct gameState *state = malloc(sizeof(struct gameState));

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, state) != 0) 
	{
		printf("councilroomTest(): Game initialization failed.\n");
		error = -1;
	}

	//Swap a council room card into the players hand
	state->hand[whoseTurn(state)][0] = council_room;

	//Track the handCount for each player
	for(i = 0; i < numPlayer; ++i)
	{
		handCount[i] = state->handCount[i];
	}

	//Track the original number of buys
	buyCount = state->numBuys;

	//Call the effectCouncilRoom function
	pCouncilRoom(state, 0);

	//Check that the Council Room is in the discard pile
	if(state->playedCards[state->playedCardCount - 1] != council_room)
	{
		printf("councilroomTest(): Council room was not discarded properly\n");
		error = -1;
	}

	//Handcount for the current player should increment by 3 (+4 cards, -1 discard)
	//and each other players handcount should increment by 1
	for(i = 0; i < numPlayer; ++i)
	{
		if(i == whoseTurn(state))
		{
			if(state->handCount[i] != (handCount[i] + 3))
			{
				printf("councilroomTest(): Error in incrementing the current players handCount\n");
				error = -1;
			}
		}
		else
		{
			if(state->handCount[i] != (handCount[i] + 1))
			{
				printf("councilroomTest(): Error in incrementing the other players handCounts\n");
				error = -1;
			}
		}
	}

	//Check that the current players number of buys is incremented
	if(state->numBuys != (buyCount + 1))
	{
		printf("councilroomTest(): Error incrementing the number of buys\n");
		error = -1;
	}

	if(error != -1)
	{
		printf("councilroomTest(): All tests passed.\n");
	}

	free(state);
	return 0;
}