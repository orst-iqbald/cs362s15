// conleyme
// Unit test for buyCard function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define PLAYERS 2

void check_buy_card(struct gameState *post) {

	// check if buy card fails when there are no buys
	post->numBuys = 0;
	assert(buyCard(adventurer, post) == -1);
	// check if buyCard fails when there are no coins
	post->coins = 0;
	assert(buyCard(adventurer, post) == -1);
	// check that buyCard fails when there are no supplies
	post->supplyCount[adventurer] = 0;
	assert(buyCard(adventurer, post) == -1);
	
	// check that buyCard succeeds when all prerequisites are filled
	post->coins = 10;
	post->supplyCount[adventurer] = 10;
	post->numBuys = 10;
	assert(buyCard(adventurer, post) != -1); 
	assert(post->coins == (10 - getCost(adventurer)));
	assert(post->numBuys == 9);
	assert(post->supplyCount[adventurer] == 9);
}

int main() {

        int r;

        struct gameState post;
        int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
        r = initializeGame(PLAYERS, k, 1000, &post);

	printf("Testing buyCard function.\n");
	check_buy_card(&post);

	return 0;
}
