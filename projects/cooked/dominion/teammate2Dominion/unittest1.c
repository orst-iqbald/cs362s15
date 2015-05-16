/* ---------------------------------------------------------------------------------
 * Unit test for testing the buyCard() function
 * unittest1: unittest1.c dominion.o rngs.o
 * 		gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
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
	struct gameState *s = malloc(sizeof(struct gameState));

	int b, c;

	//Initialize the gamestate
	if(initializeGame(numPlayer, cards, seed, s) != 0) 
	{
		printf("buyCard(): Game initialization failed.\n");
		error = -1;
	}

	//Set the number of buys to 0
	s->numBuys = 0;
	s->coins = 50;
	if(buyCard(cards[0], s) != -1) 
	{
		printf("buyCard(): failing to check for number of buys\n");
		error = -1;
	}
	//Cleanup
	s->numBuys = 10;

	//Set the card supply count to 0
	s->supplyCount[adventurer] = 0;
	assert(supplyCount(adventurer, s) == 0);

	//Test buyCard when the card supply count is 0
	s->coins = 50;
	if(buyCard(cards[0], s) != -1) 
	{
		printf("buyCard(): failing to check the target cards supply count\n");
		error = -1;
	}
	//Cleanup
	s->supplyCount[adventurer] = 10;

	//Set the current players coin count to 0
	s->coins = 0;
	if(buyCard(cards[0], s) != -1) 
	{
		printf("buyCard(): failing to check for number of coins available\n");
		return -1;
	}
	//Cleanup
	updateCoins(whoseTurn(s), s, 0);

	//Successfully buy a card and check the discard pile to make sure it was successfully purchased
	//Use this block to also verify that coins are getting used and that buy is decremented
	s->coins = 50;
	b = s->numBuys;
	c = s->coins;
	if(buyCard(cards[0], s) == 0) 
	{
		if(!(s->discard[whoseTurn(s)][s->discardCount[whoseTurn(s)] == cards[0]])) 
		{
			printf("buyCard(): fails to add the card to the discard pile\n");
		}

		if(s->coins != (c - getCost(cards[0]))) 
		{
			printf("buyCard(): coins are not being appropriately decremented\n");
		}

		if(s->numBuys != (b - 1)) 
		{
			printf("buyCard(): buys are not being appropriately decremented\n");
		}
	}

	if(s->numBuys < 1 && s->phase != 1) 
	{
		printf("buyCard(): The phase is not properly changing once all buys are used\n");
	}


	if(error != -1)
	{
		printf("buyCard(): All tests passed.\n");
	}

	free(s);
	return 0;
}