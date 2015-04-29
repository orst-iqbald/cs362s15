/********************************
 * Unit Test for isGameOver()
 * *****************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main(){
	int i;
	struct gameState G;
	int p, r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	printf("Testing isGameOver...\n");

	r = initializeGame(2,k,1000,&G);
	//Test with all supplyCounts == 0
	for (i = 0; i <= 26; i++){
		G.supplyCount[i] = 0;
	}
	p = isGameOver(&G);
	assert (p == 1);
	printf("Passed test 1\n");

	//Test that play proceeds under normal circumstances
	for (i = 0; i <= 26; i++){
		G.supplyCount[i] = 1;
	}
	p = isGameOver(&G);
	assert(p != 1);
	printf("Passed test 2!\n");

	//Test for player out of range
	G.whoseTurn = 3;
	p = isGameOver(&G);
	printf("Does not break on out-of-range player (Passed test3)\n");

	//Test for provinces empty
	G.supplyCount[province] = 0;
	p = isGameOver(&G);
	assert (p == 1);
	printf("Passed test 4!\n");

	//Test for curse cards empty and two other cards
	for (i = 0; i <= 26; i++){
		G.supplyCount[i] = 1;
	}
	G.supplyCount[curse] = 0;
	G.supplyCount[adventurer] = 0;
	G.supplyCount[council_room] = 0;
	p = isGameOver(&G);
	assert(p == 1);
	printf("Passed test 5!\n");

	return 0;
}
