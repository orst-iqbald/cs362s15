/****************************
 * Unit Test for buyCard()
 ***************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	struct gameState G;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int p, r;
	r = initializeGame(2, k, 1000, &G);	
	
	printf("Testing buyCard...\n");

	//Test with numBuys ==0
	G.numBuys = 0;
	p = buyCard(1, &G);
	assert(p == -1);
	printf("Passed test 1\n");

	//Test with supply pile empty
	G.numBuys = 1;
	G.supplyCount[1] = 0;
	p = buyCard(1, &G);
	assert(p == -1);
	printf("Passed test 2\n");
	
	//Test with not enough coins
	G.numBuys = 1;
	G.coins = 0;
	G.supplyCount[1] = 2;
	p=buyCard(1, &G);
	assert (p== -1);
	printf("Passed test 3\n");
	
	//Test with each player
	for (i = 0; i < 3; i ++) {
		G.whoseTurn = i;
		G.numBuys = 1;
		G.supplyCount[1] = 1;
		G.coins = 20;
		p = buyCard(1, &G);
		assert (p != -1);
	}
	printf("Passed test 4\n");

	//Make sure coins decrease
	G.numBuys = 1;
	G.supplyCount[1] = 2;
	G.coins = 20;
	p = buyCard(1, &G);
	i = getCost(1);
	assert (G.coins == 18);
	printf("Passed test 5\n");

	//Make sure buys decrease
	G.numBuys = 2;
	G.supplyCount[1] = 2;
	G.coins = 20;
	p = buyCard(1, &G);
	assert (G.numBuys == 1);
	printf("Passed test 6\n");	

	return 0;
}
