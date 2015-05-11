/******************************
 * Unit Test for gainCard()
 *****************************/

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

	printf("Testing gainCrad...\n");

	//assert return val of -1 for empty pile
	G.supplyCount[1] = 0;
	p = gainCard(1, &G, 1, 1);
	assert(p == -1);
	printf("Passed test 1\n");	

	//Test all three values of toFlag
	for(i = 0; i < 3; i++) {
		G.supplyCount[1] = 1;
		G.handCount[1] = 2;
		G.discardCount[1] = 2;
		G.deckCount[1] = 20;
		p = gainCard(1, &G, i, 1);
			//Make sure supply decreases
		assert(G.supplyCount[1] == 0);
		if(i ==2) {
			assert (G.handCount[1] == 3);
		}
		else if(i == 1) {
			assert (G.deckCount[1] = 21);	
		}
		else { 
			assert(G.discardCount[1] = 3);
		}
	}
	printf("Passed test 2\n");
		
	return 0;	
}
