/*************************
 * Card Test for Remodel
 ************************/

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

	r = initializeGame(2, k, 1000, &G);
	
	printf("Testing Remodel...\n");
	
	//Test with hand empty
	G.handCount[1] = 0;
	p = playRemodel(&G, 1, 1, 1, 2);
	printf("Bug: Cannot play with no cards in hand!\n");
	
	//Test with supply pile empty
	G.supplyCount[3] = 0;
	p = playRemodel(&G,1,1,1,3);
	assert(G.supplyCount[3] == 0);
	printf("Bug: shouldn't be able to select empty pile\n");

	//Test with an expensive card (more than +2)
	p = playRemodel(&G,1,1,copper,province);
	assert(p == -1);
	printf("Passed test 3\n");
	
	return 0;	
}
